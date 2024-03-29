<?php
/**
 * @file
 * This script runs Drupal tests from command line.
 */

define('SIMPLETEST_SCRIPT_COLOR_PASS', 32); // Green.
define('SIMPLETEST_SCRIPT_COLOR_FAIL', 31); // Red.
define('SIMPLETEST_SCRIPT_COLOR_EXCEPTION', 33); // Brown.

define('SIMPLETEST_SCRIPT_EXIT_SUCCESS', 0);
define('SIMPLETEST_SCRIPT_EXIT_FAILURE', 1);
define('SIMPLETEST_SCRIPT_EXIT_EXCEPTION', 2);

// Set defaults and get overrides.
list($args, $count) = simpletest_script_parse_args();

if ($args['help'] || $count == 0) {
  simpletest_script_help();
  exit(($count == 0) ? SIMPLETEST_SCRIPT_EXIT_FAILURE : SIMPLETEST_SCRIPT_EXIT_SUCCESS);
}

if ($args['execute-test']) {
  // Masquerade as Apache for running tests.
  simpletest_script_init("Apache");
  simpletest_script_run_one_test($args['test-id'], $args['execute-test']);
}
else {
  // Run administrative functions as CLI.
  simpletest_script_init(NULL);
}

// Bootstrap to perform initial validation or other operations.
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
if (!module_exists('simpletest')) {
  simpletest_script_print_error("The simpletest module must be enabled before this script can run.");
  exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
}

if ($args['clean']) {
  // Clean up left-over times and directories.
  simpletest_clean_environment();
  echo "\nEnvironment cleaned.\n";

  // Get the status messages and print them.
  $messages = array_pop(drupal_get_messages('status'));
  foreach ($messages as $text) {
    echo " - " . $text . "\n";
  }
  exit(SIMPLETEST_SCRIPT_EXIT_SUCCESS);
}

// Load SimpleTest files.
$groups = simpletest_test_get_all();
$all_tests = array();
foreach ($groups as $group => $tests) {
  $all_tests = array_merge($all_tests, array_keys($tests));
}
$test_list = array();

if ($args['list']) {
  // Display all available tests.
  echo "\nAvailable test groups & classes\n";
  echo   "-------------------------------\n\n";
  foreach ($groups as $group => $tests) {
    echo $group . "\n";
    foreach ($tests as $class => $info) {
      echo " - " . $info['name'] . ' (' . $class . ')' . "\n";
    }
  }
  exit(SIMPLETEST_SCRIPT_EXIT_SUCCESS);
}

$test_list = simpletest_script_get_test_list();

// Try to allocate unlimited time to run the tests.
drupal_set_time_limit(0);

simpletest_script_reporter_init();

// Setup database for test results.
$test_id = db_insert('simpletest_test_id')->useDefaults(array('test_id'))->execute();

// Execute tests.
$status = simpletest_script_execute_batch($test_id, simpletest_script_get_test_list());

// Retrieve the last database prefix used for testing and the last test class
// that was run from. Use the information to read the lgo file in case any
// fatal errors caused the test to crash.
list($last_prefix, $last_test_class) = simpletest_last_test_get($test_id);
simpletest_log_read($test_id, $last_prefix, $last_test_class);

// Stop the timer.
simpletest_script_reporter_timer_stop();

// Display results before database is cleared.
simpletest_script_reporter_display_results();

if ($args['xml']) {
  simpletest_script_reporter_write_xml_results();
}

// Cleanup our test results.
simpletest_clean_results_table($test_id);

// Test complete, exit.
exit($status);

/**
 * Print help text.
 */
