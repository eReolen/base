<?php

/**
 * @file
 * Contains workflow\includes\Entity\WorkflowConfigTransition.
 * Contains workflow\includes\Entity\WorkflowConfigTransitionController.
 */

/**
 * Implements a configurated Transition.
 */
class WorkflowConfigTransition extends Entity {

  // Transition data.
  public $tid = 0;
  // public $old_sid = 0;
  // public $new_sid = 0;
  public $sid = 0; // @todo D8: remove $sid, use $new_sid. (requires conversion of Views displays.)
  public $target_sid = 0;
  public $roles = array();

  // Extra fields.
  public $wid = 0;
  // The following must explicitely defined, and not be public, to avoid errors when exporting with json_encode().
  protected $workflow = NULL;

  /**
   * Entity class functions.
   */

/*
  // Implementing clone needs a list of tid-less transitions, and a conversion
  // of sids for both States and ConfigTransitions.
  // public function __clone() {}
 */

  public function __construct(array $values = array(), $entityType = NULL) {
    // Please be aware that $entity_type and $entityType are different things!
    return parent::__construct($values, $entityType = 'WorkflowConfigTransition');
  }

  /**
   * Permanently deletes the entity.
   */
  public function delete() {
    // Notify any interested modules before we delete, in case there's data needed.
    // @todo D8: this can be replaced by a hook_entity_delete(?)
    module_invoke_all('workflow', 'transition delete', $this->tid, NULL, NULL, FALSE);

    return parent::delete();
  }

  protected function defaultLabel() {
    return isset($this->label) ? t('@label', array('@label' => $this->label)) : '';
  }

  protected function defaultUri() {
    $wid = $this->wid;
    return array('path' => WORKFLOW_ADMIN_UI_PATH . "/manage/$wid/transitions/");
  }

  /**
   * Property functions.
   */

  /**
   * Returns the Workflow object of this State.
   *
   * @param Workflow $workflow
   *   An optional workflow object. Can be used as a setter.
   *
   * @return Workflow
   *   Workflow object.
   */
  public function setWorkflow($workflow) {
    $this->wid = $workflow->wid;
    $this->workflow = $workflow;
  }

  public function getWorkflow() {
    if (isset($this->workflow)) {
      return $this->workflow;
    }
    return workflow_load_single($this->wid);
  }
  public function getOldState() {
    return workflow_state_load_single($this->sid);
  }
  public function getNewState() {
    return workflow_state_load_single($this->target_sid);
  }

  /**
   * Verifies if the given transition is allowed.
   *
   * - In settings;
   * - In permissions;
   * - By permission hooks, implemented by other modules.
   *
   * @param string|array $user_roles
   *   The string 'ALL' to force allowing the transition, or an array of role
   *   IDs to compare against the roles allowed for the transition.
   *
   * @return bool
   *   If the transition is allowed, this function returns TRUE. Otherwise, it
   *   returns FALSE.
   */
  public function isAllowed($user_roles) {
    if ($user_roles === 'ALL') {
      // Superuser.
      return TRUE;
    }
    elseif ($user_roles) {
      return array_intersect($user_roles, $this->roles) == TRUE;
    }
    return TRUE;
  }

  /**
   * Generate a machine name for a transition.
   */
  public static function machineName($start_name, $end_name) {
    $new_name   = sprintf("%s_to_%s", $start_name, $end_name);

    // Special case: replace parens in creation state transition names.
    $new_name   = str_replace("(creation)", "_creation", $new_name);

    return $new_name;
  }

  public function save() {
    parent::save();

    // Ensure Workflow is marked overridden.
    $workflow = $this->getWorkflow();
    if ($workflow->status == ENTITY_IN_CODE) {
      $workflow->status = ENTITY_OVERRIDDEN;
      $workflow->save();
    }
  }

  /**
   * Helper debugging function to easily show the contents of a transition.
   */
  public function dpm($function = 'not_specified') {
    $transition = $this;
    $time = NULL;

    // Do this extensive $user_name lines, for some troubles with Action.
    $t_string = get_class($this) . ' ' . $this->identifier() . " in function '$function'";
    //$output[] = 'Entity  = ' . ((!$entity) ? 'NULL' : ($entity_type . '/' . $entity_bundle . '/' . $entity_id));
    //$output[] = 'Field   = ' . $transition->getFieldName();
    $output[] = 'From/To = ' . $transition->sid . ' > ' . $transition->target_sid . ' @ ' . $time;
    //$output[] = 'Comment = ' . $user_name . ' says: ' . $transition->getComment();
    //$output[] = 'Forced  = ' . ($transition->isForced() ? 'yes' : 'no');
    if (function_exists('dpm')) { dpm($output, $t_string); }
  }


}

/**
 * Implements a controller class for WorkflowConfigTransition.
 *
 * The 'true' controller class is 'Workflow'.
 */
class WorkflowConfigTransitionController extends EntityAPIController {

  /**
   * Overrides DrupalDefaultEntityController::cacheGet().
   *
   * Override default function, due to core issue #1572466.
   */
  protected function cacheGet($ids, $conditions = array()) {
    // Load any available entities from the internal cache.
    if ($ids === FALSE && !$conditions) {
      return $this->entityCache;
    }
    return parent::cacheGet($ids, $conditions);
  }

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    $workflow = $entity->getWorkflow();

    // To avoid double posting, check if this transition already exist.
    if (empty($entity->tid)) {
      if ($workflow) {
        $config_transitions = $workflow->getTransitionsBySidTargetSid($entity->sid, $entity->target_sid);
        $config_transition = reset($config_transitions);
        if ($config_transition) {
          $entity->tid = $config_transition->tid;
        }
      }
    }

    // Create the machine_name. This can be used to rebuild/revert the Feature in a target system.
    if (empty($entity->name)) {
      $entity->name = $entity->sid . '_' . $entity->target_sid;
    }

    $return = parent::save($entity, $transaction);
    if ($return) {
      // Save in current workflow for the remainder of this page request.
      // Keep in sync with Workflow::getTransitions() !
      $workflow = $entity->getWorkflow();
      if ($workflow) {
        $workflow->transitions[$entity->tid] = $entity;
        // $workflow->sortTransitions();
      }
    }

    // Reset the cache for the affected workflow, to force reload upon next page_load.
    workflow_reset_cache($entity->wid);

    return $return;
  }
}
