/**
 * Main javascript file for Wille theme.
 */
(function($) {

  /**
   * Detect tablets and mobile devices.
   */
  Drupal.behaviors.isDesktop = {
    attach : function(context, settings) {

      // Add class if we are on desktop.
      if(!isMobile()) {
        $('body').addClass('is-desktop');
      }

      /**
       * Detect if we are on mobile devices.
       */
      function isMobile() {
       if( navigator.userAgent.match(/Android/i)
         || navigator.userAgent.match(/webOS/i)
         || navigator.userAgent.match(/iPhone/i)
         || navigator.userAgent.match(/iPad/i)
         || navigator.userAgent.match(/iPod/i)
         || navigator.userAgent.match(/BlackBerry/i)
         || navigator.userAgent.match(/Windows Phone/i)
        ) {
          return true;
        } else {
          return false;
        }
      }
    }
  };

  /**
   * Toggle the footer menus.
   */
  Drupal.behaviors.footerToggle = {
    attach : function(context, settings) {

      $('.footer .pane-title', context).click(function() {

        var element = $(this).next().find('ul');

        // Make sure the right classes are added, so we can
        // make sure the arrow points in the right direction.
        if ( element.css('display') === 'none') {
          $(element).slideDown(200);
          $(this).addClass('open');
          $(this).removeClass('closed');
        } else {
          $(this).removeClass('open');
          $(this).addClass('closed');
          $(element).slideUp(200);
        }
      });

    }
  };

  /**
   * Toggle burger menu.
   */
  Drupal.behaviors.burgerMenu = {
    attach : function(context, settings) {
      $('.icon-menu', context).click(function() {
        $('.topbar .menu').slideToggle(200);
      });
    }
  };

  /**
   * Subject menu.
   *
   * Initialize slick.js for the subject menu.
   */
  Drupal.behaviors.subjectMenu = {
    attach : function(context, settings) {
      $( document ).ready(function() {
        // document.body.addEventListener('touchmove', function(e){ e.preventDefault(); });

        $('.subject-menu', context).slick({
          infinite: false,
          slidesToShow: 6,
          slidesToScroll: 6,
          speed: 500,
          touchThreshold: 24,
          responsive: [
            {
              breakpoint: 1026,
              settings: {
                slidesToShow: 5,
                slidesToScroll: 5,
              }
            },
            {
              breakpoint: 769,
              settings: {
                slidesToShow: 4,
                slidesToScroll: 4
              }
            },
            {
              breakpoint: 500,
              settings: {
                slidesToShow: 2,
                slidesToScroll: 2
              }
            }
            // You can unslick at a given breakpoint now by adding:
            // settings: "unslick"
            // instead of a settings object
          ]
        });
      });
    }
  };

  /**
   * Override of the behaviour.
   *
   * TODO(ts) - this is a temporary solution until we have
   * clarified whats gonna happen here.
   */
  Drupal.behaviors.dingAvailabilityAttach = function(){};

  /**
   * Modify the DOM.
   */
  Drupal.behaviors.availabilityAttach = {
    attach : function(context, settings) {
      $('.search-snippet-info').each(function() {
        $(this).addClass('js-processed');
        var metaData = $(this).find('.group-ting-right-col-search', context);
        var availability = $(this).find('.js-online, .js-pending');
        metaData.append(availability);
      });
    }
  };

  /**
   * Facets.
   */
  Drupal.behaviors.facets = {
    attach : function(context, settings) {

      $('#ding-facetbrowser-form').each(function() {
        $('fieldset').each(function() {

          var dropdown = $(this).find('.fieldset-wrapper').hide().addClass('js-processed');

          $(this).click(function() {
            dropdown.slideToggle(200).toggeClass('open');
          });
        });
      });
    }
  };

  /**
   * Search drop down.
   */
  Drupal.behaviors.searchDropDown = {
    attach : function(context, settings) {
      // If the block is not present in the DOM abort.
      if ($('.pane-search-form').length === 0) {
        return;
      }

      // If we are on the search page we dont want to hide the form,
      // but still don't want users to be able to follow the search link.
      if ($('body.page-search').length !== 0) {
        $('.menu-name-main-menu ul li.last a', context)
        .click(function(event) {
          event.preventDefault();
        });
      } else {
        var searchFormWrapper = $('.pane-search-form', context);
        searchFormWrapper.hide();

        // We assume that search is the fifth element. This would be preferable
        // if it was more dynamic.
        $('.menu-name-main-menu ul li.last a', context)
          .click(function(event) {
            event.preventDefault();
            searchFormWrapper.slideToggle();
          });
        }
    }
  };

  /**
   * Make ting object details collapsible.
   */
  Drupal.behaviors.tingObject = {
    attach : function(context, settings) {

      var contentWrapper = $('<div class="collapsible-content-wrapper" />')

      var elements = [
        '.group_material_details',
        '.ting-object-wrapper',
        '.pane-ting-ting-object-types'
      ];

      $(elements).each(function(id, element) {
        $(element)
          .addClass('ting-object-collapsible-enabled')
          .addClass('open')
          .find('h2')
          .nextAll()
          .wrapAll(contentWrapper);

        $(element).click(function() {
          $(this)
            .toggleClass('open')
            .find('.collapsible-content-wrapper')
            .slideToggle();
        });
      });
    }
  };

})(jQuery);
