
build-dependecies:
	@dce git --version >/dev/null || dce 'sh -c "apt update && apt install -y git patch unzip"'

ding: build-dependecies
	dce rm -rf profiles/ding2
	dce drush make ereolen.make . --shallow-clone --no-core --contrib-destination=profiles/ding2
	# Remove local patches and problematic .gitignores.
	dce rm profiles/ding2/*.patch profiles/ding2/.gitignore profiles/ding2/modules/ting/.gitignore

patches-dev: build-dependecies
	dce rm -rf profiles/ding2
	dce drush make ereolen.make . --working-copy --no-recursion --no-core --contrib-destination=profiles/ding2
	# Remove local patches and problematic .gitignores.
	dce rm profiles/ding2/*.patch
	cd profiles/ding2/ && fish -c 'toggleperm .' && git add *

statistics:
	dce drush sqlq "DELETE FROM queue WHERE name IN ('statistics_backlog_processing', 'statistics_processing');"
	dce drush php-eval 'reol_statistics_reset_all();reol_statistics_cron();'
	dce drush queue-list
	dce drush queue-run statistics_processing
	dce drush queue-run statistics_backlog_processing
	dce drush queue-list

dump-ereol:
	# Ensure that ssh doesn't mess with the dump because of host keys.
	dce drush @prod status
	dce drush @prod sql-dump --structure-tables-list=watchdog,cache,cache_menu | sed '/Warning: Using a password on the command line interface can be insecure/d' | gzip >private/docker/db-init/ereol/100-database.sql.gz

dump-ego:
	# Ensure that ssh doesn't mess with the dump because of host keys.
	dce drush @ego-prod status
	dce drush @ego-prod sql-dump --structure-tables-list=watchdog,cache,cache_menu | sed '/Warning: Using a password on the command line interface can be insecure/d' | gzip >private/docker/db-init/ego/100-database.sql.gz

sync-dev:
	ssh deploy@p01.ereolen.dk "cd /data/www/prod_ereolen_dk && \
	drush sql-dump --structure-tables-list=watchdog,cache,cache_menu >/tmp/dev-sync.sql && \
	cd /data/www/dev_ereolen_dk && \
	drush sql-drop -y && \
	drush sqlc < /tmp/dev-sync.sql && \
	rm /tmp/dev-sync.sql && \
	sudo -u www-data rsync -ar --del --progress --exclude=styles --exclude=ting/covers /data/www/prod_ereolen_dk/sites/default/files/ /data/www/dev_ereolen_dk/sites/default/files/ && \
	drush updb -y"
