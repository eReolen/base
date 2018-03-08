
SKIP_TABLES ?= watchdog,cache,cache_menu
FROM ?= prod

.PHONY: default
default: all

build-dependecies:
	@dce git --version >/dev/null || dce 'sh -c "apt update && apt install -y git patch unzip"'

ding: build-dependecies
	dce rm -rf profiles/ding2
	dce drush make ereolen.make . --shallow-clone --no-core --contrib-destination=profiles/ding2
	# Remove local patches and problematic .gitignores.
	dce rm profiles/ding2/*.patch profiles/ding2/.gitignore profiles/ding2/modules/ting/.gitignore profiles/ding2/modules/bpi/.gitignore

all: build-dependecies
	dce drush make ereolen.make new-core
	# Update the standard files in sites/.
	dce rsync -r new-core/sites/ ./sites/
	# Don't touch sites folder when deleting old files.
	dce rm -rf new-core/sites/
	# Now delete all top-level stuff.
	dce ls new-core | xargs rm -rf
	# Copy in new files.
	dce rsync -r new-core/ ./
	# Remove local patches and problematic .gitignores.
	dce rm profiles/ding2/*.patch profiles/ding2/.gitignore profiles/ding2/modules/ting/.gitignore profiles/ding2/modules/bpi/.gitignore
	# And remave build directory.
	dce rm -rf new-core

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
	dce drush @$(FROM) status
	dce drush @$(FROM) sql-dump --structure-tables-list=$(SKIP_TABLES) | sed '/Warning: Using a password on the command line interface can be insecure/d' | gzip >private/docker/db-init/ereol/100-database.sql.gz

import-ereol: 
	dce -c ereol drush sql-drop -y
	(zcat private/docker/db-init/ereol/100-database.sql.gz ; cat private/docker/db-init/ereol/900-sanitize.sql) | dce drush sqlc

dump-ego:
	# Ensure that ssh doesn't mess with the dump because of host keys.
	dce drush @ego-$(FROM) status
	dce drush @ego-$(FROM) sql-dump --structure-tables-list=$(SKIP_TABLES) | sed '/Warning: Using a password on the command line interface can be insecure/d' | gzip >private/docker/db-init/ego/100-database.sql.gz

import-ego:
	dce -c ego drush sql-drop -y
	(zcat private/docker/db-init/ego/100-database.sql.gz ; cat private/docker/db-init/ego/900-sanitize.sql) | dce drush sqlc

sync-dev:
	ssh deploy@p01.ereolen.dk "cd /data/www/prod_ereolen_dk && \
	drush sql-dump --structure-tables-list=watchdog,cache,cache_menu >/tmp/dev-sync.sql && \
	cd /data/www/dev_ereolen_dk && \
	drush sql-drop -y && \
	drush sqlc < /tmp/dev-sync.sql && \
	rm /tmp/dev-sync.sql && \
	sudo -u www-data rsync -ar --del --progress --exclude=styles --exclude=ting/covers /data/www/prod_ereolen_dk/sites/default/files/ /data/www/dev_ereolen_dk/sites/default/files/ && \
	drush updb -y"

sync-ego-dev:
	ssh deploy@p01.ereolen.dk "cd /data/www/prod_ereolengo_dk && \
	drush sql-dump --structure-tables-list=watchdog,cache,cache_menu >/tmp/ego-dev-sync.sql && \
	cd /data/www/dev_ereolengo_dk && \
	drush sql-drop -y && \
	drush sqlc < /tmp/ego-dev-sync.sql && \
	rm /tmp/ego-dev-sync.sql && \
	sudo -u www-data rsync -ar --del --progress --exclude=styles --exclude=ting/covers /data/www/prod_ereolengo_dk/sites/default/files/ /data/www/dev_ereolengo_dk/sites/default/files/ && \
	drush updb -y"

sync-ego-stg:
	ssh deploy@p01.ereolen.dk "cd /data/www/prod_ereolengo_dk && \
	drush sql-dump --structure-tables-list=watchdog,cache,cache_menu >/tmp/ego-stg-sync.sql && \
	cd /data/www/stg_ereolengo_dk && \
	drush sql-drop -y && \
	drush sqlc < /tmp/ego-stg-sync.sql && \
	rm /tmp/ego-stg-sync.sql && \
	sudo -u www-data rsync -ar --del --progress --exclude=styles --exclude=ting/covers /data/www/prod_ereolengo_dk/sites/default/files/ /data/www/stg_ereolengo_dk/sites/default/files/ && \
	drush updb -y"
