ding:
	rm -rf profiles/ding2
	drush make ereolen.make . --shallow-clone --no-core --contrib-destination=profiles/ding2
# Remove local patches.
	rm profiles/ding2/*.patch
