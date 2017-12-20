core = 7.x
api = 2

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
