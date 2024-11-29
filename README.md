# ereolen.dk and ereolengo.dk

``` shell
git clone --branch feature/next-debug https://github.com/ereolen/base ereolengo
cd ereolengo
git clone https://github.com/ereolen/ereolengo sites/all/modules/breol
cat > sites/default/settings.local.php <<'EOF'
<?php

$databases['default']['default'] = [
 'database' => getenv('DATABASE_DATABASE') ?: 'db',
 'username' => getenv('DATABASE_USERNAME') ?: 'db',
 'password' => getenv('DATABASE_PASSWORD') ?: 'db',
 'host' => getenv('DATABASE_HOST') ?: 'mariadb',
 'port' => getenv('DATABASE_PORT') ?: '',
 'driver' => getenv('DATABASE_DRIVER') ?: 'mysql',
 'header' => '',
];

// Enable logging (cf. sites/all/modules/publizon/lib/PublizonClient.class.inc)
$conf['publizon_logging'] = TRUE;
EOF
```

Start the show:

``` shell name=site-reset
docker compose pull
docker compose up --detach
docker compose exec phpfpm composer install
# Load database
docker compose exec phpfpm vendor/bin/drush sql:create --yes
docker compose exec --no-TTY phpfpm vendor/bin/drush sql:cli < ereolengo.sql
open $(docker compose exec phpfpm vendor/bin/drush --uri="https://0.0.0.0:3000" user:login)
```

## Xdebug

``` shell
PHP_XDEBUG_MODE=debug PHP_XDEBUG_WITH_REQUEST=yes docker compose up
```
