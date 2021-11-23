<?php

/**
 * @file
 * Media_videotool/includes/MediaVideoToolBrowser.inc.
 *
 * Definition of MediaVideoToolBrowser.
 */

/**
 * Media browser plugin for displaying a specific view and display.
 */
class MediaVideoToolBrowser extends MediaBrowserPlugin {

  /**
   * Implements MediaBrowserPluginInterface::access().
   */
  public function access($account = NULL) {

    return file_entity_access('create', NULL, $account);
  }

  /**
   * Implements MediaBrowserPlugin::view().
   */
  public function view() {

    // Check if the user is able to add remote media.
    if (user_access('add media from remote sources')) {
      $build['form'] = drupal_get_form('media_videotool_add', $this->params['types'], $this->params['multiselect']);
      return $build;
    }
  }

}
