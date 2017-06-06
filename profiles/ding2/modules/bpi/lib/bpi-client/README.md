Installation
============

    $ composer install

Composer
------------

    $ curl -sS https://getcomposer.org/installer | php

This installer script will simply check some php.ini settings, warn you if they are set incorrectly, and then download the latest composer.phar in the current directory.

Usage
------------

    <?php
    include_once __DIR__ . '/vendor/autoload.php';
    new Bpi\Sdk\Document(new Goutte\Client());
    ?>
