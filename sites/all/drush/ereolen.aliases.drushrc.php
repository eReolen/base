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
  'uri' => 'prod.ereolen.dk',
  'root' => '/data/www/prod_ereolen_dk',
  'deployotron' => array(
    'branch' => 'develop',
    'dump-dir' => '/home/deploy/backup/prod',
    'restart-apache2' => TRUE,
    // Updb clears the cache.
    'no-cc-all' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);

$aliases['stg'] = array(
  'parent' => '@p01',
  'uri' => 'stg.ereolen.dk',
  'root' => '/data/www/stg_ereolen_dk',
  'deployotron' => array(
    'branch' => 'develop',
    'dump-dir' => '/home/deploy/backup/stg',
    'restart-apache2' => TRUE,
    // Updb clears the cache.
    'no-cc-all' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);

$aliases['dev'] = array(
  'parent' => '@p01',
  'uri' => 'dev.ereolen.dk',
  'root' => '/data/www/dev_ereolen_dk',
  'deployotron' => array(
    'branch' => 'develop',
    'dump-dir' => '/home/deploy/backup/dev',
    'restart-apache2' => TRUE,
    // Updb clears the cache.
    'no-cc-all' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);

$aliases['test1404'] = array(
  'remote-host' => 'test1404.reload.dk',
  'remote-user' => 'reload',
);

$aliases['test'] = array(
  'parent' => '@test1404',
  'uri' => 'ereolen.test1404.reload.dk',
  'root' => '/var/www/ereolen.test1404.reload.dk',
  'deployotron' => array(
    'branch' => 'develop',
    'dump-dir' => '/home/reload/backup/ereolen',
    'restart-apache2' => TRUE,
    'no-offline' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);

$aliases['test-test'] = array(
  'parent' => '@test1404',
  'uri' => 'ereolen-test.test1404.reload.dk',
  'root' => '/var/www/ereolen-test.test1404.reload.dk',
  'deployotron' => array(
    'branch' => 'develop',
    'dump-dir' => '/home/reload/backup/ereolen',
    'restart-apache2' => TRUE,
    'no-offline' => TRUE,
    'flowdock-token' => '2665ccaf6a5e3a4939c06a10adab861f',
  ),
);

// The server only allows certain IPs to log in, so we hack up an
// alias for the jump server here.
$aliases['circle'] = $aliases['p01'];
$aliases['circle']['ssh-options'] .= " -o ForwardAgent=yes -o 'ProxyCommand  ssh circleci@ding.reload.dk nc %h %p'";

$aliases['circle-dev'] = $aliases['dev'];
$aliases['circle-dev']['parent'] = '@circle';