function simpletest_script_help() {
  global $args;

  echo <<<EOF

Run Drupal tests from the shell.

Usage:        {$args['script']} [OPTIONS] <tests>
Example:      {$args['script']} Profile

All arguments are long options.

  --help      Print this page.

  --list      Display all available test groups.

  --clean     Cleans up database tables or directories from previous, failed,
              tests and then exits (no tests are run).

  --url       Immediately precedes a URL to set the host and path. You will
              need this parameter if Drupal is in a subdirectory on your
              localhost and you have not set \$base_url in settings.php. Tests
              can be run under SSL by including https:// in the URL.

  --php       The absolute path to the PHP executable. Usually not needed.

  --concurrency [num]

              Run tests in parallel, up to [num] tests at a time.

  --all       Run all available tests.

  --class     Run tests identified by specific class names, instead of group names.
              A specific test method can be added, for example,
              'UserAccountLinksUnitTests::testDisabledAccountLink'.

  --file      Run tests identified by specific file names, instead of group names.
              Specify the path and the extension (i.e. 'modules/user/user.test').

  --directory Run all tests found within the specified file directory.

  --xml       <path>

              If provided, test results will be written as xml files to this path.

  --color     Output text format results with color highlighting.

  --verbose   Output detailed assertion messages in addition to summary.

  --fail-only When paired with --verbose, do not print the detailed messages
              for passing tests.

  --cache     (Experimental) Cache result of setUp per installation profile.
              This will create one cache entry per profile and is generally safe
              to use.
              To clear all cache entries use --clean.

  --cache-modules

              (Experimental) Cache result of setUp per installation profile and
              installed modules. This will create one copy of the database
              tables per module-combination and therefore this option should not
              be used when running all tests. This is most useful for local
              development of individual test cases. This option implies --cache.
              To clear all cache entries use --clean.

  <test1>[,<test2>[,<test3> ...]]

              One or more tests to be run. By default, these are interpreted
              as the names of test groups as shown at
              ?q=admin/config/development/testing.
              These group names typically correspond to module names like "User"
              or "Profile" or "System", but there is also a group "XML-RPC".
              If --class is specified then these are interpreted as the names of
              specific test classes whose test methods will be run. Tests must
              be separated by commas. Ignored if --all is specified.

To run this script you will normally invoke it from the root directory of your
Drupal installation as the webserver user (differs per configuration), or root:

sudo -u [wwwrun|www-data|etc] php ./scripts/{$args['script']}
  --url http://example.com/ --all
sudo -u [wwwrun|www-data|etc] php ./scripts/{$args['script']}
  --url http://example.com/ --class BlockTestCase
\n
EOF;
}

/**
 * Parse execution argument and ensure that all are valid.
 *
 * @return The list of arguments.
 */
function simpletest_script_parse_args() {
  // Set default values.
  $args = array(
    'script' => '',
    'help' => FALSE,
    'list' => FALSE,
    'clean' => FALSE,
    'url' => '',
    'php' => '',
    'concurrency' => 1,
    'all' => FALSE,
    'class' => FALSE,
    'file' => FALSE,
    'directory' => '',
    'color' => FALSE,
    'verbose' => FALSE,
    'cache' => FALSE,
    'cache-modules' => FALSE,
    'test_names' => array(),
    'fail-only' => FALSE,
    // Used internally.
    'test-id' => 0,
    'execute-test' => '',
    'xml' => '',
  );

  // Override with set values.
  $args['script'] = basename(array_shift($_SERVER['argv']));

  $count = 0;
  while ($arg = array_shift($_SERVER['argv'])) {
    if (preg_match('/--(\S+)/', $arg, $matches)) {
      // Argument found.
      if (array_key_exists($matches[1], $args)) {
        // Argument found in list.
        $previous_arg = $matches[1];
        if (is_bool($args[$previous_arg])) {
          $args[$matches[1]] = TRUE;
        }
        else {
          $args[$matches[1]] = array_shift($_SERVER['argv']);
        }
        // Clear extraneous values.
        $args['test_names'] = array();
        $count++;
      }
      else {
        // Argument not found in list.
        simpletest_script_print_error("Unknown argument '$arg'.");
        exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
      }
    }
    else {
      // Values found without an argument should be test names.
      $args['test_names'] += explode(',', $arg);
      $count++;
    }
  }

  // Validate the concurrency argument
  if (!is_numeric($args['concurrency']) || $args['concurrency'] <= 0) {
    simpletest_script_print_error("--concurrency must be a strictly positive integer.");
    exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
  }

  return array($args, $count);
}

