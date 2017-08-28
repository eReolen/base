/**
 * @file
 * Main javascript file for Pratchett theme.
 */

(function ($) {
  "use strict"

  /**
   * Make login link toggle login form.
   */
  Drupal.behaviors.loginFoldout = {
    attach: function (context) {
      // Only add the click-toggle behavior if we have a login form to toggle.
      if ($('.js-login-form').length) {
        $('.js-login-link', context).click(function (e) {
          e.preventDefault();
          $('.pane-user-login').toggle();
        });
      }
    }
  };

})(jQuery);
