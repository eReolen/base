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

dump-ereol:
	# Ensure that ssh doesn't mess with the dump because of host keys.
	dce drush @prod status
	dce drush @prod sql-dump --structure-tables-list=watchdog,cache,cache_menu | sed '/Warning: Using a password on the command line interface can be insecure/d' | gzip >private/docker/db-init/ereol/100-database.sql.gz

dump-ego:
	# Ensure that ssh doesn't mess with the dump because of host keys.
	dce drush @ego-prod status
	dce drush @ego-prod sql-dump --structure-tables-list=watchdog,cache,cache_menu | sed '/Warning: Using a password on the command line interface can be insecure/d' | gzip >private/docker/db-init/ego/100-database.sql.gz
