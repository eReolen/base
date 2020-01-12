# E-reolen app feeds

This module exposes e-reolen content as json data.

See
https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.12un1qdppa6x
for details on feed structure.

## Installation

Install the `reol_app_feeds` module and go to
[/admin/config/ereolen/reol_app_feeds](/admin/config/ereolen/reol_app_feeds)
to configure the feeds.

**NOTE**: After installing this module (but not before!) you must uninstall the
`ereol_app_feeds` module.

## Endpoints

* [/app/feed/frontpage](/app/feed/frontpage)

  Frontpage feed.

* [/app/feed/themes](/app/feed/themes)

  Theme feed.

* [/app/feed/categories](/app/feed/categories)

  Categories feed.
