<?php

/**
 * @file
 * Admin functionality for App Banners.
 */

/**
 * Admin form callback.
 */
function appbanners_admin_form() {
  $form['ios'] = array(
    '#type' => 'fieldset',
    '#title' => t('iOS'),
    '#description' => t('See the <a href="!apple">Safari Web Content Guide</a> for more information on App Banners in iOS',
      array(
        '!apple' => 'https://developer.apple.com/library/content/documentation/AppleApplications/Reference/SafariWebContent/PromotingAppswithAppBanners/PromotingAppswithAppBanners.html',
      )),
  );

  $form['ios']['appbanners_ios_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('App ID'),
    '#default_value' => variable_get('appbanners_ios_app_id', ''),
  );

  $form['ios']['appbanners_ios_affiliate_data'] = array(
    '#type' => 'textfield',
    '#title' => t('Affiliate Data'),
    '#default_value' => variable_get('appbanners_ios_affiliate_data', ''),
  );

  $form['ios']['appbanners_ios_app_argument'] = array(
    '#type' => 'textfield',
    '#title' => t('App Argument'),
    '#default_value' => variable_get('appbanners_ios_app_argument', ''),
  );

  $form['android'] = array(
    '#type' => 'fieldset',
    '#title' => t('Android'),
    '#description' => t('See the <a href="!android">Google Developer Fundamentals</a> for more information on Native App Install Banners in Android',
      array(
        '!android' => 'https://developers.google.com/web/fundamentals/app-install-banners/#native_app_install_banners',
      )),
  );

  $form['android']['appbanners_android_app_id'] = array(
    '#type' => 'textfield',
    '#title' => t('App ID'),
    '#default_value' => variable_get('appbanners_android_app_id', ''),
  );

  $form['android']['appbanners_android_short_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Short Name'),
    '#default_value' => variable_get('appbanners_android_short_name', ''),
  );

  $form['android']['appbanners_android_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => variable_get('appbanners_android_name', ''),
  );

  $form['android']['appbanners_android_icon'] = array(
    '#type' => 'textfield',
    '#title' => t('Icon'),
    '#default_value' => variable_get('appbanners_android_icon', ''),
  );

  $form['visibility'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['visibility']['appbanners_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include app banners tags on admin pages?'),
    '#default_value' => variable_get('appbanners_admin', FALSE),
  );

  $form['visibility']['appbanners_visibility'] = array(
    '#type' => 'radios',
    '#options' => array(
      'exclude' => t('All pages except those listed'),
      'include' => t('Only the listed pages'),
    ),
    '#default_value' => variable_get('appbanners_visibility', 'exclude'),
  );

  $form['visibility']['appbanners_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Include script on specific pages'),
    '#default_value' => variable_get('appbanners_pages', ''),
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.",
      array(
        '%blog' => 'blog',
        '%blog-wildcard' => 'blog/*',
        '%front' => '<front>',
      )),
  );

  return system_settings_form($form);
}
