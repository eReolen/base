<?php

/**
 * @file
 * Media_videotool/includes/MediaInterenetVideoToolHandler.inc.
 *
 * Contains MediaInternetVideoToolHandler.
 */

/**
 * Implementation of MediaInternetBaseHandler.
 *
 * @see hook_media_internet_providers().
 */
class MediaInternetVideoToolHandler extends MediaInternetBaseHandler {

  /**
   * Check if a VideoTool video id is valid.
   *
   * Check against the oembed stream instead of the gdata api site to
   * avoid "yt:quota too_many_recent_calls" errors.
   *
   * @return bool
   *   True if the id a valid. Otherwise false.
   */
  public static function validId($id) {
    $url = 'http://www.videotool.dk/oembed?url=http%3A//media.videotool.dk/%3Fvn%3D' . $id;

    $response = drupal_http_request($url, array('method' => 'HEAD'));
    if ($response->code != 200) {
      throw new MediaInternetValidationException("The VideoTool video ID is invalid or the video was deleted.");
    }
    return TRUE;
  }

  /**
   * {@inheritdoc}
   */
  public function parse($embedCode) {

    $patterns = array(
      '@videotool\.dk/?[#\?].*?vn=([^"\& ]+)@i',
    );

    foreach ($patterns as $pattern) {
      preg_match($pattern, $embedCode, $matches);
      // @todo Parse is called often. Refactor so that valid ID is checked
      // when a video is added, but not every time the embedCode is parsed.
      if (isset($matches[1]) && self::validId($matches[1])) {
        return file_stream_wrapper_uri_normalize('videotool://vn/' . $matches[1]);
      }
    }
  }

  /**
   * {@inheritdoc}
   */
  public function claim($embedCode) {

    if ($this->parse($embedCode)) {
      return TRUE;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getFileObject() {
    $uri = $this->parse($this->embedCode);
    $file = file_uri_to_object($uri, TRUE);

    if (empty($file->fid) && $info = $this->getOEmbed()) {
      $file->filename = truncate_utf8($info['title'], 255);
    }

    return $file;
  }

  // phpcs:disable Drupal.NamingConventions.ValidFunctionName.ScopeNotCamelCaps

  /**
   * Returns information about the media. See http://www.oembed.com/.
   *
   * @return array|null
   *   If oEmbed information is available, an array containing 'title', 'type',
   *   'url', and other information as specified by the oEmbed standard.
   *   Otherwise, NULL.
   *
   * @throws \Exception
   */
  public function getOEmbed() {
    $uri = $this->parse($this->embedCode);
    $external_url = file_create_url($uri);

    $oembed_url = url('http://www.videotool.dk/oembed', array(
      'query' => array(
        'url' => $external_url,
        'format' => 'json',
      ),
    ));
    $response = drupal_http_request($oembed_url);
    if (!isset($response->error)) {
      return drupal_json_decode($response->data);
    }
    else {
      throw new Exception("Error Processing Request. (Error: {$response->code}, {$response->error})");
    }
  }

}
