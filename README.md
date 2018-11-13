ereolen.dk and ereolengo.dk
===========================

Ereolen.dk anno 2015 based on DDB CMS

## Patches

The project is base on DDB Core (https://github.com/ding2/ding2) with some changes 
which is tracked by patches in _sites/all/patches_.

### Drupal core patches

* http://drupal.org/files/issues/menu-get-item-rebuild-1232346-45.patch
* http://drupal.org/files/ssl-socket-transports-1879970-13.patch
* http://www.drupal.org/files/issues/1232416-autocomplete-for-drupal7x53.patch
* http://drupal.org/files/issues/translate_role_names-2205581-1.patch
 
Fix shortcut_set_save when set does not exist (https://www.drupal.org/node/1175700).
* https://www.drupal.org/files/fix-shortcut-set-save-1175700-10.patch


Add search_get_info() in search.module should include an _alter hook (https://www.drupal.org/node/1911276).
* https://www.drupal.org/files/search-info-alter-1911276--D7-16.patch

### Contrib patches

Add alter to strong-arm variables. Note this patch is part of the next release of the module.
* https://www.drupal.org/files/issues/2018-05-22/strongarm-2076543-import-export-value-alter-hooks-11.patch

### Ding2 patches

