Installation
============

Install dependencies (skipping dev dependencies):

```
composer install --no-dev
```

Usage
------------

```
<?php
include_once __DIR__ . '/vendor/autoload.php';
include_once __DIR__ . '/Bpi/Sdk/Bpi.php';

$bpi = new Bpi(…);
$nodes = $bpi->searchNodes([]);
…
```

Running tests
-------------

Install dev dependencies:

```
composer install
```

Run all unit tests:

```
./vendor/bin/phpunit
```

Run web service tests:

```
BPI_WS_ENDPOINT=http://bpi-web-service.vm BPI_WS_AGENCY_ID=200100 BPI_WS_API_KEY=98c645c7e2882e7431037caa75ca5134 BPI_WS_SECRET_KEY=90eb05e4fbc327d3f455fb7576c493d3872fca7f ./vendor/bin/phpunit --stop-on-failure Tests/WebService/
```
