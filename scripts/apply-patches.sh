#!/usr/bin/env bash
script_dir=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
project_dir=$(cd "$(dirname "$script_dir")" && pwd)

cd "$project_dir" || exit

# Apply core patches (cf. README.md#patches)
core_patches=(
  # @see https://www.drupal.org/node/1232346 (does not apply cleanly)
  "https://drupal.org/files/issues/menu-get-item-rebuild-1232346-45.patch"
  # @see https://www.drupal.org/node/1232416 (does not apply cleanly)
  "https://www.drupal.org/files/issues/1232416-autocomplete-for-drupal7x53.patch"
  # @see https://www.drupal.org/node/2205581 (does not apply cleanly)
  "https://drupal.org/files/issues/translate_role_names-2205581-1.patch"
  # @see https://www.drupal.org/node/1079628 (does not apply cleanly)
  "https://www.drupal.org/files/issues/programatically_added-1079628-29-d7.patch"
  # @see https://www.drupal.org/node/1175700 (applies cleanly)
  "https://www.drupal.org/files/issues/1175700-shortcut-set-save-fix-set-name-api_1.patch"
  # @see https://www.drupal.org/node/1911276 (does not apply cleanly)
  "https://www.drupal.org/files/search-info-alter-1911276--D7-16.patch"
  # @see https://www.drupal.org/node/3292211 (applies cleanly)
  "https://www.drupal.org/files/issues/2022-06-23/update_fieldset-legend__collapsable-3292211-3.patch"
  "file://$PWD/sites/all/patches/number.patch"
)

for patch in "${core_patches[@]}"; do
  echo "$patch"
  curl --silent --location "$patch" | patch --strip=1
done
