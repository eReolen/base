<?php
/**
 * @file
 * This file contains all the added functionality for making
 * loans possible in Ding.
 */

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
function reol_loan_loan_form($form, &$form_state, $loanable) {
  // Save the loanable in form state.
  $form['loanable'] = array(
    '#type' => 'value',
    '#value' => $loanable,
  );

  $form['text'] = array(
    '#type' => 'markup',
    '#markup' => '<p>' . t("Are you sure you wish to loan this title?") . '</p>',
  );

  // Extras for both submit buttons.
  $submit_extras = array(
    '#attributes' => array(
      'class' => array(
        'action-button',
        'reserve-button',
      ),
    ),
    '#ajax' => array(
      'callback' => 'reol_loan_loan_form_callback',
      'wrapper' => 'reol-loan-loan-form',
    ),
  );

  $form['actions'] = array('#type' => 'actions');

  $form['actions']['submit'] = $submit_extras + array(
    '#type' => 'submit',
    '#value' => t('Yes'),
    '#name' => 'yes',
  );

  $form['actions']['cancel'] = $submit_extras + array(
    '#type' => 'submit',
    '#name' => 'no',
    '#value' => t('No'),
  );

  return $form;
}

/**
 * Submit handler for loan form.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form including values.
 */
function reol_loan_loan_form_submit($form, &$form_state) {
  try {
    // Only do something if user agrees.
    if ($form_state['triggering_element']['#name'] != 'no') {
      global $user;
      if ($form_state['values']['loanable']) {
        $loanable = $form_state['values']['loanable'];
        // Throws exception in case of error.
        ding_provider_invoke('loan', 'create', $user, $loanable->localId);

        // Clear ding_loans and ding_reservation caches.
        if (module_exists('ding_session_cache')) {
          ding_session_cache_clear('ding_loan', 'list');
          ding_session_cache_clear('ding_reservation', 'reservations');
        }

        $form_state['loaned'] = TRUE;
        drupal_set_message(t('"@title" loaned.', array('@title' => $loanable->getTitle())));

        // TODO Clear loan session cache (availability etc.).
      }
    }
  }
  catch (Exception $e) {
    $form_state['error'] = $e;
  }
}

/**
 * Ajax entry callback.
 *
 * Display the form for loaning the material.
 *
 * @param TingEntity $loanable
 *   Ting entity object.
 *
 * @return array
 *   Render array with Ajax commands.
 */
function reol_loan_loan_ajax($loanable, $form = array(), $form_state = array()) {
  $commands = array();

  // If no form is defined, load confirmation form.
  if (empty($form)) {
    $form = ding_provider_get_form('reol_loan_loan_form', $loanable, FALSE);
    $commands[] = ajax_command_ding_popup('reol_loan', t('Loan'), render($form), array('refresh' => TRUE));
  }
  else {
    // If error occurred during submit, rethrow.
    if (isset($form_state['error'])) {
      throw $form_state['error'];
    }

    // If user clicked no, do nothing.
    if ($form_state['triggering_element']['#name'] == 'no') {
      $commands[] = ajax_command_ding_popup_close('reol_loan');
    }
    // Otherwise, reshow form if needed.
    else {
      $html = theme('status_messages');
      // If we have loaned the item, display completed form.
      if ($form_state['loaned']) {
        $html .= drupal_render(ding_provider_build_form('reol_loan_loan_completed_form', $form_state));
      }
      elseif ($form_state['rebuild'] || form_get_errors()) {
        // Redisplay form.
        $html .= drupal_render($form);
      }

      $commands[] = ajax_command_ding_popup('reol_loan', t('Loan'), $html);
    }
  }

  return $commands;
}

/**
 * Ajax callback.
 *
 * Closes the modal on no, reshows form if needed on yes.
 *
 * @param array $form
 *   The form.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   Response array.
 */
function reol_loan_loan_form_callback($form, &$form_state) {
  return reol_base_entity_ajax_form('reol_loan', 'reol_loan_loan_ajax', $form_state['values']['loanable'], $form, $form_state);
}

/**
 * Form for completed loan.
 *
 * @param array $form
 *   The form array.
 * @param array $form_state
 *   The state of the form.
 *
 * @return array
 *   The built form array.
 */
function reol_loan_loan_completed_form($form, &$form_state) {
  // Extras for all submit buttons.
  $submit_extras = array(
    '#attributes' => array(
      'class' => array(
        'action-button',
        'reserve-button',
      ),
    ),
    '#ajax' => array(
      'callback' => 'reol_loan_loan_completed_form_callback',
      'wrapper' => 'reol-loan-loan-completed-form',
    ),
  );

  $form['close'] = $submit_extras + array(
    '#type' => 'submit',
    '#value' => t('Close'),
    '#name' => 'close',
  );

  return $form;
}

/**
 * Form callback.
 *
 * Used for the completed form to handle the buttons.
 *
 * @param array $form
 *   The form array of the form calling this.
 * @param array $form_state
 *   The state of the form at callback.
 *
 * @return array
 *   Response array.
 */
function reol_loan_loan_completed_form_callback($form, &$form_state) {
  $response = array(
    '#type' => 'ajax',
    '#commands' => array(),
  );

  // If user clicked close, close the popup.
  if ($form_state['triggering_element']['#name'] == 'close') {
    $response['#commands'][] = ajax_command_ding_popup_close('reol_loan');
  }

  return $response;
}
