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

  $form['submit'] = $submit_extras + array(
    '#type' => 'submit',
    '#value' => t('Yes'),
    '#name' => 'yes',
  );

  $form['cancel'] = $submit_extras + array(
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
  // Only do something if user agrees.
  if ($form_state['triggering_element']['#name'] != 'no') {
    global $user;
    if ($form_state['values']['loanable']) {
      $loanable = $form_state['values']['loanable'];
      try {
        $loan_result = ding_provider_invoke('loan', 'create', $user, $loanable->ding_entity_id);
        $form_state['loaned'] = TRUE;
        drupal_set_message(t('"@title" loaned.', array('@title' => $loanable->getTitle())));

        // TODO Clear loan session cache (availability etc.).
      }
      catch (DingProviderUserException $e) {
        drupal_set_message($e->getMessageT(array('@title' => $reservable->getTitle())), 'error');
      }
      catch (DingProviderAuthException $e) {
        // Just rethrow.
        throw $e;
      }
      catch (Exception $e) {
        drupal_set_message(t('An error occurred while loaning item. Please try again later.'), 'error');
        watchdog('reol_loan', 'Error while loaning, message: @message', array('@message', $e->getMessage()), WATCHDOG_ERROR);
      }
    }
  }
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
        $loanable = $entity;

        // Try to create loan form.
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
  $response = array(
    '#type' => 'ajax',
    '#commands' => array(),
  );

  // If user clicked no, do nothing.
  if ($form_state['triggering_element']['#name'] == 'no') {
    $response['#commands'][] = ajax_command_ding_popup_close('reol_loan');
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

    $response['#commands'][] = ajax_command_ding_popup('reol_loan', t('Loan'), $html);
  }

  return $response;
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
