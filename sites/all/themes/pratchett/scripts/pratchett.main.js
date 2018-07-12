/**
 * @file
 * Main javascript file for Pratchett theme.
 */

(function ($) {

  'use strict';

  // Scroll to top when opening a dialog. Dialogs on this site can get
  // pretty big - e.g. when viewing a reading sample. This is
  // furthermore problematic as scrolling is disabled. In _popup.scss
  // we force the popup to the top of the page. jQuery UI should
  // scroll the viewport to make the popup visible but scrolling does
  // not happen on Mobile safari and the popup is rendered out of
  // sight. This forces the browser to scroll to the top of the page
  // when a popup is opened.
  Drupal.behaviors.modalScroll = {
    attach : function () {
      $('body').bind('dialogopen', function () {
        window.scrollTo(0, 0);
      });
    }
  };

  jQuery.fn.extend({
    viewPicker: function (viewPickerWrapper) {

      var wrapper = $(this);

      var gridClass = 'js-search-results-grid-view';
      var viewType = localStorage.getItem('breol-search-view-type');

      if (viewType === null) {
        viewType = 'grid';
        localStorage.setItem('breol-search-view-type', viewType);
      }

      if (viewType === 'grid') {
        wrapper.addClass(gridClass);
      }

      // If the mini panel exist we will continue.
      if (wrapper.length !== 0) {
        var viewPicker = getViewPicker(viewType);

        $(viewPickerWrapper).after(viewPicker);

        // Listen for user input.
        $('.view-picker__item').click(function () {
          viewType = $(this).attr('data-view-type');

          // Apply classes depending on user choice.
          if (!$(this).hasClass('active')) {

            $('.view-picker__item').toggleClass('active');

            if (viewType === 'grid') {
              wrapper.addClass(gridClass);
            }
            else {
              wrapper.removeClass(gridClass);
            }

            // Store the last chosen view type in localstorage.
            localStorage.setItem('breol-search-view-type', viewType);
          }
        });
      }

      function getViewPicker(viewType) {
        var viewPicker = $('<div class="view-picker"></div>');
        var listPicker = $('<div class="view-picker__item list-view" data-view-type="list"></div>');
        var gridPicker = $('<div class="view-picker__item grid-view" data-view-type="grid"></div>');

        if (viewType === 'list') {
          listPicker.addClass('active');
        }
        else {
          gridPicker.addClass('active');
        }

        return viewPicker.append(listPicker, gridPicker);
      }
    }
  });

  /**
   * Add grid view option.
   */
  Drupal.behaviors.gridView = {
    attach : function (context, settings) {
      $('.page-search-ting').viewPicker('.pane-ting-search-sort-form');
    }
  };

  /**
   * Make sure overlay are never shown on initial page show.
   *
   * Because inconsistent cross-browser behaviour, we will always
   * check if the search overlay is injected into the dom and if it
   * is, we will remove. This prevents users from seing the overlay
   * when using the back button.
   */
  Drupal.behaviors.overlay = {
    attach : function (context, settings) {
      $(window).bind('pageshow', function () {
        var overlay = $('.search-overlay--wrapper');
        if (overlay.length !== 0) {
          overlay.remove();
        }
      });
    }
  };

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
        var availability = $(this).find('.search-result--availability');
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

      $('.js-search-form-trigger', searchFormWrapper).click(function (event) {
        event.preventDefault();
        searchFormWrapper.toggleClass('open');
        if (searchFormWrapper.is(':visible')) {
          searchFormWrapper.find('input[name=search_block_form]').focus();
        }
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

  /**
   * Override default auto-complete submit behavior.
   *
   * Override ting_search overriding default auto-complete behavior
   * that prevents form submit.
   *
   * Fix ajax error on mobile Safari.
   */
  Drupal.autocompleteSubmit = function () {
    // On mobile Safari the autocomplete AJAX request gets torn down
    // before Drupals event handler on beforeunload and pagehide is
    // triggered, so the logic to suppress an error popup is non
    // triggered. So, when we submit the form, set the variable it
    // checks for.
    Drupal.beforeUnloadCalled = true;
    $('#autocomplete').each(function () {
      this.owner.hidePopup();
    });

    return true;
  };

})(jQuery);