/**
 * Initialize script variables and perform general setup requirements.
 */
function simpletest_script_init($server_software) {
  global $args, $php;

  $host = 'localhost';
  $path = '';
  // Determine location of php command automatically, unless a command line argument is supplied.
  if (!empty($args['php'])) {
    $php = $args['php'];
  }
  elseif ($php_env = getenv('_')) {
    // '_' is an environment variable set by the shell. It contains the command that was executed.
    $php = $php_env;
  }
  elseif (defined('PHP_BINARY') && $php_env = PHP_BINARY) {
    // 'PHP_BINARY' specifies the PHP binary path during script execution. Available since PHP 5.4.
    $php = $php_env;
  }
  elseif ($sudo = getenv('SUDO_COMMAND')) {
    // 'SUDO_COMMAND' is an environment variable set by the sudo program.
    // Extract only the PHP interpreter, not the rest of the command.
    list($php, ) = explode(' ', $sudo, 2);
  }
  else {
    simpletest_script_print_error('Unable to automatically determine the path to the PHP interpreter. Supply the --php command line argument.');
    simpletest_script_help();
    exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
  }

  // Get URL from arguments.
  if (!empty($args['url'])) {
    $parsed_url = parse_url($args['url']);
    $host = $parsed_url['host'] . (isset($parsed_url['port']) ? ':' . $parsed_url['port'] : '');
    $path = isset($parsed_url['path']) ? $parsed_url['path'] : '';

    // If the passed URL schema is 'https' then setup the $_SERVER variables
    // properly so that testing will run under HTTPS.
    if ($parsed_url['scheme'] == 'https') {
      $_SERVER['HTTPS'] = 'on';
    }
  }

  $_SERVER['HTTP_HOST'] = $host;
  $_SERVER['REMOTE_ADDR'] = '127.0.0.1';
  $_SERVER['SERVER_ADDR'] = '127.0.0.1';
  $_SERVER['SERVER_SOFTWARE'] = $server_software;
  $_SERVER['SERVER_NAME'] = 'localhost';
  $_SERVER['REQUEST_URI'] = $path .'/';
  $_SERVER['REQUEST_METHOD'] = 'GET';
  $_SERVER['SCRIPT_NAME'] = $path .'/index.php';
  $_SERVER['PHP_SELF'] = $path .'/index.php';
  $_SERVER['HTTP_USER_AGENT'] = 'Drupal command line';

  if (!empty($_SERVER['HTTPS']) && $_SERVER['HTTPS'] == 'on') {
    // Ensure that any and all environment variables are changed to https://.
    foreach ($_SERVER as $key => $value) {
      // The first time this script runs $_SERVER['SERVER_SOFTWARE'] will be
      // NULL, so avoid errors from str_replace().
      if (!empty($_SERVER[$key])) {
        $_SERVER[$key] = str_replace('http://', 'https://', $_SERVER[$key]);
      }
    }
  }

  chdir(realpath(dirname(__FILE__) . '/..'));
  define('DRUPAL_ROOT', getcwd());
  require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
}

/**
 * Execute a batch of tests.
 */
