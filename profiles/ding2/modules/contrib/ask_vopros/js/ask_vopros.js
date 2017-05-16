/**
 * @file
 * JavaScript functions for the ask_vopros tab.
 */

(function ($) {
  Drupal.askVopros = {};

  Drupal.askVopros.activate = function(className) {
    $('.ask-vopros-tab:not(.' + className + ')').fadeOut(400);
    if (className) {
      var active_tab = $('.ask-vopros-tab.' + className);
      if (active_tab.length) {
        active_tab.fadeIn();
        return true;
      }
    }
    return false;
  };

  Drupal.askVopros.updateTabs = function() {
    // Try to handle the local clock being set wrong.
    var time = Date.now() - (typeof ask_vopros_offset !== 'undefined' ? ask_vopros_offset : 0);
    var hours = Drupal.settings.ask_vopros_opening_hours;
    var state = 'external';
    if (hours['open'] && hours['close']) {
      if (time > hours['open'] && time < hours['close']) {
        state = 'local';
      }
    }
    else if (hours['open'] && time > hours['open']) {
      state = 'local';
    }
    else if (hours['close'] && time < hours['close']) {
      state = 'local';
    }

    var nextUpdate = null;
    if (hours['open'] && time <= hours['open']) {
      nextUpdate = hours['open'] - time;
    }
    else if (hours['close'] && time <= hours['close']) {
      nextUpdate = hours['close'] - time;
    }

    // If tabs isn't shown yet, schedule a quick update.
    if (!Drupal.askVopros.activate(state)) {
      nextUpdate = 500;
    }

    if (nextUpdate) {
      setTimeout(Drupal.askVopros.updateTabs, nextUpdate);
    }
  };

  Drupal.behaviors.askVoprosTabs = {
    attach: function (context, settings) {
      Drupal.askVopros.updateTabs();
    }
  }
})(jQuery);
