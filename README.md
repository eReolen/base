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

### Ding2 patches

* Upgrade media and media_youtube -> update-media.patch
* Upgrade varnish -> update-varnish.patch
* Add custom type labels -> https://github.com/ding2/ding2/pull/141
* BPI patch to use our node type -> bpi-change-node-type.patch
* Update field_group. Adapted from https://github.com/ding2/ding2/commit/d88c068d3d -> update-field_group.patch
* Update entity, features, jquery_update, og, og_menu, scheduler and views -> module-updates.patch
* Use better secure_permissions patch -> secure_permissions.patch
* Update i18n module -> i18n.patch
* Unload popup content on close -> https://github.com/ding2/ding2/pull/274
* Add width: auto, as width in standard theme is set elsewhere -> ding_popup-width.patch
* Set resizable false, as standard theme does not support it anyway -> ding_popup-resizable.patch
* Add option for adding class on modal -> ding_popup-add-class.patch
* Slick for search carousel; based on a squashed version of https://github.com/ding2/ding2/pull/614 -> slick-carousel.patch
* Disable sort used message -> disable-message.patch
* Fix dings /user redirect bug -> ding_user-redirect.patch
* Adjust ddbasic to the new field_group 1.5 -> ddbasic-field_group.patch
* Patch oembed to not produce fatal error -> https://github.com/ding2/ding2/pull/269
* Make P2 not mess up ting object display -> https://github.com/ding2/ding2/pull/606
* Make ting_carusel compatible with the latest field_group -> https://github.com/ding2/ding2/pull/619
* And another cover fix based on https://github.com/ding2/ding2/pull/196 -> ting_covers-4.patch
* Fix up the type fetching in ting admin pages based on https://github.com/ding2/ding2/pull/851 -> remove-random.patch
* Fixup menu_block so the content_type works -> https://github.com/ding2/ding2/pull/880
* Fix cover loading on iPhone -> https://github.com/ding2/ding2/pull/904
* Add ding_webtrekk module -> ding_webtrekk.patch
* Fix P2 JS errors -> https://github.com/ding2/ding2/commit/00e8a6d7cff318e758bf402cdbc8491a73c50ebd.patch
* Fix P2 JS errors -> https://github.com/ding2/ding2/pull/1035
* Remove auto logout modeule -> remove_autologout_configuration.patch