function simpletest_script_execute_batch($test_id, $test_classes) {
  global $args;

  $total_status = SIMPLETEST_SCRIPT_EXIT_SUCCESS;

  // Multi-process execution.
  $children = array();
  while (!empty($test_classes) || !empty($children)) {
    while (count($children) < $args['concurrency']) {
      if (empty($test_classes)) {
        break;
      }

      // Fork a child process.
      $test_class = array_shift($test_classes);
      $command = simpletest_script_command($test_id, $test_class);
      $process = proc_open($command, array(), $pipes, NULL, NULL, array('bypass_shell' => TRUE));

      if (!is_resource($process)) {
        echo "Unable to fork test process. Aborting.\n";
        exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
      }

      // Register our new child.
      $children[] = array(
        'process' => $process,
        'class' => $test_class,
        'pipes' => $pipes,
      );
    }

    // Wait for children every 200ms.
    usleep(200000);

    // Check if some children finished.
    foreach ($children as $cid => $child) {
      $status = proc_get_status($child['process']);
      if (empty($status['running'])) {
        // The child exited, unregister it.
        proc_close($child['process']);
        if ($status['exitcode'] == SIMPLETEST_SCRIPT_EXIT_FAILURE) {
          if ($status['exitcode'] > $total_status) {
            $total_status = $status['exitcode'];
          }
        }
        elseif ($status['exitcode']) {
          $total_status = $status['exitcode'];
          echo 'FATAL ' . $test_class . ': test runner returned a non-zero error code (' . $status['exitcode'] . ').' . "\n";
        }

        // Remove this child.
        unset($children[$cid]);
      }
    }
  }
  return $total_status;
}

/**
 * Bootstrap Drupal and run a single test.
 */
function simpletest_script_run_one_test($test_id, $test_class) {
  global $args;

  try {
    // Bootstrap Drupal.
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

    simpletest_classloader_register();

    $test = new $test_class($test_id);
    $test->useSetupInstallationCache = !empty($args['cache']);
    $test->useSetupModulesCache = !empty($args['cache-modules']);
    $test->run();
    $info = $test->getInfo();

    $had_fails = (isset($test->results['#fail']) && $test->results['#fail'] > 0);
    $had_exceptions = (isset($test->results['#exception']) && $test->results['#exception'] > 0);
    $status = ($had_fails || $had_exceptions ? 'fail' : 'pass');
    simpletest_script_print($info['name'] . ' ' . _simpletest_format_summary_line($test->results) . "\n", simpletest_script_color_code($status));

    // Finished, kill this runner.
    if ($had_fails || $had_exceptions) {
      exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
    }
    exit(SIMPLETEST_SCRIPT_EXIT_SUCCESS);
  }
  catch (Exception $e) {
    echo (string) $e;
    exit(SIMPLETEST_SCRIPT_EXIT_EXCEPTION);
  }
}

/**
 * Return a command used to run a test in a separate process.
 *
 * @param $test_id
 *  The current test ID.
 * @param $test_class
 *  The name of the test class to run.
 */
function simpletest_script_command($test_id, $test_class) {
  global $args, $php;

  $command = escapeshellarg($php) . ' ' . escapeshellarg('./scripts/' . $args['script']) . ' --url ' . escapeshellarg($args['url']);
  if ($args['color']) {
    $command .= ' --color';
  }
  if ($args['cache-modules']) {
    $command .= ' --cache --cache-modules';
  }
  elseif ($args['cache']) {
    $command .= ' --cache';
  }

  $command .= " --php " . escapeshellarg($php) . " --test-id $test_id --execute-test " . escapeshellarg($test_class);
  return $command;
}

/**
 * Get list of tests based on arguments. If --all specified then
 * returns all available tests, otherwise reads list of tests.
 *
 * Will print error and exit if no valid tests were found.
 *
 * @return List of tests.
 */
