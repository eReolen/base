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
$conf['stage_file_proxy_origin'] = 'http://ereolen.dk';
$conf['stage_file_proxy_origin_dir'] = 'sites/default/files';
