/**
 * @file
 * Really simple survey.
 */

(function ($) {
  "use strict";

  Drupal.reolSurvey = Drupal.reolSurvey || {};

  Drupal.reolSurvey.reset = function () {
    return $.removeCookie('Drupal.reolSurvey.seen', {path: Drupal.settings.basePath});
  };

  Drupal.reolSurvey.close = function () {
    $.cookie('Drupal.reolSurvey.seen', 1, {
      path: Drupal.settings.basePath,
      // The cookie should "never" expire.
      expires: 36500
    });

    var popup = {
      name: 'reol_survey'
    };
    Drupal.ding_popup.close(popup);
  };

  Drupal.reolSurvey.open = function () {
    var win = window.open('https://goo.gl/forms/2gdI9PCE5psv6BZZ2', '_blank');
    win.focus();
    Drupal.reolSurvey.close();
  };

  Drupal.behaviors.reolSurvey = {
    attach: function () {
      $('body').once('reol-survey', function () {
        if (typeof $.cookie('Drupal.reolSurvey.seen') == 'undefined') {
          var popup = {
            name: 'reol_survey',
            title: '',
            class: ['reol-survey'],
            refresh: false,
            resubmit: false,
            extra_data: [],
            data: '<p>Besvar eReolens spørgeskema om lydbøger, og deltag i lodtrækningen om 10 gavekort til biografen.</p><a href="#" class="button" onclick="Drupal.reolSurvey.open();">Ok</a><a href="#" class="button" onclick="Drupal.reolSurvey.close();">Nej tak</a>'
          };
          Drupal.ding_popup.open(popup);
        }
      });
    }
  };
})(jQuery);
