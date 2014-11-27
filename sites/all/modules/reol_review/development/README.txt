Development tools
=================

This directory contais development tools to use in reol_review module.

If you wish to generate a .json file with 4 test-reviews, just execute `generateJson.php`

```bash
drush php-script generateJson.php > recommendations.json
```

It does not require Drupal Bootstrap, so this is just as good:
```bash
php generateJson.php > recommendations.json
```

To avoid having to wait for finding reviews at each cache clear, you can use this newly generated json file for review endpoint.
recommendations.json is pre-generated, and ready for use.

To use it, run:

```bash
drush vset reol_review_litteratursiden_feed "[site-url]/sites/all/modules/reol_review/development/recommendations.json"
```
