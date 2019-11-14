/**
 * @file
 * Lazy load images with the 'js-lazy' class.
 */
(function($) {

  // Obverser configuration.
  var options = {
    root: null,
    rootMargin: '0px'
  };

  /**
   * Observer instersection object.
   *
   * Swaps the placeholder image with the real image when image comes into view
   * in the browser.
   *
   * @type {IntersectionObserver}
   */
  if ('IntersectionObserver' in window) {
    var imageObserver = new IntersectionObserver(function imageHandler(entries, observer) {
      entries.forEach(function (entry) {
        if (entry.isIntersecting) {
          var lazyImage = entry.target;
          lazyImage.src = lazyImage.dataset.src;
          imageObserver.unobserve(lazyImage);
        }
      });
    }, options);
  }

  /**
   * Attached observer to images.
   *
   * This is re-attached every time the carousal or other drupal ajax event is
   * completed.
   *
   * @type {{attach: Drupal.behaviors.reader.attach}}
   */
  Drupal.behaviors.lazyLoad = {
    attach : function(context, settings) {
      $('.js-lazy').once('lazy-loading', function (index, image) {
        if ('IntersectionObserver' in window) {
          imageObserver.observe(image);
        }
        else {
          // If the browser doesn't support observer pattern simply load all
          // images now.
          image.src = image.dataset.src;
        }
      });
    }
  };
})(jQuery);
