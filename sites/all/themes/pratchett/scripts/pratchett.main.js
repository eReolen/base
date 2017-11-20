/**
 * @file
 * Main javascript file for Pratchett theme.
 */

(function ($) {

  /**
   * Detect tablets and mobile devices.
   */
  Drupal.behaviors.isDesktop = {
    attach : function (context, settings) {

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
    attach : function (context, settings) {

      $('.footer .pane-title', context).click(function () {

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
   * Modify the DOM.
   */
  Drupal.behaviors.availabilityAttach = {
    attach : function (context, settings) {
      $('.search-snippet-info').each(function () {
        $(this).addClass('js-processed');
        var metaData = $(this).find('.ting-object-right', context);
        var availability = $(this).find('.js-online, .js-pending');
        metaData.append(availability);
      });
    }
  };

  /**
   * Make ting object details collapsible.
   */
  Drupal.behaviors.tingObject = {
    attach : function (context, settings) {
      $('.js-collaps').each(function (id, element) {
        $(element).find('.ting-relations__content').hide();
        $(element).find('h2').first().click(function () {
          $(element).find('.ting-relations__content').slideToggle();
        });
      });
    }
  };

  /**
   * Detect if jquery ui-dialog is open.
   */
  Drupal.behaviors.uiDialog = {
    attach : function (context, settings) {
      if ($('.ui-dialog', context).css('display') == 'none' || $('.ui-dialog').length === 0) {
        // Fallback.
        $('body').removeClass('ui-dialog-is-open');
      }
      else {
        // Add Class that indicates the dialog is open.
        $('body').addClass('ui-dialog-is-open');

        // Make sure we remove the class when users close the dialog.
        $('.ui-button-icon-primary').click(function () {
          $('body').removeClass('ui-dialog-is-open');
        });
      }
    }
  };

  /**
   * Search drop down.
   */
  Drupal.behaviors.searchDropDown = {
    attach : function (context, settings) {
      // If the block is not present in the DOM abort.
      if ($('.js-search-form').length === 0) {
        return;
      }

      var searchFormWrapper = $('.js-search-form', context);

      $(openTrigger, searchFormWrapper).click(function (event) {
        event.preventDefault();
        searchFormWrapper.toggleClass('open');
      });
    }
  };

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
