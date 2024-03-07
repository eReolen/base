/**
 * @file
 * Replaces ding_carousel.js.
 */

(function ($) {
  "use strict";

  Drupal.dingCarouselTransitions = Drupal.dingCarouselTransitions || {};

  /*
   * Transition definitions.
   */

  // Shorthand for the following code.
  var transitions = Drupal.dingCarouselTransitions;

  transitions.none = function () {
  };

  transitions.none.prototype.switchTo = function (to, element) {
    element.find('.ding-carousel:visible').hide();
    to.show();
  };

  transitions.fade = function () {
  };

  transitions.fade.prototype.switchTo = function (to, element) {
    // Freeze height so it wont collapse in the instant that both tabs
    // are invisible. Avoids odd scrolling.
    element.height(element.height());
    element.find('.ding-carousel:visible').fadeOut(200, function () {
      to.fadeIn(200);
      element.height('auto');
    });
  };

  transitions.crossFade = function () {
  };

  transitions.crossFade.prototype.init = function (element) {
    // Add a delay so things have time to find their size.
    window.setTimeout(function () {
      // Add a wrapper and set position/width height, so we can
      // cross-fade between carousels.
      element.find('.ding-carousel').wrapAll($('<div class=fade-container>'));
      var container = element.find('.fade-container');
      container.css('position', 'relative').height(container.height());
      container.find('.ding-carousel').css({
        'position': 'absolute',
        'width': '100%',
        'box-sizing': 'border-box'
      });
    });
  };

  transitions.crossFade.prototype.switchTo = function (to, element) {
    element.find('.ding-carousel').fadeOut(200);
    to.fadeIn(200);
  };

  /*
   * End of transition definitions.
   */

  /**
   * Object handling tabs.
   */
  var Tabset = function (dingCarousel, transition, beforeChange) {
    var self = this;
    this.dingCarousel = dingCarousel;
    this.beforeChange = beforeChange;
    this.transition = transition;
    this.element = $('<div>').addClass('carousel-tabs');
    this.tabs = $('<ul>');
    this.select = $('<select>');

    // Make basic tab structure.
    this.element.append(this.tabs).append(this.select);

    // Initialize transition.
    if (typeof this.transition.init === 'function') {
      this.transition.init(this.dingCarousel);
    }

    // Add event handler for changing tabs when clicked.
    this.tabs.on('click', 'li', function (e) {
      e.preventDefault();
      self.changeTab($(this).data('target'));
      return false;
    });

    // Add event handler for the select for mobile users.
    this.select.on('change', function () {
      self.changeTab($(this).find(':selected').data('target'));
    });

    /**
     * Add a tab.
     */
    this.addTab = function (title, element) {
      // Without the href, the styling suffers.
      var tab = $('<li>').append($('<a>').text(title).attr('href', '#')).data('target', element);
      element.data('tabset-tab', tab);
      this.tabs.append(tab);
      var option = $('<option>').text(title).data('target', element);
      element.data('tabset-option', option);
      this.select.append(option);
    };

    /**
     * Change tab.
     */
    this.changeTab = function (target) {
      // Ignore clicks on the active tab.
      if (target === this.tabs.find('.active').data('target')) {
        return;
      }
      // De-activate current tab.
      this.tabs.find('.active').removeClass('active');
      this.select.find(':selected').removeAttr('selected');

      if (typeof this.beforeChange === 'function') {
        this.beforeChange(target, this.dingCarousel);
      }
      this.transition.switchTo(target, this.dingCarousel);

      // Activate the current tab.
      $(target).data('tabset-tab').addClass('active');
      $(target).data('tabset-option').attr('selected', true);
    };

    /**
     * Make tabs equal width.
     *
     * @todo This might be done with CSS these days.
     */
    this.equalizeTabWith = function () {
      // Get the list of tabs and the number of tabs in the list.
      var childCount = this.tabs.children('li').length;

      // Only do somehting if there actually is tabs.
      if (childCount > 0) {

        // Get the width of the <ul> list element.
        var parentWidth = this.tabs.width();

        // Calculate the width of the <li>'s.
        var childWidth = Math.floor(parentWidth / childCount);

        // Calculate the last <li> width to combined childrens width it self not
        // included.
        var childWidthLast = parentWidth - (childWidth * (childCount - 1));

        // Set the tabs css widths.
        this.tabs.children().css({width: childWidth + 'px'});
        this.tabs.children(':last-child').css({width: childWidthLast + 'px'});
      }
    };

    /**
     * Insert the tabs into the page.
     */
    this.insert = function (element) {
      $(element).after(this.element);

      // Make the tabs equal size.
      this.equalizeTabWith();
      var self = this;
      // Resize the tabs if the window size changes.
      $(window).bind('resize', function () {
        self.equalizeTabWith();
      });

      // Activate the first tab.
      var target = this.tabs.find('li:first-child').data('target');
      $(target).data('tabset-tab').addClass('active');
      $(target).data('tabset-option').attr('selected', true);
    };
  };

  var queue = [];
  var running = false;

  /**
   * Fetches more covers.
   *
   * Runs the queue if not already running.
   */
  var update = function () {
    if (running || queue.length < 1) {
      return;
    }
    running = true;
    var swiper = queue.shift();
    var url = new URL($(swiper.el).data('path'), location.href)
    url.pathname += '/' + $(swiper.el).data('offset')
    $.ajax({
      type: 'get',
      url: url.toString(),
      dataType: 'json',
      success: function (data) {
        // Remove placeholders.
        $(swiper.el).find('.ding-carousel-item.placeholder').remove();
        if (data.content) {
          // Add slide elements in content as individual slides (cf.
          // https://swiperjs.com/swiper-api#method-swiper-appendSlide)
          // Parse HTML content and put it into wrapper element.
          $('<div/>')
            .append($.parseHTML(data.content))
            // Find the slides.
            .find('.'+swiper.params.slideClass)
            // Append each slide to the carousel.
            .each((index, slide) => swiper.appendSlide(slide))

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
   * Event handler for progressively loading more covers.
   */
  var update_handler = function () {
    var tab = $(this.el);

    if (!tab.data('updating')) {
      // If its the first batch or we're near the end.
      if (tab.data('offset') === 0 ||
          (tab.data('offset') > -1 &&
          // Use .75 to make it trigger when scrolling to the end when the
          // coursel only has 5 elements as it will have when initially loaded.
          this.progress > 0.75)) {
        // Disable updates while updating.
        tab.data('updating', true);
        // Add to queue.
        queue.push(this);
      }
    }
    // Run queue.
    update();
  };

  /**
   * Init handler for Swiper.
   *
   * Sets sticky mode and number of slides per "page" depending on the
   * widths of the carousel and first slide.
   */
  var init_handler = function () {

    var gridMediumBreakpoint = 783; // grid-media($medium)
    var carouselWidth = $(this.el).width();
    var slideWidth = $(this.slides[0]).outerWidth();

    // If the first slide is more than 80% of the carousel width enable sticky
    // mode and slide only one item at the time.
    if (slideWidth > (carouselWidth * 0.8)) {
      this.params.freeModeSticky = true;
      this.params.slidesPerGroup = 1;
    }
    else {
      // Scroll only one item on mobile
      if (carouselWidth < gridMediumBreakpoint ) {
        this.params.slidesPerGroup = 1;
      }
      // Scroll up to 3 items on larger screens
      else {
        this.params.slidesPerGroup = Math.min(Math.floor(carouselWidth / slideWidth), 3);
      }

      // Apparently swiper needs to be updated for this to take effect. https://swiperjs.com/swiper-api#method-swiper-update
      this.update();
    }

    if ($(this.el).hasClass('add-wrapper')) {
      $('.carousel', this.el).wrap('<div class="carousel-wrapper"></div>');
    }

    // Call update_handler with the same 'this'.
    update_handler.apply(this);
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
          slidesPerView: 'auto',
          slidesPerGroup: 1,
          spaceBetween: 20, // This is used to calculate width in sites/all/themes/wille/assets/sass/component/_subject.scss
          centerInsufficientSlides: true,
          wrapperClass: 'carousel',
          slideClass: 'ding-carousel-item',
          freeMode: {
            enabled: true,
            sticky: true,
            minimumVelocity: 0.02,
            momentumRatio: 0.15,
          },
          navigation: {
            nextEl: '.button-next',
            prevEl: '.button-prev'
          },
          breakpoints: {
            // grid-media($medium)
            783: {
              spaceBetween: 40, // This size is used to calculate width in sites/all/themes/wille/assets/sass/component/_subject.scss
              slidesPerGroup: 3,
              freeMode: {
                enabled: false,
              },
            },
          },
          init: false
        });
        swiper.on('init', init_handler);
        swiper.on('slideChange', update_handler);
        swiper.init();
      });

      // Initialize tab behavior on tabbed carousels.
      $('.ding-tabbed-carousel', context).once('ding-tabbed-carousel', function () {

        var transition;
        if (typeof $(this).data('transition') === 'string' &&
            typeof Drupal.dingCarouselTransitions[$(this).data('transition')] === 'function') {
          transition = new Drupal.dingCarouselTransitions[$(this).data('transition')]();
        }
        else {
          transition = new Drupal.dingCarouselTransitions.fade();
        }

        // Add tabs.
        var tabs = new Tabset($(this), transition, function (tab) {
          if (tab.hasClass('hidden')) {
            // Silck cannot find the proper width when the parent is hidden, so
            // show the tab, reinit slick and immediately hide it again, before
            // running the real transition.
            tab.show();
            $('.slick-slider', tab).slick('reinit');
            tab.hide();
          }
        });

        $('.ding-carousel', this).each(function () {
          tabs.addTab($(this).data('title'), $(this));
        });

        tabs.insert($(this));
      });
    }

  };

})(jQuery);
