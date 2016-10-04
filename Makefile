ding:
	rm -rf profiles/ding2
	drush make ereolen.make . --shallow-clone --no-core --contrib-destination=profiles/ding2
# Remove local patches.
	rm profiles/ding2/*.patch

statistics:
	drush sqlq "DELETE FROM queue WHERE name IN ('statistics_backlog_processing', 'statistics_processing');"
	drush php-eval 'reol_statistics_reset_all();reol_statistics_cron();'
	drush queue-list
	drush queue-run statistics_processing
	drush queue-run statistics_backlog_processing
	drush queue-list
