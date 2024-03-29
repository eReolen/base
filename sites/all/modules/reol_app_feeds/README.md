# E-reolen app feeds

This module exposes e-reolen content as json data.

See [Nye eReolen Feed og
typer](https://docs.google.com/document/d/1lJ3VPAJf7DAbBWAQclRHfcltzZefUG3iGCec-z97KlA/edit?ts=5c4ef9d5#heading=h.12un1qdppa6x)
for details on feed structure.

## Installation

Install the `reol_app_feeds` module and go to
[/admin/config/ereolen/reol_app_feeds](/admin/config/ereolen/reol_app_feeds)
to configure the feeds.

## Generating feed content

For performance reasons the feed content must be generated by running the
`reol-app-feeds-generate` command before it can be delivered (cf.
[Delivering feed content](#delivering-feed-content)).

Example cron expressions:

```sh
# Generate categories feed hourly.
0 * * * * /usr/local/bin/drush --uri=https://ereolengo.dk --root=/data/www/ereolengo_dk/htdocs reol-app-feeds-generate categories > /dev/null 2>&1
# Generate overdrive mapping feed daily.
0 2 * * * /usr/local/bin/drush --uri=https://ereolengo.dk --root=/data/www/ereolengo_dk/htdocs reol-app-feeds-generate overdrive/mapping > /dev/null 2>&1
```

## Delivering feed content

The following endpoints deliver JSON feed content. If the content for a feed
does not exist, the feed endpoint will return a `404 Not Found` response.

* [/app/feed/v2/frontpage](/app/feed/v2/frontpage)

  Frontpage feed.

* [/app/feed/v2/themes](/app/feed/v2/themes)

  Theme feed.

* [/app/feed/v2/categories](/app/feed/v2/categories)

  Categories feed.

* [/app/feed/v2/overdrive/mapping](/app/feed/v2/overdrive/mapping)

  Overdrive mapping.
