/**
 * @file
 * User lazy loading of images as the user scroll down the page.
 */

(function ($) {
  'use strict';

  window.lazySizesConfig = window.lazySizesConfig || {};
  window.lazySizesConfig.lazyClass = 'js-lazy';
  window.lazySizesConfig.init = false;

  Drupal.behaviors.reol_base_lazy = {
    attach: function (context, settings) {
      lazySizes.init();
    }
  };
})(jQuery);
