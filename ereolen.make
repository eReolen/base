core = 7.x
api = 2

; Core definition copied from profiles/ding2/drupal.make.
; This is taken from the master branch of ding2 to get the latest security updates.
projects[drupal][type] = core
projects[drupal][version] = 7.57
projects[drupal][patch][] = "http://drupal.org/files/issues/menu-get-item-rebuild-1232346-45.patch"
projects[drupal][patch][] = "http://drupal.org/files/ssl-socket-transports-1879970-13.patch"
projects[drupal][patch][] = "http://www.drupal.org/files/issues/1232416-autocomplete-for-drupal7x53.patch"
projects[drupal][patch][] = "http://drupal.org/files/issues/translate_role_names-2205581-1.patch"
; Our own patches
; Fix shortcut_set_save when set does not exist.
; https://www.drupal.org/node/1175700
projects[drupal][patch][] = "https://www.drupal.org/files/fix-shortcut-set-save-1175700-10.patch"
; search_get_info() in search.module should include an _alter hook.
; https://www.drupal.org/node/1911276
projects[drupal][patch][] = "https://www.drupal.org/files/search-info-alter-1911276--D7-16.patch"

; Get the profile, which will contain the next makefile.
projects[ding2][type] = "profile"
projects[ding2][download][type] = "git"
projects[ding2][download][url] = "git@github.com:ding2/ding2.git"
projects[ding2][download][tag] = "7.x-3.0.2"

; Upgrade media and media_youtube.
projects[ding2][patch][] = "sites/all/patches/update-media.patch"

; Upgrade varnish.
projects[ding2][patch][] = "sites/all/patches/update-varnish.patch"

; Add custom type labels.
; https://github.com/ding2/ding2/pull/141
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/141.patch"

; Patch to use our node type.
projects[ding2][patch][] = "sites/all/patches/bpi-change-node-type.patch"

; Update field_group.
; Adapted from https://github.com/ding2/ding2/commit/d88c068d3d
projects[ding2][patch][] = "sites/all/patches/update-field_group.patch"

; Update entity, features, jquery_update, og, og_menu, scheduler and views.
projects[ding2][patch][] = "sites/all/patches/module-updates.patch"

; Use better secure_permissions patch.
projects[ding2][patch][] = "sites/all/patches/secure_permissions.patch"

; Update i18n module.
projects[ding2][patch][] = "sites/all/patches/i18n.patch"

; Unload popup content on close.
; https://github.com/ding2/ding2/pull/274
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/274.patch"

; ; Add width: auto, as width in standard theme is set elsewhere.
projects[ding2][patch][] = "sites/all/patches/ding_popup-width.patch"

; Set resizable false, as standard theme does not support it anyway.
projects[ding2][patch][] = "sites/all/patches/ding_popup-resizable.patch"

; Add option for adding class on modal.
projects[ding2][patch][] = "sites/all/patches/ding_popup-add-class.patch"

; Slick for search carousel.
; based on a squashed version of https://github.com/ding2/ding2/pull/614
projects[ding2][patch][] = "sites/all/patches/slick-carousel.patch"

; Disable sort used message.
projects[ding2][patch][] = "sites/all/patches/disable-message.patch"

; Fix dings /user redirect bug.
projects[ding2][patch][] = "sites/all/patches/ding_user-redirect.patch"

; Adjust ddbasic to the new field_group 1.5.
projects[ding2][patch][] = "sites/all/patches/ddbasic-field_group.patch"

; Patch oembed to not produce fatal error.
; https://github.com/ding2/ding2/pull/269
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/269.patch"

; Make P2 not mess up ting object display.
; https://github.com/ding2/ding2/pull/606
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/606.patch"

; Make ting_carusel compatible with the latest field_group.
; https://github.com/ding2/ding2/pull/619
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/619.patch"

; And another cover fix.
; based on https://github.com/ding2/ding2/pull/196
projects[ding2][patch][] = "sites/all/patches/ting_covers-4.patch"

; Fix up the type fetching in ting admin pages.
; based on https://github.com/ding2/ding2/pull/851
projects[ding2][patch][] = "sites/all/patches/remove-random.patch"

; Fixup menu_block so the content_type works.
; https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/880.patch"

; Fix cover loading on iPhone.
; https://github.com/ding2/ding2/pull/904
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/904.patch"

; Add ding_webtrekk module.
projects[ding2][patch][] = "sites/all/patches/ding_webtrekk.patch"

; Fix p2 JS errors.
projects[ding2][patch][] = "https://github.com/ding2/ding2/commit/00e8a6d7cff318e758bf402cdbc8491a73c50ebd.patch"
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/1035.patch"
