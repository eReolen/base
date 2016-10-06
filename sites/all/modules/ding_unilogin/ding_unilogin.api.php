<?php

/**
 * @file
 * Hooks provided by the ding_unilogin module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Custom access control for UNI•Login users.
 *
 * This hook is invoked in the login process, just after ding_unilogin has
 * validated that the response from UNI•Login, and before the user and profile
 * are created. Implementations can do additional access checks, and provide
 * data for the user profile. It can also change the authname used.
 *
 * It's the implementations responsibility to log extra information about
 * access denials that might aid any debugging.
 *
 * The function is passed a DingUniloginUser object which can be used to query
 * information and set data for later use. Of particular note is
 * DingUniloginUser::setAuthName() and DingUniloginUser::setProfileData().
 *
 * @param DingUniloginUser $user
 *   Represents the user.
 *
 * @return bool
 *   True to proceed with login, false to deny.
 */
function hook_ding_unilogin_login(DingUniloginUser $user) {
  $municipality = $user->getInstitutionMunicipality();
  $libraries = publizon_get_libraries();
  foreach ($libraries as $retailer_id => $library) {
    if (!empty($library->unilogin_id) &&
        $library->unilogin_id == $municipality) {
      $user->setProfileData('field_publizon_retailer_id', $retailer_id);
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * @} End of "addtogroup hooks".
 */
