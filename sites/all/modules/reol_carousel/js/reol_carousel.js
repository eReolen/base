/**
 * @file
 * Replaces ding_carousel.js.
 */

(function ($) {
  "use strict";

  var queue = [];
  var running = false;

  var update = function () {
    if (running || queue.length < 1) {
      return;
    }
    running = true;
    var swiper = queue.shift();
    $.ajax({
      type: 'get',
      url: Drupal.settings.basePath + $(swiper.el).data('path') + '/' + $(swiper.el).data('offset'),
      dataType: 'json',
      success: function (data) {
        // Remove placeholders.
        $(swiper.el).find('.ding-carousel-item.placeholder').remove();
        if (data.content) {
          swiper.appendSlide(data.content);
          if (swiper.slides.length === 1) {
            $(swiper.el).addClass('single-slide')
          }
          Drupal.attachBehaviors(data.content);
        }
        $(swiper.el).data('offset', data.offset);
        $(swiper.el).data('updating', false);
        // Carry on processing the queue.
        running = false;
        update();
      }
    });
  };

  /**
   * Start the carousel when the document is ready.
   */
  Drupal.behaviors.ding_carousel = {
    attach: function (context) {
      // Start all carousels, tabbed or standalone.
      $('.ding-carousel', context).each(function () {
        var carousel = $(this);

        // Add prev/next buttons to header, if one is present, or
        // simply the container..
        var header = carousel.find('.carousel__header');
        var buttons = '<div class="button-next"></div><div class="button-prev"></div>';

        if (header.length) {
          header.prepend(buttons);
        }
        else {
          carousel.prepend(buttons);
        }

        var swiper = new Swiper(this, {
          speed: 400,
          observer: true,
          //rewind: true, // This does not seem to have any effect
          slidesPerView: 'auto',
          slidesPerGroup: 3,
          //slidesPerGroupAuto: true,
          //centeredSlides: true,
          //loop: true,
          spaceBetween: 20,
          centerInsufficientSlides: true,
          //slidesOffsetAfter: 200,
          wrapperClass: 'carousel',
          slideClass: 'ding-carousel-item',
          freeMode: false,
          freeModeMinimumVelocity: 0.0002,
          freeModeMomentumRatio: 0.5,
          navigation: {
            nextEl: '.button-next',
            prevEl: '.button-prev'
          },
          breakpoints: {
            // when window width is =< 783px (grid-media($medium))
            783: {
              spaceBetween: 40,
              slidesPerGroup: 3,
              freeMode: false,
            },
          },
        });
        swiper.on('slideChange', update);
      });
    }
  };

})(jQuery);
