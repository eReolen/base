(function($) {

  let options = {
    root: null,
    rootMargin: '0px'
  };

  let imageObserver = new IntersectionObserver(function imageHandler(entries, observer) {
    entries.forEach(function (entry) {
      if (entry.isIntersecting) {

        console.log('Load image');

        let lazyImage = entry.target;
        lazyImage.src = lazyImage.dataset.src;
        imageObserver.unobserve(lazyImage);
      }
    });
  }, options);

  Drupal.behaviors.reader = {
    attach : function(context, settings) {

      console.log('ATT');

      //setTimeout(function () {
        $('.js-lazy').once('lazy-loading', function (index, image) {
          if ('IntersectionObserver' in window) {
            imageObserver.observe(image);
          }
          else {
            image.src = image.dataset.src;
          }
        });
      //}, 1000);


    }
  };
})(jQuery);
