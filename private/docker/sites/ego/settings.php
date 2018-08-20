<?php
$databases = array(
  'default' => array(
    'default' => array(
      'driver' => 'mysql',
      'database' => getenv('MYSQL_DATABASE'),
      'username' => getenv('MYSQL_USER'),
      'password' => getenv('MYSQL_PASSWORD'),
      'host' => getenv('MYSQL_HOST'),
      'prefix' => '',
    ),
  ),
);

$conf['file_private_path'] = 'sites/default/private';
$conf['file_public_path'] = 'sites/default/files';
$conf['stage_file_proxy_origin'] = 'http://ereolengo.dk';
$conf['stage_file_proxy_origin_dir'] = 'sites/default/files';

// Set error_level to print all errors.
$conf['error_level'] = 2;

$conf['cache'] = FALSE;
$conf['block_cache'] = FALSE;
$conf['preprocess_css'] = FALSE;
$conf['preprocess_js'] = FALSE;

$conf['theme_debug'] = TRUE;
