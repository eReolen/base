<?php

/**
 * @file
 * Drush aliases.
 */

// Shut up phpcs.
$aliases = array();

$aliases['p01'] = array(
  'remote-host' => 'p01.ereolen.dk',
  'remote-user' => 'deploy',
  // Need to suppress the sshd Banner.
  'ssh-options' => "-o PasswordAuthentication=no -o LogLevel=Error",
);

$aliases['prod'] = array(
  'parent' => '@p01',
  'uri' => 'ereolen.dk',
  'root' => '/data/www/prod_ereolen_dk',
  'deployotron' => array(
    'branch' => 'master',
    'dump-dir' => '/data/backup/prod',
    // Updb clears the cache.
    'no-cc-all' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
    'newrelic-api-key' => '36372beaa3607d3b8082f6ed3d1ed986609d7359def9a47',
    'newrelic-app-name' => 'ereolen.dk',
    'post-online' => array(
      'sudo service varnish restart',
    ),
  ),
);

$aliases['stg'] = array(
  'parent' => '@p01',
  'uri' => 'stg.ereolen.dk',
  'root' => '/data/www/stg_ereolen_dk',
  'deployotron' => array(
    'branch' => 'develop',
    // Updb clears the cache.
    'no-cc-all' => TRUE,
    // Don't bother with db.
    'no-dump' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);

$aliases['dev'] = array(
  'parent' => '@p01',
  'uri' => 'dev.ereolen.dk',
  'root' => '/data/www/dev_ereolen_dk',
  'deployotron' => array(
    'branch' => 'develop',
    'no-dump' => TRUE,
    // Updb clears the cache.
    'no-cc-all' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);

$aliases['ego-prod'] = array(
  'parent' => '@p01',
  'uri' => 'ereolengo.dk',
  'root' => '/data/www/prod_ereolengo_dk',
  'deployotron' => array(
    'branch' => 'master',
    'dump-dir' => '/data/backup/ego-prod',
    // Updb clears the cache.
    'no-cc-all' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
    'newrelic-api-key' => '36372beaa3607d3b8082f6ed3d1ed986609d7359def9a47',
    'newrelic-app-name' => 'ereolengo.dk',
    'post-online' => array(
      'sudo service varnish restart',
    ),
  ),
);

// The server only allows certain IPs to log in, so we hack up an
// alias for the jump server here.
// $aliases['circle'] = $aliases['p01'];
// $aliases['circle']['ssh-options'] .= " -o ForwardAgent=yes -o 'ProxyCommand  ssh circleci@ding.reload.dk nc %h %p'";

// $aliases['circle-dev'] = $aliases['dev'];
// $aliases['circle-dev']['parent'] = '@circle';
