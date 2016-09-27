/**
 * @file
 * Main javascript file for Wille theme.
 */

(function($) {

  /**
   * Detect tablets and mobile devices.
   */
  Drupal.behaviors.isDesktop = {
    attach : function(context, settings) {

      // Add class if we are on desktop.
      if (!isMobile()) {
        $('body').addClass('is-desktop');
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
        if (element.css('display') === 'none') {
          $(element).slideDown(200);
          $(this).addClass('open');
          $(this).removeClass('closed');
        }
        else {
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

      var phoneBreakPoint = 667;

      $('.icon-menu', context).click(function() {
        $('.topbar .menu').slideToggle(200);
      });

      $('.menu-name-main-menu .menu a', context).click(function() {
        if ($(window).width() < phoneBreakPoint) {
          $('.topbar .menu').slideUp(500);

          // Goto top of page.
          window.scrollTo(0, 0);
        }
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
      $(document).ready(function() {

        // If slick is not loaded, we will abort.
        if (!jQuery().slick) {
          return;
        }

        $('.subject-menu', context).slick({
          infinite: false,
          slidesToShow: 6,
          slidesToScroll: 6,
          speed: 500,
          touchThreshold: 24,
          lazyLoad: 'progressive',
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
          ]
        });
      });
    }
  };

  /**
   * Modify the DOM.
   */
  Drupal.behaviors.availabilityAttach = {
    attach : function(context, settings) {
      $('.search-snippet-info').each(function() {
        $(this).addClass('js-processed');
        var metaData = $(this).find('.ting-object-right', context);
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

      $('#ding-facetbrowser-form', context).each(function() {
        $('fieldset', this).each(function() {

          var dropdown = $(this).find('.fieldset-wrapper').addClass('js-processed');

          $(this).click(function() {
            dropdown.slideToggle(200).toggleClass('open');
          });
        });
      });

      if ($('#ding-facetbrowser-form').length !== 0) {

        var html = $('<div class="js-toggle-facets">' + Drupal.t('Limit search results') + '</div>');

        $('.pane-panels-mini.pane-search').prepend(html);

        $('.js-toggle-facets').click(function() {

          $(this).toggleClass('open');

          $('.pane-breol-facetbrowser').toggle();
          $('.before-content').toggle();
        });
      }
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

        // Show search form.
        $('.pane-search-form').show();

        $('.menu-name-main-menu ul li.last a', context)
          .click(function(event) {
            event.preventDefault();
          });
      }
      else {
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
        '.group-material-details',
        '.ting-object-related-item',
        '.pane-ting-ting-object-types'
      ];

      $(elements).each(function(id, element) {
        $(element)
          .addClass('ting-object-collapsible-enabled')
          .addClass('open')
          .find('h2')
          .nextAll()
          .wrapAll(contentWrapper);

        $('.collapsible-content-wrapper').hide();

        $(element).find('h2').click(function() {
          $(element)
            .toggleClass('open')
            .find('.collapsible-content-wrapper')
            .slideToggle();
        });
      });
    }
  };

  /**
   * Detect if jquery ui-dialog is open.
   */
  Drupal.behaviors.uiDialog = {
    attach : function(context, settings) {
      if($('.ui-dialog', context).css('display') == 'none' || $('.ui-dialog').length === 0) {
        // Fallback.
        $('body').removeClass('ui-dialog-is-open');
      } else {
        // Add Class that indicates the dialog is open.
        $('body').addClass('ui-dialog-is-open');

        // Make sure we remove the class when users close the dialog.
        $('.ui-button-icon-primary').click(function() {
          $('body').removeClass('ui-dialog-is-open');
        });
      }
    }
  };

  /**
   * Add grid view option.
   */
  Drupal.behaviors.gridView = {
    attach : function(context, settings) {
      $('.pane-panels-mini.pane-search').viewPicker('.pane-ting-search-sort-form');
    }
  };

  var resizeTimer; // Set resizeTimer to empty so it resets on page load

  function resizeFunction() {
      var windowWidth = window.innerWidth;

      if (windowWidth > 768) {
        $('.pane-breol-facetbrowser, .before-content').show();
      }
  };

  // On resize, run the function and reset the timeout
  // 250 is the delay in milliseconds. Change as you see fit.
  $(window).resize(function() {
      clearTimeout(resizeTimer);
      resizeTimer = setTimeout(resizeFunction, 250);
  });

  resizeFunction();

  /**
   * Detect if we are on mobile devices.
   */
  function isMobile() {
    if (navigator.userAgent.match(/Android/i)
      || navigator.userAgent.match(/webOS/i)
      || navigator.userAgent.match(/iPhone/i)
      || navigator.userAgent.match(/iPad/i)
      || navigator.userAgent.match(/iPod/i)
      || navigator.userAgent.match(/BlackBerry/i)
      || navigator.userAgent.match(/Windows Phone/i)
    ) {
      return true;
    }
    else {
      return false;
    }
  }

})(jQuery);
