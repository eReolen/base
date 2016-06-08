<?php
/**
 * @file
 * breol_video.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function breol_video_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-breol_video-field_breol_video'
  $field_instances['node-breol_video-field_breol_video'] = array(
    'bundle' => 'breol_video',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'image',
        'settings' => array(
          'image_link' => '',
          'image_style' => '',
        ),
        'type' => 'image',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'teaser_medium' => array(
        'label' => 'hidden',
        'module' => 'file_entity',
        'settings' => array(
          'file_view_mode' => 'teaser_medium',
        ),
        'type' => 'file_rendered',
        'weight' => 0,
      ),
      'teaser_small' => array(
        'label' => 'hidden',
        'module' => 'file_entity',
        'settings' => array(
          'file_view_mode' => 'teaser_small',
        ),
        'type' => 'file_rendered',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_breol_video',
    'label' => 'Video',
    'required' => 1,
    'settings' => array(
      'alt_field' => 0,
      'default_image' => 0,
      'file_directory' => '',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'media',
      'settings' => array(
        'allowed_schemes' => array(
          'private' => 0,
          'public' => 'public',
          'vimeo' => 'vimeo',
          'youtube' => 'youtube',
        ),
        'allowed_types' => array(
          'audio' => 0,
          'document' => 0,
          'image' => 0,
          'video' => 'video',
        ),
        'browser_plugins' => array(
          'ding_content' => 0,
          'media_default--media_browser_1' => 0,
          'media_default--media_browser_my_files' => 0,
          'media_internet' => 'media_internet',
          'upload' => 0,
        ),
      ),
      'type' => 'media_generic',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Video');

  return $field_instances;
}
