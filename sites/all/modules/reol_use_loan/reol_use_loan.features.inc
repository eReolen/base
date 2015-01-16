<?php
/**
 * @file
 * reol_use_loan.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function reol_use_loan_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
