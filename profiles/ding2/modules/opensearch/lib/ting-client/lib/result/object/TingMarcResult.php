<?php
/**
 * @file
 * TingMarcResult class implementation.
 */

class TingMarcResult {
  /**
   * Raw data from webservice.
   */
  private $result;

  private $data = array();

  /**
   * Object constructor.
   *
   * @param object $result
   *   JSON decoded result from webservice.
   */
  public function __construct($result) {
    $this->_position = 0;
    $this->result = $result;
    $this->process();
  }

  /**
   * Build items from raw data (json).
   */
  protected function process() {
    // Check for errors.
    if (!empty($this->result->searchResponse->error)) {
      throw new TingMarcException($this->result->searchResponse->error);
    }

    $object = $this->result->searchResponse->result->searchResult[0]->collection->object[0];
    $records = $object->collection->record;

    // If we have multiple records we need to figure out which one to use.
    if (is_array($records)) {
      foreach ($records as $key => $record) {
        $type = $record->{'@type'}->{'$'};
        // We want the full bibliographic post and not some incomplete main,
        // section or volume post.
        if (strtolower($type) === 'bibliographic') {
          $data = $record->datafield;
          break;
        }
        // Ensure that something is always set, so that we don't fail
        // completely if the type attribute on the record for some reason is
        // not set correctly.
        $data = $record->datafield;
      }
    }
    else {
      $data = $records->datafield;
    }

    if (empty($data)) {
      unset($this->result);
      return;
    }

    $index = 0;
    foreach ($data as $datafield) {
      $tag = $datafield->{'@tag'}->{'$'};
      $subfields = $datafield->subfield;

      if (empty($subfields)) {
        unset($this->result);
        return;
      }

      if (is_object($subfields)) {
        $code = $subfields->{'@code'}->{'$'};
        $value = $subfields->{'$'};
        $this->setData($tag, $code, $value, $index);
      }
      elseif (is_array($subfields)) {
        foreach ($subfields as $subfield) {
          $code = $subfield->{'@code'}->{'$'};
          $value = $subfield->{'$'};
          $this->setData($tag, $code, $value, $index);
        }
      }
      $index++;
    }
    unset($this->result);
  }

  /**
   * Get value.
   *
   * @param string $field
   *   MarcXchange field.
   * @param string $subfield
   *   MarcXchange subfield.
   * @param int $index
   *   Index of the tag.
   *
   * @return mixed|null
   *   Value of the field/subfield.
   */
  public function getValue($field, $subfield = NULL, $index = -1) {
    if ($subfield) {
      if ($index == -1 && isset($this->data[$field][$subfield])) {
        return $this->data[$field][$subfield];
      }
      elseif (isset($this->data[$field][$subfield][$index])) {
        return $this->data[$field][$subfield][$index];
      }
    }
    elseif (isset($this->data[$field])) {
      return $this->data[$field];
    }
    return NULL;
  }

  /**
   * Store values into internal storage.
   *
   * @param string $tag
   *   MarcXchange field.
   * @param string $code
   *   MarcXchange subfield.
   * @param string $value
   *   Field value.
   * @param int $index
   *   Index of the tag.
   */
  private function setData($tag, $code, $value, $index) {
    if (!empty($this->data[$tag][$code][$index])) {
      if (is_array($this->data[$tag][$code][$index])) {
        $this->data[$tag][$code][$index][] = $value;
      }
      else {
        $tmp = $this->data[$tag][$code][$index];
        $this->data[$tag][$code][$index] = array($tmp);
        $this->data[$tag][$code][$index][] = $value;
      }
    }
    else {
      $this->data[$tag][$code][$index] = $value;
    }
  }
}