function simpletest_script_get_test_list() {
  global $args, $all_tests, $groups;

  $test_list = array();
  if ($args['all']) {
    $test_list = $all_tests;
  }
  else {
    if ($args['class']) {
      // Check for valid class names.
      $test_list = array();
      foreach ($args['test_names'] as $test_class) {
        list($class_name, $method) = explode('::', $test_class, 2);
        if (class_exists($class_name)) {
          if (empty($method) || method_exists($class_name, $method)) {
            $test_list[] = $test_class;
          } else {
            $all_methods = get_class_methods($class_name);
            simpletest_script_print_error('Test method not found: ' . $test_class);
            simpletest_script_print_alternatives($method, $all_methods, 6);
            exit(1);
          }
        }
        else {
          $groups = simpletest_test_get_all();
          $all_classes = array();
          foreach ($groups as $group) {
            $all_classes = array_merge($all_classes, array_keys($group));
          }
          simpletest_script_print_error('Test class not found: ' . $class_name);
          simpletest_script_print_alternatives($class_name, $all_classes, 6);
          exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
        }
      }
    }
    elseif ($args['file']) {
      $files = array();
      foreach ($args['test_names'] as $file) {
        $files[drupal_realpath($file)] = 1;
      }

      // Check for valid class names.
      foreach ($all_tests as $class_name) {
        $refclass = new ReflectionClass($class_name);
        $file = $refclass->getFileName();
        if (isset($files[$file])) {
          $test_list[] = $class_name;
        }
      }
    }
    elseif ($args['directory']) {
      // Extract test case class names from specified directory.
      // Find all tests in the PSR-X structure; Drupal\$extension\Tests\*.php
      // Since we do not want to hard-code too many structural file/directory
      // assumptions about PSR-0/4 files and directories, we check for the
      // minimal conditions only; i.e., a '*.php' file that has '/Tests/' in
      // its path.
      // Ignore anything from third party vendors, and ignore template files used in tests.
      // And any api.php files.
      $ignore = array('nomask' => '/vendor|\.tpl\.php|\.api\.php/');
      $files = array();
      if ($args['directory'][0] === '/') {
        $directory = $args['directory'];
      }
      else {
        $directory = DRUPAL_ROOT . "/" . $args['directory'];
      }
      $file_list = file_scan_directory($directory, '/\.php|\.test$/', $ignore);
      foreach ($file_list as $file) {
        // '/Tests/' can be contained anywhere in the file's path (there can be
        // sub-directories below /Tests), but must be contained literally.
        // Case-insensitive to match all Simpletest and PHPUnit tests:
        //   ./lib/Drupal/foo/Tests/Bar/Baz.php
        //   ./foo/src/Tests/Bar/Baz.php
        //   ./foo/tests/Drupal/foo/Tests/FooTest.php
        //   ./foo/tests/src/FooTest.php
        // $file->filename doesn't give us a directory, so we use $file->uri
        // Strip the drupal root directory and trailing slash off the URI
        $filename = substr($file->uri, strlen(DRUPAL_ROOT)+1);
        if (stripos($filename, '/Tests/')) {
          $files[drupal_realpath($filename)] = 1;
        } else if (stripos($filename, '.test')){
          $files[drupal_realpath($filename)] = 1;
        }
      }

      // Check for valid class names.
      foreach ($all_tests as $class_name) {
        $refclass = new ReflectionClass($class_name);
        $classfile = $refclass->getFileName();
        if (isset($files[$classfile])) {
          $test_list[] = $class_name;
        }
      }
    }
    else {
      // Check for valid group names and get all valid classes in group.
      foreach ($args['test_names'] as $group_name) {
        if (isset($groups[$group_name])) {
          $test_list = array_merge($test_list, array_keys($groups[$group_name]));
        }
        else {
          simpletest_script_print_error('Test group not found: ' . $group_name);
          simpletest_script_print_alternatives($group_name, array_keys($groups));
          exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
        }
      }
    }
  }

  if (empty($test_list)) {
    simpletest_script_print_error('No valid tests were specified.');
    exit(SIMPLETEST_SCRIPT_EXIT_FAILURE);
  }
  return $test_list;
}

/**
 * Initialize the reporter.
 */
