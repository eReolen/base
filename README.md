ereolen.dk and ereolengo.dk
===========================

Ereolen.dk anno 2015 based on DDB CMS

## Patches

The project is base on DDB Core (https://github.com/ding2/ding2) with some changes
which is tracked by patches in _sites/all/patches_.

### Drupal core patches

* http://drupal.org/files/issues/menu-get-item-rebuild-1232346-45.patch
* ~~http://drupal.org/files/ssl-socket-transports-1879970-13.patch~~
* http://www.drupal.org/files/issues/1232416-autocomplete-for-drupal7x53.patch
* http://drupal.org/files/issues/translate_role_names-2205581-1.patch

Fix shortcut_set_save when set does not exist (https://www.drupal.org/node/1175700).
* https://www.drupal.org/files/fix-shortcut-set-save-1175700-10.patch

Add search_get_info() in search.module should include an _alter hook (https://www.drupal.org/node/1911276).
* https://www.drupal.org/files/search-info-alter-1911276--D7-16.patch

### Contrib patches

Add alter to strong-arm variables. Note this patch is part of the next release of the module.
* https://www.drupal.org/files/issues/2018-05-22/strongarm-2076543-import-export-value-alter-hooks-11.patch

Handle translated roles https://www.drupal.org/node/1744274
* https://www.drupal.org/files/secure_permissions-duplicate_role_exception-1744274-4.patch

### Ding2 patches

* Change BPI node type to use (bpi-change-node-type.patch)
* Don't remove no expire loans for the loans list (ding-user-loan-list.patch)
* Revert ding popup back from DDB Core to use swipe etc. (ding_popup_revert.patch)
* Use hook_init to redirect user to login form (ding_user-redirect.patch)
* Disable dependencies for removed core modules (disable_modules_dependencies.patch)
* Override material details - should be move into alters in base (feature_material_overrride.patch)
* Update i18n module (i18n.patch)
* Roll-back auto complete to open-suggestions (opensearch-autocomplete.patch)
* Removed the "Other formats" entity button (remove-other-formats-button.patch)
* Remove auto-logout config (remove_autologout_configuration.patch)
* Ensure infomedia field file is loaded (ting_infomedia-missing-include.patch)
* Change subject link rendering on ting object view (ting_material_details-subjects-view.patch)
* Change the way number of results are displayed (ting_search_result.patch)
* Update the varnish module (update-varnish.patch)
* Enabled 'user/%/view' path (user-menu.patch)
* Run attached behaviours as in DDB core - carousle-attach.patch
* Fixed "Undefined index" warnings (ding-loan-loans.patch)
* Fixed offset in carousel search (ting_search_carousel.patch)
* Fix missing record error title in ting references (error-missing-record.patch)
* Allow empty value in bpi field mapping (bpi-mappings.patch)
* Remove bpi settings from feature (ding_base-bpi-settings.patch)
* Enable fulltext render static cache reset (sites/all/patches/ting_fulltext_cache_reset.patch)
* Fix rotation origin of search spinner (sites/all/patches/ting_search_overlay.patch)
* Allow lazy loading of covers (sites/all/patches/ting_covers.patch)

# Docker
This repository comes with an `docker-compose.yml` to run the stack in 
docker and a makefile to ease the usage. The setup exposes access to
http (nginx and varnish) and mysql.

The service labels in the compose file is the ones that should be used
to address the containers. So in `settings.local.php` these should be
used when setting up database etc.

```php
$databases['default']['default'] = array(
 'database' => 'db',
 'username' => 'db',
 'password' => 'db',
 'host' => 'mariadb',
 'port' => '',
 'driver' => 'mysql',
 'prefix' => '',
);
```

The exposed ports can always be accessed by the address `0.0.0.0:PORT`.

__Note__: the repositry contains a `.docker` folder that holds the nginx and varnish configuration. 

## Commands 

* Start up the container stack (nginx, php7.0, memcached and varnish)

```sh
make up
```
or
```sh
docker-compose -p ereolen up -d
```

* Access the site.

```sh
make open
```
or
```sh
docker-compose -p ereolen port varnishd 80
```

* Stop the containers.

```sh
make stop
```
or
```sh
docker-compose -p ereolen stop
```

* Remove it all.

```sh
make clean
```
or
```sh
docker-compose -p ereolen rm
```

* Access MySQL by showing the port number for mysql.

```sh
make mysql
```
or
```sh
docker-compose -p ereolen port mariadb 3306
```

* Using drush

```sh
docker-compose run --rm drush [command]
```


# Building themes

```sh
docker-compose run --rm node bash -c "cd /app/sites/all/themes/orwell/ && npm install"
docker-compose run --rm node bash -c "cd /app/sites/all/themes/orwell/ && node_modules/.bin/gulp sass"
```

```sh
docker-compose run --rm node bash -c "cd /app/sites/all/themes/wille/ && npm install"
docker-compose run --rm node bash -c "cd /app/sites/all/themes/wille/ && node_modules/.bin/gulp sass"
```
