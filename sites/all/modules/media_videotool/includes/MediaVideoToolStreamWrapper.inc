<?php

/**
 * @file
 * Media_videotool/includes/MediaVideoToolStreamWrapper.inc.
 *
 *  Create a VideoTool Stream Wrapper class for the Media/Resource module.
 */

/**
 * Media Video Tool Stream Wrapper.
 *
 * Create an instance like this:
 *  $videotool = new MediaVideoToolStreamWrapper('videotool://v/[video-code]');
 */
class MediaVideoToolStreamWrapper extends MediaReadOnlyStreamWrapper {

  // phpcs:disable
  // phpcs:ignore Drupal.NamingConventions.ValidVariableName.LowerCamelName
  /**
   * Overrides $base_url defined in MediaReadOnlyStreamWrapper.
   */
  protected $base_url = 'http://media.videotool.dk/';
  // phpcs:enable

  /**
   * Returns a url in the format "http://media.videotool.dk/?vn=qsPQN4MiTeE".
   *
   * Overrides interpolateUrl() defined in MediaReadOnlyStreamWrapper.
   * This is an exact copy of the function in MediaReadOnlyStreamWrapper,
   * here in case that example is redefined or removed.
   */
  public function interpolateUrl() {

    if ($parameters = $this->get_parameters()) {

      return $this->base_url . '?' . http_build_query($parameters);
    }
  }

  /**
   * Get mime type.
   */
  public static function getMimeType($uri, $mapping = NULL) {

    return 'video/videotool';
  }

  /**
   * Get target.
   */
  public function getTarget($f) {

    return FALSE;
  }

  /**
   * Get original thumbnail path.
   */
  public function getOriginalThumbnailPath() {

    $parts = $this->get_parameters();

    $handler_to_vt = new MediaInternetVideoToolHandler($this->interpolateUrl());
    $orig_vt_image_url = '';
    if ($info = $handler_to_vt->getOEmbed()) {
      $orig_vt_image_url = $info['thumbnail_url'];
    }

    return $orig_vt_image_url;
  }

  /**
   * Get local thumbnail path.
   */
  public function getLocalThumbnailPath() {
    $parts = $this->get_parameters();
    $local_path = file_default_scheme() . '://media-videotool/' . check_plain($parts['vn']) . '.jpg';
    if (!file_exists($local_path)) {
      $dirname = drupal_dirname($local_path);
      file_prepare_directory($dirname, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);
      $response = drupal_http_request($this->getOriginalThumbnailPath());
      if (!isset($response->error)) {
        file_unmanaged_save_data($response->data, $local_path, TRUE);
      }
      else {
        @copy($this->getOriginalThumbnailPath(), $local_path);
      }
    }

    return $local_path;
  }

}
