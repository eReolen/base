/**
 * @file
 * appbanners.js
 */
(function ($) {
  // This will get the prompt to show up if all the criteria are met.
  window.addEventListener('beforeinstallprompt', (function(e) {
    e.prompt();
  }));
})(jQuery);
