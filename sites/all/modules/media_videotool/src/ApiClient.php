<?php

namespace Drupal\media_videotool;

/**
 * Videotool API client.
 */
final class ApiClient {
  /**
   * The API url.
   *
   * @var string
   */
  private $apiUrl = 'https://api.videotool.dk/api/';

  /**
   * The API public key.
   *
   * @var string
   */
  private $publicKey;

  /**
   * The API secret key.
   *
   * @var string
   */
  private $secretKey;

  /**
   * Constructor.
   */
  public function __construct(array $options = []) {
    $this->publicKey = $options['public_key'] ?? variable_get('media_videotool_api_key')['public'] ?? NULL;
    $this->secretKey = $options['secret_key'] ?? variable_get('media_videotool_api_key')['secret'] ?? NULL;
  }

  /**
   * Check that client can authenticate with Videotool API.
   *
   * @return bool
   *   True if authentication is successful.
   */
  public function authenticate() {
    $data = $this->fetchData('getVideos');

    return 'SUCCESS' === ($data['status'] ?? NULL);
  }

  /**
   * Get all videos.
   *
   * @param array $parameters
   *   The parameters.
   *
   * @return null|array
   *   The videos if found.
   */
  public function getVideos(array $parameters = []) {
    return $this->fetchData(__FUNCTION__, $parameters)['videos'] ?? NULL;
  }

  /**
   * Get one video by parameters.
   *
   * @param array $parameters
   *   The parameters.
   *
   * @return null|array
   *   A single video matching all parameters if found.
   */
  public function getVideoBy(array $parameters) {
    $videos = $this->getVideos($parameters);

    // Apparently the Videotool API returns all videos if the parameters do not
    // match any video! Therefore we have to check for an actual match in the
    // video list.
    if (is_array($videos)) {
      // The parameters
      // * DurationFull
      // * ThumbLifeTimeInSeconds
      // * HlsLifeTimeInSeconds
      // are only used to control how the result looks so we
      // removed those before checking for a video match.
      $parameters = array_filter(
        $parameters,
        static function ($key) {
          return !in_array(
            strtolower($key),
            ['durationfull', 'thumblifetimeinseconds', 'hlslifetimeinseconds'],
            TRUE
          );
        },
        ARRAY_FILTER_USE_KEY
      );

      foreach ($videos as $video) {
        if ($parameters === array_intersect_uassoc($parameters, $video, 'strcasecmp')) {
          return $video;
        }
      }
    }

    return NULL;
  }

  /**
   * Get one video by url and parameters.
   *
   * @param string $url
   *   The Videotool video url.
   * @param array $parameters
   *   The parameters.
   *
   * @return null|array
   *   A single video matching url and all parameters if found.
   */
  public function getVideoByUrl($url, array $parameters) {
    if (preg_match('/media.videotool.dk.*[?&]vn=(?P<name>[^&]+)/', $url, $matches)) {
      return $this->getVideoBy($parameters + [
        'VideoName' => $matches['name'],
      ]);
    }

    return NULL;
  }

  /**
   * Fetch data from Videotool API.
   *
   * @return null|array
   *   The data if any.
   */
  private function fetchData($method, array $parameters = []) {
    $response = $this->fetch($method, $parameters);

    return (200 === (int) $response->code) ? json_decode($response->data, TRUE) : NULL;
  }

  /**
   * Fetch response from Videotool API.
   *
   * @return object
   *   Result of calling drupal_http_request().
   */
  private function fetch($method, array $parameters = []) {
    $sendTime = (new \DateTimeImmutable())->format('YmdHis');
    $encryptedKey = sha1($this->publicKey . $this->secretKey . $method . $sendTime);
    $parameters += [
      'publicKey' => $this->publicKey,
      'sendtime' => $sendTime,
      'method' => $method,
      'encryptedKey' => $encryptedKey,
    ];

    return drupal_http_request($this->apiUrl, [
      'method' => 'POST',
      'data' => $parameters,
      'headers' => ['content-type' => 'application/x-www-form-urlencoded'],
    ]);
  }

}