function simpletest_script_reporter_init() {
  global $args, $all_tests, $test_list, $results_map;

  $results_map = array(
    'pass' => 'Pass',
    'fail' => 'Fail',
    'exception' => 'Exception'
  );

  echo "\n";
  echo "Drupal test run\n";
  echo "---------------\n";
  echo "\n";

  // Tell the user about what tests are to be run.
  if ($args['all']) {
    echo "All tests will run.\n\n";
  }
  else {
    echo "Tests to be run:\n";
    foreach ($test_list as $test_name) {
      if (strpos($test_name, '::') > 0) {
        list($test_class, $method) = explode('::', $test_name, 2);
        $info = call_user_func(array($test_class, 'getInfo'));
      } else {
        $info = call_user_func(array($test_name, 'getInfo'));
      }
      echo " - " . $info['name'] . ' (' . $test_name . ')' . "\n";
    }
    echo "\n";
  }

  echo "Test run started:\n";
  echo " " . format_date($_SERVER['REQUEST_TIME'], 'long') . "\n";
  timer_start('run-tests');
  echo "\n";

  echo "Test summary\n";
  echo "------------\n";
  echo "\n";
}

/**
 * Display jUnit XML test results.
 */
function simpletest_script_reporter_write_xml_results() {
  global $args, $test_id, $results_map;

  $results = db_query("SELECT * FROM {simpletest} WHERE test_id = :test_id ORDER BY test_class, message_id", array(':test_id' => $test_id));

  $test_class = '';
  $xml_files = array();

  foreach ($results as $result) {
    if (isset($results_map[$result->status])) {
      if ($result->test_class != $test_class) {
        // We've moved onto a new class, so write the last classes results to a file:
        if (isset($xml_files[$test_class])) {
          file_put_contents($args['xml'] . '/' . $test_class . '.xml', $xml_files[$test_class]['doc']->saveXML());
          unset($xml_files[$test_class]);
        }
        $test_class = $result->test_class;
        if (!isset($xml_files[$test_class])) {
          $doc = new DomDocument('1.0');
          $root = $doc->createElement('testsuite');
          $root = $doc->appendChild($root);
          $xml_files[$test_class] = array('doc' => $doc, 'suite' => $root);
        }
      }

      // For convenience:
      $dom_document = &$xml_files[$test_class]['doc'];

      // Create the XML element for this test case:
      $case = $dom_document->createElement('testcase');
      $case->setAttribute('classname', $test_class);
      list($class, $name) = explode('->', $result->function, 2);
      $case->setAttribute('name', $name);

      // Passes get no further attention, but failures and exceptions get to add more detail:
      if ($result->status == 'fail') {
        $fail = $dom_document->createElement('failure');
        $fail->setAttribute('type', 'failure');
        $fail->setAttribute('message', $result->message_group);
        $text = $dom_document->createTextNode($result->message);
        $fail->appendChild($text);
        $case->appendChild($fail);
      }
      elseif ($result->status == 'exception') {
        // In the case of an exception the $result->function may not be a class
        // method so we record the full function name:
        $case->setAttribute('name', $result->function);

        $fail = $dom_document->createElement('error');
        $fail->setAttribute('type', 'exception');
        $fail->setAttribute('message', $result->message_group);
        $full_message = $result->message . "\n\nline: " . $result->line . "\nfile: " . $result->file;
        $text = $dom_document->createTextNode($full_message);
        $fail->appendChild($text);
        $case->appendChild($fail);
      }
      // Append the test case XML to the test suite:
      $xml_files[$test_class]['suite']->appendChild($case);
    }
  }
  // The last test case hasn't been saved to a file yet, so do that now:
  if (isset($xml_files[$test_class])) {
    file_put_contents($args['xml'] . '/' . $test_class . '.xml', $xml_files[$test_class]['doc']->saveXML());
    unset($xml_files[$test_class]);
  }
}

/**
 * Stop the test timer.
 */
function simpletest_script_reporter_timer_stop() {
  echo "\n";
  $end = timer_stop('run-tests');
  echo "Test run duration: " . format_interval($end['time'] / 1000);
  echo "\n\n";
}

/**
 * Display test results.
 */
