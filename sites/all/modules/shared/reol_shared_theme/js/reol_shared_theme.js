/**
 * @file
 * Shared JS.
 */

(function($) {
  // ting_search and ting_search_autocomplete is pretty insistent on
  // wanting to modify the autocomplete behaviour, even when the
  // autocomplete is disabled. Rather than adding another Ding patch,
  // we just ensure that the object is available for them to muck
  // with.
  Drupal.jsAC = {prototype: {}};
  // Scroll to top when opening a dialog. Dialogs on this site can get
  // pretty big - e.g. when viewing a reading sample. This is
  // furthermore problematic as scrolling is disabled. In _popup.scss
  // we force the popup to the top of the page. jQuery UI should
  // scroll the viewport to make the popup visible but scrolling does
  // not happen on Mobile safari and the popup is rendered out of
  // sight. This forces the browser to scroll to the top of the page
  // when a popup is opened.
  Drupal.behaviors.modalScroll = {
    attach : function() {
      $('body').bind('dialogopen', function() {
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
        wrapper.addClass(gridClass)
      }

      // If the mini panel exist we will continue.
      if (wrapper.length !== 0) {
        var viewPicker = getViewPicker(viewType);

        $(viewPickerWrapper).after(viewPicker);

        // Listen for user input.
        $('.view-picker__item').click(function() {
          viewType = $(this).attr('data-view-type');

          // Apply classes depending on user choice.
          if (!$(this).hasClass('active')) {

            $('.view-picker__item').toggleClass('active');

            if (viewType === 'grid') {
              wrapper.addClass(gridClass)
            }
            else {
              wrapper.removeClass(gridClass)
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
    attach : function(context, settings) {
      $('.page-search-ting').viewPicker('.pane-ting-search-sort-form');
    }
  };
})(jQuery);
