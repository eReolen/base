<?php
/**
 * @file
 * This file contains all the added functionality for making
 * loans possible in Ding.
 */

/**
 * Implements hook_ding_entity_buttons().
 *
 * Add loan button on entity view page for audiobook or ebook.
 */
function reol_loan_ding_entity_buttons($type, $entity) {
  if ($entity instanceof TingEntity && (strtolower($entity->type) == "lydbog (net)")/* TODO OR ebook */) {
    drupal_add_library('system', 'drupal.ajax');

    $button = array(
      array(
        '#theme' => 'link',
        '#text' => t('Loan'),
        '#path' => 'ting/object/' . $entity->id . '/loan',
        '#options' => array(
          'attributes' => array(
            'class' => array(
              'action-button',
              'reserve-button',
              'use-ajax',
            ),
            'id' => 'reservation-' . $entity->id,
          ),
          'html' => FALSE,
        ),
      ),
    );

    return $button;
  }
}

/**
 * Implements hook_ding_entity_menu().
 *
 * Create menu callback for loaning an audiobook or ebook.
 */
function reol_loan_ding_entity_menu(&$items, $type, $path, $index) {
  if ($type == 'ding_entity') {
    $items[$path . '/loan'] = array(
      'title' => 'Loan',
      'page callback' => 'ding_provider_get_form',
      'page arguments' => array('reol_loan_loan_form', $index),
      'access callback' => TRUE,
    );
  }
}

/**
 * Form for loaning an audiobook or ebook.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The end form array.
 */
function reol_loan_loan_form($form, &$form_state) {
  $form['text'] = array(
    '#type' => 'markup',
    '#markup' => '<p>' . t("Are you sure you wish to loan this title?") . '</p>',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Yes'),
  );

  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('No'),
  );

  return $form;
}

/**
 * Ajax entry callback.
 *
 * Try display the form for loaning the material, if the user is not logged in
 * trigger a ajax login.
 *
 * @param TingEntity $entity
 *   Ting entity object.
 *
 * @return array
 *   Render array with Ajax commands.
 */
function reol_loan_loan_ajax($entity) {
  $commands = array();

  // Check if the logged in user is a library user.
  global $user;
  if (user_is_logged_in()) {
    if (ding_user_is_provider_user($user)) {
      if (is_object($entity) && $entity instanceof TingEntity) {
        $loanable = new DingReservationReservableEntity($entity);

        // Try to make loan.
        try {
          $form = ding_provider_get_form('reol_loan_loan_form', $loanable, FALSE);
          $commands[] = ajax_command_ding_popup('reol_loan', t('Loan'), render($form));
        }
        catch (DingProviderAuthException $exception) {
          // The form may have thrown an Auth exception, so display login. (the
          // reservation link will be triggered on success).
          $commands[] = ajax_command_ding_user_authenticate('');
        }
        catch (Exception $exception) {
          // The form may have thrown an auth exception as the login may have
          // timed-out (the reservation link will be triggered on success).
          $commands[] = ajax_command_ding_popup('reol_loan', t('Error'), '<p>' . t('Unknown error in loan, please contact the library.') . '</p>');

          // Log exception.
          watchdog_exception('reol_loan', $exception);
        }
      }
      else {
        // Error not ting entity.
        $commands[] = ajax_command_ding_popup('reol_loan', t('Error'), '<p>' . t('Unable to load information about the material.') . '</p>');
      }
    }
    else {
      // Error not library user.
      $commands[] = ajax_command_ding_popup('reol_loan', t('Error'), '<p>' . t('Only library user can make reservations.') . '</p>');
    }
  }
  else {
    // Trigger log-in (the reservation link will be triggered on success).
    $commands[] = ajax_command_ding_user_authenticate('');
  }

  // Return the ajax commands as an render array.
  return array('#type' => 'ajax', '#commands' => $commands);
}