function simpletest_script_reporter_display_results() {
  global $args, $test_id, $results_map;

  if ($args['verbose']) {
    // Report results.
    echo "Detailed test results\n";
    echo "---------------------\n";

    $results = db_query("SELECT * FROM {simpletest} WHERE test_id = :test_id ORDER BY test_class, message_id", array(':test_id' => $test_id));
    $test_class = '';
    foreach ($results as $result) {
      if (isset($results_map[$result->status]) && (!$args['fail-only'] || $result->status !== 'pass')) {
        if ($result->test_class != $test_class) {
          // Display test class every time results are for new test class.
          echo "\n\n---- $result->test_class ----\n\n\n";
          $test_class = $result->test_class;

          // Print table header.
          echo "Status    Group      Filename          Line Function                            \n";
          echo "--------------------------------------------------------------------------------\n";
        }

        simpletest_script_format_result($result);
      }
    }
  }
}

/**
 * Format the result so that it fits within the default 80 character
 * terminal size.
 *
 * @param $result The result object to format.
 */
function simpletest_script_format_result($result) {
  global $results_map, $color;

  $summary = sprintf("%-9.9s %-10.10s %-17.17s %4.4s %-35.35s\n",
    $results_map[$result->status], $result->message_group, basename($result->file), $result->line, $result->function);

  simpletest_script_print($summary, simpletest_script_color_code($result->status));

  $lines = explode("\n", wordwrap(trim(strip_tags($result->message)), 76));
  foreach ($lines as $line) {
    echo "    $line\n";
  }
}

/**
 * Print error message prefixed with "  ERROR: " and displayed in fail color
 * if color output is enabled.
 *
 * @param $message The message to print.
 */
function simpletest_script_print_error($message) {
  simpletest_script_print("  ERROR: $message\n", SIMPLETEST_SCRIPT_COLOR_FAIL);
}

/**
 * Print a message to the console, if color is enabled then the specified
 * color code will be used.
 *
 * @param $message The message to print.
 * @param $color_code The color code to use for coloring.
 */
function simpletest_script_print($message, $color_code) {
  global $args;
  if (!empty($args['color'])) {
    echo "\033[" . $color_code . "m" . $message . "\033[0m";
  }
  else {
    echo $message;
  }
}

/**
 * Get the color code associated with the specified status.
 *
 * @param $status The status string to get code for.
 * @return Color code.
 */
function simpletest_script_color_code($status) {
  switch ($status) {
    case 'pass':
      return SIMPLETEST_SCRIPT_COLOR_PASS;
    case 'fail':
      return SIMPLETEST_SCRIPT_COLOR_FAIL;
    case 'exception':
      return SIMPLETEST_SCRIPT_COLOR_EXCEPTION;
  }
  return 0; // Default formatting.
}

/**
 * Prints alternative test names.
 *
 * Searches the provided array of string values for close matches based on the
 * Levenshtein algorithm.
 *
 * @see http://php.net/manual/en/function.levenshtein.php
 *
 * @param string $string
 *   A string to test.
 * @param array $array
 *   A list of strings to search.
 * @param int $degree
 *   The matching strictness. Higher values return fewer matches. A value of
 *   4 means that the function will return strings from $array if the candidate
 *   string in $array would be identical to $string by changing 1/4 or fewer of
 *   its characters.
 */
function simpletest_script_print_alternatives($string, $array, $degree = 4) {
  $alternatives = array();
  foreach ($array as $item) {
    $lev = levenshtein($string, $item);
    if ($lev <= strlen($item) / $degree || FALSE !== strpos($string, $item)) {
      $alternatives[] = $item;
    }
  }
  if (!empty($alternatives)) {
    simpletest_script_print("  Did you mean?\n", SIMPLETEST_SCRIPT_COLOR_FAIL);
    foreach ($alternatives as $alternative) {
      simpletest_script_print("  - $alternative\n", SIMPLETEST_SCRIPT_COLOR_FAIL);
    }
  }
}
