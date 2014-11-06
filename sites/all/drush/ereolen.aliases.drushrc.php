<?php

/**
 * @file
 * Drush aliases.
 */

// Shut up phpcs.
$aliases = array();

$aliases['test1404'] = array(
  'remote-host' => 'test1404.reload.dk',
  'remote-user' => 'reload',
);

$aliases['test'] = array(
  'parent' => '@test1404',
  'uri' => 'reload.dk',
  'root' => '/var/www/ereolen.test1404.reload.dk',
  'deployotron' => array(
    'branch' => 'master',
    'dump-dir' => '/home/reload/backup/ereolen',
    'restart-apache2' => TRUE,
    'no-offline' => TRUE,
    'no-updb' => TRUE,
    'no-cc-all' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);
