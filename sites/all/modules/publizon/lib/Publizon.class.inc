<?php
/**
 * @file
 * This is a basic abstract class the holds function that are the same for the
 * different Publizon classes that holds information fetched from the Publizon
 * web-service
 */

/**
 * Abstract class that all Publizon storage class should extend.
 */
abstract class Publizon {
  protected $properties = array();

  /**
   * Implements PHP magic __get function.
   */
  public function __get($name) {
    if (array_key_exists($name, $this->properties)) {
      return $this->properties[$name];
    }
    // getClass($this) returns the name of the called class, not this class.
    throw new RuntimeException('Trying to get ' . get_class($this) . ' property that do not exists (' . $name . ').');
  }

  /**
   * Implements PHP magic __set function.
   */
  public function __set($name, $value) {
    if (array_key_exists($name, $this->properties)) {
      $this->properties[$name] = $value;
    }
    else {
      throw new RuntimeException('Trying to set ' . get_class($this) . ' property that do not exists (' . $name . ').');
    }
  }

  /**
   * Implements PHP magic __isset function.
   */
  public function __isset($name) {
    if (array_key_exists($name, $this->properties)) {
      return isset($this->properties[$name]);
    }
    else {
      throw new RuntimeException('Trying to test ' . get_class($this) . ' property that do not exists (' . $name . ').');
    }
  }

  /**
   * Implements PHP magic __unset function.
   */
  public function __unset($name) {
    if (array_key_exists($name, $this->properties)) {
      $this->properties[$name] = NULL;
    }
    else {
      throw new RuntimeException('Trying to unset ' . get_class($this) . ' property that do not exists (' . $name . ').');
    }
  }

  /**
   * Implements PHP magic __toString function.
   */
  public function __toString() {
    throw new RuntimeException('To string have not been implemented yet');
  }
}
