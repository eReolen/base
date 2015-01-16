Development notes
=================

By default, this module keeps results updated using cron. This is to avoid having the user wait for the (possibly) slow ting query.

For development environments, this is not preferrable, as clearing cache clears the results, and only cron will update them. The module checks a variable, for whether or not it is okay for the user to wait for the results. Use this for development like this:

```bash
drush vset reol_latest_user_allowed_to_wait TRUE
```

The module will then update results when there are none, even though the user might have to wait for the update.
