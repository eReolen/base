<?php

function wille_form_system_theme_settings_alter(&$form, $form_state) {
  $form['wille_orla_overlay'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable Orla overlay'),
    '#default_value' => theme_get_setting('wille_orla_overlay'),
    '#description'   => t("Enable this to show the Orla overlay"),
  );

  $form['wille_orla_overlay_urls'] = array(
    '#type'          => 'textfield',
    '#title'         => t('Show Orla overlay on these urls'),
    '#default_value' => theme_get_setting('wille_orla_overlay_urls'),
    '#description'   => t("Add comma seperated urls to show the overlay on. (Fx. '/inspiration/orlaprisen)','/node/1' "),
  );
}
