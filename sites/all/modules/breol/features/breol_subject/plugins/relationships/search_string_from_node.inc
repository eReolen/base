<?php

/**
 * @file
 * Plugin to provide an relationship handler for search string from node.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Search string from node'),
  'keyword' => 'string',
  'description' => t('Adds the node search string.'),
  'required context' => new ctools_context_required(t('Node'), 'node'),
  'context' => 'breol_subject_search_string_from_node_context',
);

/**
 * Return a new context based on an existing context.
 */
function breol_subject_search_string_from_node_context($context, $conf) {
  // If unset it wants a generic, unfilled context, which is just NULL.
  if (!empty($context->data)) {
    $wrapper = entity_metadata_wrapper('node', $context->data);
    if (isset($wrapper->field_search_string) &&
      $string = $wrapper->field_search_string->value()) {
      return ctools_context_create('string', $string);
    }
  }
  return ctools_context_create_empty('string', NULL);
}
