This module adds a hook which alerts other modules when the site is switched
into maintenance mode.

This means modules can add features such as:
- Disabling Nagios alerts when the site is in maintenance mode.
- Disabling cron workers when the site is in maintenance mode.
- Changing external reverse-proxies to disable access to the site during
  maintenance.
- Alerting a list of users when the site is switched to or from maintenance
  mode.

This module integrates with the Drupal administration page at
admin/config/development/maintenance, and with Drush when the variable
'site_maintenance' is changed.  If the usual methods to switch to maintenance
mode are avoided and the normal API bypassed (for example, by setting
maintenance mode through a direct database query), this feature will not work
(but can be implemented by other modules through invoking
hook_change_maintenance_mode).
