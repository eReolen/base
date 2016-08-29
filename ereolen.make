core = 7.x
api = 2

; Get the profile, which will contain the next makefile.
projects[ding2][type] = "profile"
projects[ding2][download][type] = "git"
projects[ding2][download][url] = "git@github.com:ding2/ding2.git"
projects[ding2][download][tag] = "7.x-2.4.4"

; Upgrade media and media_youtube.
projects[ding2][patch][] = "sites/all/patches/update-media.patch"

; Upgrade varnish.
projects[ding2][patch][] = "sites/all/patches/update-varnish.patch"

; Add width: auto, as width in standard theme is set elsewhere.
projects[ding2][patch][] = "sites/all/patches/ding_popup-width.patch"

; Set resizable false, as standard theme does not support it anyway.
projects[ding2][patch][] = "sites/all/patches/ding_popup-resizable.patch"

; Add option for adding class on modal.
projects[ding2][patch][] = "sites/all/patches/ding_popup-add-class.patch"

; Fix ting zero cache lifetime so debugging is easier.
; https://github.com/ding2/ding2/pull/139
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/139.patch"

; Fix the ting CTools argument plugin.
; https://github.com/ding2/ding2/pull/140
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/140.patch"

; Add custom type labels.
; https://github.com/ding2/ding2/pull/141
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/141.patch"

; Allow provider to fiddle with user login form, so we can add the library selector.
; https://github.com/ding2/ding2/pull/142
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/142.patch"

; Backport generic search field.
; based on https://github.com/ding2/ding2/pull/143
projects[ding2][patch][] = "sites/all/patches/ting_material_details-generic-search.patch"

; Add loans and reservations to their list form, so we can catch them in form_alter.
; https://github.com/ding2/ding2/pull/144
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/144.patch"

; Patch to use our node type.
projects[ding2][patch][] = "sites/all/patches/bpi-change-node-type.patch"

; Fix facet browser to not duplicate "show more" links when the logon popup shows.
; https://github.com/ding2/ding2/pull/215
projects[ding2][patch][] = "https://patch-diff.githubusercontent.com/raw/ding2/ding2/pull/215.patch"

; Pluggable covers and carousel update. Applied manueally.
; https://github.com/ding2/ding2/pull/196
projects[ding2][patch][] = "sites/all/patches/ting_covers.patch"

; Latest fixes to the above.
; based on https://github.com/ding2/ding2/pull/196
projects[ding2][patch][] = "sites/all/patches/ting_covers-2.patch"

; Hand applied footer icon fix.
; https://github.com/ding2/ding2/pull/218
projects[ding2][patch][] = "sites/all/patches/footer-icons.patch"

; Update admin_vievs.
projects[ding2][patch][] = "sites/all/patches/admin_views.patch"

; Update entity, features, field_group, jquery_update, og, og_menu, scheduler and views.
projects[ding2][patch][] = "sites/all/patches/module-updates.patch"

; Use better secure_permissions patch.
projects[ding2][patch][] = "sites/all/patches/secure_permissions.patch"

; Update i18n module.
projects[ding2][patch][] = "sites/all/patches/i18n.patch"

; Unload popup content on close.
; based on https://github.com/ding2/ding2/pull/274
projects[ding2][patch][] = "sites/all/patches/popup-unload.patch"

; Add support for authentication for the datawell
; based on https://github.com/ding2/ding2/pull/219
projects[ding2][patch][] = "sites/all/patches/ting-auth.patch"

; Slick for search carousel.
; based on https://github.com/ding2/ding2/pull/271
; without changes to ddbasic
projects[ding2][patch][] = "sites/all/patches/slick-carousel.patch"
; Part two.
projects[ding2][patch][] = "sites/all/patches/slick-carousel-2.patch"

; Disable sort used message.
projects[ding2][patch][] = "sites/all/patches/disable-message.patch"
