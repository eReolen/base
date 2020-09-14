(window["webpackJsonp"] = window["webpackJsonp"] || []).push([["app"],{

/***/ "./assets/app.js":
/*!***********************!*\
  !*** ./assets/app.js ***!
  \***********************/
/*! no exports provided */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var _app_scss__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./app.scss */ "./assets/app.scss");
/* harmony import */ var _app_scss__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(_app_scss__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var jquery__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! jquery */ "./node_modules/jquery/dist/jquery.js");
/* harmony import */ var jquery__WEBPACK_IMPORTED_MODULE_1___default = /*#__PURE__*/__webpack_require__.n(jquery__WEBPACK_IMPORTED_MODULE_1__);
/* harmony import */ var _scripts_ding_availability_labels_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./scripts/ding_availability_labels.js */ "./assets/scripts/ding_availability_labels.js");
/* harmony import */ var _scripts_ding_availability_labels_js__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_scripts_ding_availability_labels_js__WEBPACK_IMPORTED_MODULE_2__);
/* harmony import */ var _scripts_pratchett_main_js__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./scripts/pratchett.main.js */ "./assets/scripts/pratchett.main.js");
/* harmony import */ var _scripts_pratchett_main_js__WEBPACK_IMPORTED_MODULE_3___default = /*#__PURE__*/__webpack_require__.n(_scripts_pratchett_main_js__WEBPACK_IMPORTED_MODULE_3__);
// assets/js/app.js

/*
 * Welcome to your app's main JavaScript file!
 *
 * We recommend including the built version of this JavaScript file
 * (and its CSS file) in your base layout (base.html.twig).
 */
// any CSS you import will output into a single css file (app.css in this case)
 // Need jQuery? Install it with "yarn add jquery", then uncomment to import it.





/***/ }),

/***/ "./assets/app.scss":
/*!*************************!*\
  !*** ./assets/app.scss ***!
  \*************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

// extracted by mini-css-extract-plugin

/***/ }),

/***/ "./assets/scripts/ding_availability_labels.js":
/*!****************************************************!*\
  !*** ./assets/scripts/ding_availability_labels.js ***!
  \****************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

/* WEBPACK VAR INJECTION */(function(jQuery) {__webpack_require__(/*! core-js/modules/es.array.find */ "./node_modules/core-js/modules/es.array.find.js");

__webpack_require__(/*! core-js/modules/es.array.join */ "./node_modules/core-js/modules/es.array.join.js");

__webpack_require__(/*! core-js/modules/es.regexp.exec */ "./node_modules/core-js/modules/es.regexp.exec.js");

__webpack_require__(/*! core-js/modules/es.string.match */ "./node_modules/core-js/modules/es.string.match.js");

/**
 * @file
 * Override the JS behavior of ding_availability_labels.
 */
(function ($) {
  'use strict'; // Cache of fetched availability information.

  Drupal.DADB = {};
  Drupal.behaviors.dingAvailabilityAttach = {
    attach: function attach(context, settings) {
      var ids = [];
      var html_ids = []; // Extract entity ids from Drupal settings array.

      if (settings.hasOwnProperty('ding_availability')) {
        $.each(settings.ding_availability, function (id, entity_ids) {
          $.each(entity_ids, function (index, entity_id) {
            if (Drupal.DADB[entity_id] === undefined) {
              Drupal.DADB[entity_id] = null;
              ids.push(entity_id);
              html_ids.push(id);
            }
          });
        });
      } // Fetch availability.


      if (ids.length > 0) {
        var mode = settings.ding_availability_mode ? settings.ding_availability_mode : 'items';
        var path = settings.basePath + 'ding_availability/' + mode + '/' + ids.join(',');
        $.ajax({
          dataType: 'json',
          url: path,
          success: function success(data) {
            $.each(data, function (id, item) {
              // Update cache.
              Drupal.DADB[id] = item;
            });
            $.each(settings.ding_availability, function (id, entity_ids) {
              if (id.match(/^availability-/)) {
                // Update availability indicators.
                update_availability(id, entity_ids);
              }
            });
            update_availability_remove_pending();
          },
          error: function error() {
            $('div.loader').remove();
          }
        });
      } else {
        // Apply already fetched availability, if any.
        if (settings.hasOwnProperty('ding_availability')) {
          $.each(settings.ding_availability, function (id, entity_ids) {
            update_availability(id, entity_ids);
          });
          update_availability_remove_pending();
        }
      }
      /**
       * Update availability on the page.
       *
       * The array of entity_ids is an array as we only show one availability
       * label per material type. So if one of these have an available status
       * the label have to reflect this.
       * @param id {number} The element id that this should target.
       * @param entity_ids {number[]} Array of entities.
       */


      function update_availability(id, entity_ids) {
        // Default the status to not available and not reservable.
        var status = {
          available: false,
          reservable: false
        }; // Loop over the entity ids and if one has available or reservable
        // true save that value.

        $.each(entity_ids, function (index, entity_id) {
          if (Drupal.DADB[entity_id]) {
            status.available = status.available || Drupal.DADB[entity_id]['available'];
            status.reservable = status.reservable || Drupal.DADB[entity_id]['reservable'];
          }
        });
        var element = $('#' + id);
        element.removeClass('pending').addClass('processed'); // Get hold of the reserve button (it hidden as default, so we may need
        // to show it).

        var reserver_btn = element.parents('.ting-object:first').find('[id^=ding-reservation-reserve-form]');
        update_availability_elements(element, reserver_btn, status);
      }
      /**
       * Helper function to move the materials based on availability.
       * @param element {Object} The target element (material that should be moved).
       * @param status {string} Structure with available and reservable state.
       */


      function update_availability_type(element, status) {
        var groups_wrapper = element.closest('.search-result--availability');
        var reservable = status['reservable'];
        var available = status['available'];
        var group = null;

        if ($('.js-online', groups_wrapper).length !== 0) {
          group = $('.js-online', groups_wrapper);
        } else if (available) {
          group = $('.js-available', groups_wrapper);

          if (group.length === 0) {
            group = $('<p class="js-available"></p>');
            groups_wrapper.append(group);
          }
        } else if (reservable) {
          group = $('.js-reservable', groups_wrapper);

          if (group.length === 0) {
            group = $('<p class="js-reservable"></p>');
            groups_wrapper.append(group);
          }
        } else {
          group = $('.js-unavailable', groups_wrapper);

          if (group.length === 0) {
            group = $('<p class="js-unavailable"></p>');
            groups_wrapper.append(group);
          }
        } // Move the element into that type.


        group.append(element);
      }
      /**
       * Remove pending groups.
       *
       * Removes js-pending groups (labels) if they are empty. This
       * should be called as the last function in updating
       * availability information and see as a clean-up function.
       */


      function update_availability_remove_pending() {
        // Loop over all pending availability groups.
        $('.js-pending').each(function () {
          var elm = $(this);
          var children = elm.children();

          if (!children.length) {
            // The current pending group is empty, so simply remove it.
            elm.remove();
          }
        });
      }
      /**
       * Add class to both an element and the reservation button.
       *
       * @param element
       *   jQuery availability element to add the class to.
       * @param btn
       *   Reservation button to add the class to.
       * @param status
       *   Structure with available and reservable state.
       */


      function update_availability_elements(element, btn, status) {
        var class_name = null;

        for (var i in status) {
          if (status[i] === true) {
            class_name = i;
          } else {
            if (i === 'available') {
              class_name = 'un' + i;
            } else if (i === 'reservable') {
              class_name = 'not-' + i;
            }
          }

          element.addClass(class_name);

          if (btn.length) {
            btn.addClass(class_name);
          }
        }

        $(element).once('reol-availability', function () {
          // TODO: this is very fragile.
          var type_name = element.text().toLowerCase();
          var string;

          if (Drupal.settings.ding_availability_type_mapping[type_name]) {
            type_name = Drupal.settings.ding_availability_type_mapping[type_name];
          }

          if (status['available'] === true) {
            string = Drupal.settings.ding_availability_type_strings['available'];
            element.text(Drupal.formatString(string, {
              '@type': type_name
            }));
          } else if (status['reservable'] === true) {
            string = Drupal.settings.ding_availability_type_strings['reservable'];
            element.text(Drupal.formatString(string, {
              '@type': type_name
            }));
          }
        });
        update_availability_type(element, status);
      }
    }
  };
})(jQuery);
/* WEBPACK VAR INJECTION */}.call(this, __webpack_require__(/*! jquery */ "./node_modules/jquery/dist/jquery.js")))

/***/ }),

/***/ "./assets/scripts/pratchett.main.js":
/*!******************************************!*\
  !*** ./assets/scripts/pratchett.main.js ***!
  \******************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

/* WEBPACK VAR INJECTION */(function(jQuery) {__webpack_require__(/*! core-js/modules/es.array.find */ "./node_modules/core-js/modules/es.array.find.js");

__webpack_require__(/*! core-js/modules/es.function.bind */ "./node_modules/core-js/modules/es.function.bind.js");

__webpack_require__(/*! core-js/modules/es.regexp.exec */ "./node_modules/core-js/modules/es.regexp.exec.js");

__webpack_require__(/*! core-js/modules/es.string.match */ "./node_modules/core-js/modules/es.string.match.js");

/**
 * @file
 * Main javascript file for Pratchett theme.
 */
(function ($) {
  'use strict'; // Disable AJAX request error popup. On mobile Safari the
  // autocomplete AJAX request gets torn down before Drupals event
  // handler on beforeunload and pagehide is triggered, so the logic
  // to suppress an error popup is non triggered. Even the form submit
  // handler can be called after the AJAX request is killed, so
  // setting this there doesn't help. As end users don't understand
  // the popup anyway, we completely disable it.
  // See misc/drupal.js to how this works.

  Drupal.beforeUnloadCalled = true; // Scroll to top when opening a dialog. Dialogs on this site can get
  // pretty big - e.g. when viewing a reading sample. This is
  // furthermore problematic as scrolling is disabled. In _popup.scss
  // we force the popup to the top of the page. jQuery UI should
  // scroll the viewport to make the popup visible but scrolling does
  // not happen on Mobile safari and the popup is rendered out of
  // sight. This forces the browser to scroll to the top of the page
  // when a popup is opened.

  Drupal.behaviors.modalScroll = {
    attach: function attach() {
      $('body').bind('dialogopen', function () {
        window.scrollTo(0, 0);
      });
    }
  };
  jQuery.fn.extend({
    viewPicker: function viewPicker(viewPickerWrapper) {
      var wrapper = $(this);
      var gridClass = 'js-search-results-grid-view';
      var viewType = localStorage.getItem('breol-search-view-type');

      if (viewType === null) {
        viewType = 'grid';
        localStorage.setItem('breol-search-view-type', viewType);
      }

      if (viewType === 'grid') {
        wrapper.addClass(gridClass);
      } // If the mini panel exist we will continue.


      if (wrapper.length !== 0) {
        var viewPicker = getViewPicker(viewType);
        $(viewPickerWrapper).after(viewPicker); // Listen for user input.

        $('.view-picker__item').click(function () {
          viewType = $(this).attr('data-view-type'); // Apply classes depending on user choice.

          if (!$(this).hasClass('active')) {
            $('.view-picker__item').toggleClass('active');

            if (viewType === 'grid') {
              wrapper.addClass(gridClass);
            } else {
              wrapper.removeClass(gridClass);
            } // Store the last chosen view type in localstorage.


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
        } else {
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
    attach: function attach(context, settings) {
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
    attach: function attach(context, settings) {
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
    attach: function attach(context, settings) {
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
    attach: function attach(context, settings) {
      $('.footer .pane-title', context).click(function () {
        var element = $(this).next().find('ul'); // Make sure the right classes are added, so we can
        // make sure the arrow points in the right direction.

        if (element.css('display') === 'none') {
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
   * Modify the DOM.
   */

  Drupal.behaviors.availabilityAttach = {
    attach: function attach(context, settings) {
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
    attach: function attach(context, settings) {
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
    attach: function attach(context, settings) {
      if ($('.ui-dialog', context).css('display') == 'none' || $('.ui-dialog').length === 0) {
        // Fallback.
        $('body').removeClass('ui-dialog-is-open');
      } else {
        // Add Class that indicates the dialog is open.
        $('body').addClass('ui-dialog-is-open'); // Make sure we remove the class when users close the dialog.

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
    attach: function attach(context, settings) {
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
    if (navigator.userAgent.match(/Android/i) || navigator.userAgent.match(/webOS/i) || navigator.userAgent.match(/iPhone/i) || navigator.userAgent.match(/iPad/i) || navigator.userAgent.match(/iPod/i) || navigator.userAgent.match(/BlackBerry/i) || navigator.userAgent.match(/Windows Phone/i)) {
      return true;
    } else {
      return false;
    }
  }
})(jQuery);
/* WEBPACK VAR INJECTION */}.call(this, __webpack_require__(/*! jquery */ "./node_modules/jquery/dist/jquery.js")))

/***/ })

},[["./assets/app.js","runtime","vendors~app"]]]);
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9hc3NldHMvYXBwLmpzIiwid2VicGFjazovLy8uL2Fzc2V0cy9hcHAuc2NzcyIsIndlYnBhY2s6Ly8vLi9hc3NldHMvc2NyaXB0cy9kaW5nX2F2YWlsYWJpbGl0eV9sYWJlbHMuanMiLCJ3ZWJwYWNrOi8vLy4vYXNzZXRzL3NjcmlwdHMvcHJhdGNoZXR0Lm1haW4uanMiXSwibmFtZXMiOlsiJCIsIkRydXBhbCIsIkRBREIiLCJiZWhhdmlvcnMiLCJkaW5nQXZhaWxhYmlsaXR5QXR0YWNoIiwiYXR0YWNoIiwiY29udGV4dCIsInNldHRpbmdzIiwiaWRzIiwiaHRtbF9pZHMiLCJoYXNPd25Qcm9wZXJ0eSIsImVhY2giLCJkaW5nX2F2YWlsYWJpbGl0eSIsImlkIiwiZW50aXR5X2lkcyIsImluZGV4IiwiZW50aXR5X2lkIiwidW5kZWZpbmVkIiwicHVzaCIsImxlbmd0aCIsIm1vZGUiLCJkaW5nX2F2YWlsYWJpbGl0eV9tb2RlIiwicGF0aCIsImJhc2VQYXRoIiwiam9pbiIsImFqYXgiLCJkYXRhVHlwZSIsInVybCIsInN1Y2Nlc3MiLCJkYXRhIiwiaXRlbSIsIm1hdGNoIiwidXBkYXRlX2F2YWlsYWJpbGl0eSIsInVwZGF0ZV9hdmFpbGFiaWxpdHlfcmVtb3ZlX3BlbmRpbmciLCJlcnJvciIsInJlbW92ZSIsInN0YXR1cyIsImF2YWlsYWJsZSIsInJlc2VydmFibGUiLCJlbGVtZW50IiwicmVtb3ZlQ2xhc3MiLCJhZGRDbGFzcyIsInJlc2VydmVyX2J0biIsInBhcmVudHMiLCJmaW5kIiwidXBkYXRlX2F2YWlsYWJpbGl0eV9lbGVtZW50cyIsInVwZGF0ZV9hdmFpbGFiaWxpdHlfdHlwZSIsImdyb3Vwc193cmFwcGVyIiwiY2xvc2VzdCIsImdyb3VwIiwiYXBwZW5kIiwiZWxtIiwiY2hpbGRyZW4iLCJidG4iLCJjbGFzc19uYW1lIiwiaSIsIm9uY2UiLCJ0eXBlX25hbWUiLCJ0ZXh0IiwidG9Mb3dlckNhc2UiLCJzdHJpbmciLCJkaW5nX2F2YWlsYWJpbGl0eV90eXBlX21hcHBpbmciLCJkaW5nX2F2YWlsYWJpbGl0eV90eXBlX3N0cmluZ3MiLCJmb3JtYXRTdHJpbmciLCJqUXVlcnkiLCJiZWZvcmVVbmxvYWRDYWxsZWQiLCJtb2RhbFNjcm9sbCIsImJpbmQiLCJ3aW5kb3ciLCJzY3JvbGxUbyIsImZuIiwiZXh0ZW5kIiwidmlld1BpY2tlciIsInZpZXdQaWNrZXJXcmFwcGVyIiwid3JhcHBlciIsImdyaWRDbGFzcyIsInZpZXdUeXBlIiwibG9jYWxTdG9yYWdlIiwiZ2V0SXRlbSIsInNldEl0ZW0iLCJnZXRWaWV3UGlja2VyIiwiYWZ0ZXIiLCJjbGljayIsImF0dHIiLCJoYXNDbGFzcyIsInRvZ2dsZUNsYXNzIiwibGlzdFBpY2tlciIsImdyaWRQaWNrZXIiLCJncmlkVmlldyIsIm92ZXJsYXkiLCJpc0Rlc2t0b3AiLCJpc01vYmlsZSIsImZvb3RlclRvZ2dsZSIsIm5leHQiLCJjc3MiLCJzbGlkZURvd24iLCJzbGlkZVVwIiwiYXZhaWxhYmlsaXR5QXR0YWNoIiwibWV0YURhdGEiLCJhdmFpbGFiaWxpdHkiLCJ0aW5nT2JqZWN0IiwiaGlkZSIsImZpcnN0Iiwic2xpZGVUb2dnbGUiLCJ1aURpYWxvZyIsInNlYXJjaERyb3BEb3duIiwic2VhcmNoRm9ybVdyYXBwZXIiLCJldmVudCIsInByZXZlbnREZWZhdWx0IiwiaXMiLCJmb2N1cyIsIm5hdmlnYXRvciIsInVzZXJBZ2VudCJdLCJtYXBwaW5ncyI6Ijs7Ozs7Ozs7OztBQUNBO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBOztBQUNBOzs7Ozs7QUFPQTtDQUdBOztBQUNBO0FBRUE7Ozs7Ozs7Ozs7OztBQ2ZBLHVDOzs7Ozs7Ozs7Ozs7Ozs7Ozs7O0FDQUE7Ozs7QUFLQSxDQUFDLFVBQVVBLENBQVYsRUFBYTtBQUVaLGVBRlksQ0FJWjs7QUFDQUMsUUFBTSxDQUFDQyxJQUFQLEdBQWMsRUFBZDtBQUVBRCxRQUFNLENBQUNFLFNBQVAsQ0FBaUJDLHNC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QVV5QixLQUFWLEVBQWlCO0FBQ3JFQSxhQUFLLENBQUNDLGNBQU47QUFDQUYseUJBQWlCLENBQUNyQixXQUFsQixDQUE4QixNQUE5Qjs7QUFDQSxZQUFJcUIsaUJBQWlCLENBQUNHLEVBQWxCLENBQXFCLFVBQXJCLENBQUosRUFBc0M7QUFDcENILDJCQUFpQixDQUFDOUQsSUFBbEIsQ0FBdUIsK0JBQXZCLEVBQXdEa0UsS0FBeEQ7QUFDRDtBQUNGLE9BTkQ7QUFPRDtBQWhCK0IsR0FBbEM7QUFtQkE7Ozs7QUFHQSxXQUFTbkIsUUFBVCxHQUFvQjtBQUNsQixRQUFJb0IsU0FBUyxDQUFDQyxTQUFWLENBQW9CakYsS0FBcEIsQ0FBMEIsVUFBMUIsS0FDQ2dGLFNBQVMsQ0FBQ0MsU0FBVixDQUFvQmpGLEtBQXBCLENBQTBCLFFBQTFCLENBREQsSUFFQ2dGLFNBQVMsQ0FBQ0MsU0FBVixDQUFvQmpGLEtBQXBCLENBQTBCLFNBQTFCLENBRkQsSUFHQ2dGLFNBQVMsQ0FBQ0MsU0FBVixDQUFvQmpGLEtBQXBCLENBQTBCLE9BQTFCLENBSEQsSUFJQ2dGLFNBQVMsQ0FBQ0MsU0FBVixDQUFvQmpGLEtBQXBCLENBQTBCLE9BQTFCLENBSkQsSUFLQ2dGLFNBQVMsQ0FBQ0MsU0FBVixDQUFvQmpGLEtBQXBCLENBQTBCLGFBQTFCLENBTEQsSUFNQ2dGLFNBQVMsQ0FBQ0MsU0FBVixDQUFvQmpGLEtBQXBCLENBQTBCLGdCQUExQixDQU5MLEVBT0U7QUFDQSxhQUFPLElBQVA7QUFDRCxLQVRELE1BVUs7QUFDSCxhQUFPLEtBQVA7QUFDRDtBQUNGO0FBRUYsQ0F6UEQsRUF5UEdpQyxNQXpQSCxFIiwiZmlsZSI6ImFwcC5qcyIsInNvdXJjZXNDb250ZW50IjpbIlxuLy8gYXNzZXRzL2pzL2FwcC5qc1xuLypcbiAqIFdlbGNvbWUgdG8geW91ciBhcHAncyBtYWluIEphdmFTY3JpcHQgZmlsZSFcbiAqXG4gKiBXZSByZWNvbW1lbmQgaW5jbHVkaW5nIHRoZSBidWlsdCB2ZXJzaW9uIG9mIHRoaXMgSmF2YVNjcmlwdCBmaWxlXG4gKiAoYW5kIGl0cyBDU1MgZmlsZSkgaW4geW91ciBiYXNlIGxheW91dCAoYmFzZS5odG1sLnR3aWcpLlxuICovXG5cbi8vIGFueSBDU1MgeW91IGltcG9ydCB3aWxsIG91dHB1dCBpbnRvIGEgc2luZ2xlIGNzcyBmaWxlIChhcHAuY3NzIGluIHRoaXMgY2FzZSlcbmltcG9ydCAnLi9hcHAuc2Nzcyc7XG5cbi8vIE5lZWQgalF1ZXJ5PyBJbnN0YWxsIGl0IHdpdGggXCJ5YXJuIGFkZCBqcXVlcnlcIiwgdGhlbiB1bmNvbW1lbnQgdG8gaW1wb3J0IGl0LlxuaW1wb3J0ICQgZnJvbSAnanF1ZXJ5JztcblxuaW1wb3J0ICcuL3NjcmlwdHMvZGluZ19hdmFpbGFiaWxpdHlfbGFiZWxzLmpzJztcbmltcG9ydCAnLi9zY3JpcHRzL3ByYXRjaGV0dC5tYWluLmpzJztcbiIsIi8vIGV4dHJhY3RlZCBieSBtaW5pLWNzcy1leHRyYWN0LXBsdWdpbiIsIi8qKlxuICogQGZpbGVcbiAqIE92ZXJyaWRlIHRoZSBKUyBiZWhhdmlvciBvZiBkaW5nX2F2YWlsYWJpbGl0eV9sYWJlbHMuXG4gKi9cblxuKGZ1bmN0aW9uICgkKSB7XG5cbiAgJ3VzZSBzdHJpY3QnO1xuXG4gIC8vIENhY2hlIG9mIGZldGNoZWQgYXZhaWxhYmlsaXR5IGluZm9ybWF0aW9uLlxuICBEcnVwYWwuREFEQiA9IHt9O1xuXG4gIERydXBhbC5iZWhhdmlvcnMuZGluZ0F2YWlsYWJpbGl0eUF0dGFjaCA9IHtcbiAgICBhdHRhY2g6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuICAgICAgdmFyIGlkcyA9IFtdO1xuICAgICAgdmFyIGh0bWxfaWRzID0gW107XG5cbiAgICAgIC8vIEV4dHJhY3QgZW50aXR5IGlkcyBmcm9tIERydXBhbCBzZXR0aW5ncyBhcnJheS5cbiAgICAgIGlmIChzZXR0aW5ncy5oYXNPd25Qcm9wZXJ0eSgnZGluZ19hdmFpbGFiaWxpdHknKSkge1xuICAgICAgICAkLmVhY2goc2V0dGluZ3MuZGluZ19hdmFpbGFiaWxpdHksIGZ1bmN0aW9uIChpZCwgZW50aXR5X2lkcykge1xuICAgICAgICAgICQuZWFjaChlbnRpdHlfaWRzLCBmdW5jdGlvbiAoaW5kZXgsIGVudGl0eV9pZCkge1xuICAgICAgICAgICAgaWYgKERydXBhbC5EQURCW2VudGl0eV9pZF0gPT09IHVuZGVmaW5lZCkge1xuICAgICAgICAgICAgICBEcnVwYWwuREFEQltlbnRpdHlfaWRdID0gbnVsbDtcbiAgICAgICAgICAgICAgaWRzLnB1c2goZW50aXR5X2lkKTtcbiAgICAgICAgICAgICAgaHRtbF9pZHMucHVzaChpZCk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgfSk7XG4gICAgICAgIH0pO1xuICAgICAgfVxuXG4gICAgICAvLyBGZXRjaCBhdmFpbGFiaWxpdHkuXG4gICAgICBpZiAoaWRzLmxlbmd0aCA+IDApIHtcbiAgICAgICAgdmFyIG1vZGUgPSBzZXR0aW5ncy5kaW5nX2F2YWlsYWJpbGl0eV9tb2RlID8gc2V0dGluZ3MuZGluZ19hdmFpbGFiaWxpdHlfbW9kZSA6ICdpdGVtcyc7XG4gICAgICAgIHZhciBwYXRoID0gc2V0dGluZ3MuYmFzZVBhdGggKyAnZGluZ19hdmFpbGFiaWxpdHkvJyArIG1vZGUgKyAnLycgKyBpZHMuam9pbignLCcpO1xuICAgICAgICAkLmFqYXgoe1xuICAgICAgICAgIGRhdGFUeXBlOiAnanNvbicsXG4gICAgICAgICAgdXJsOiBwYXRoLFxuICAgICAgICAgIHN1Y2Nlc3M6IGZ1bmN0aW9uIChkYXRhKSB7XG4gICAgICAgICAgICAkLmVhY2goZGF0YSwgZnVuY3Rpb24gKGlkLCBpdGVtKSB7XG4gICAgICAgICAgICAgIC8vIFVwZGF0ZSBjYWNoZS5cbiAgICAgICAgICAgICAgRHJ1cGFsLkRBREJbaWRdID0gaXRlbTtcbiAgICAgICAgICAgIH0pO1xuXG4gICAgICAgICAgICAkLmVhY2goc2V0dGluZ3MuZGluZ19hdmFpbGFiaWxpdHksIGZ1bmN0aW9uIChpZCwgZW50aXR5X2lkcykge1xuICAgICAgICAgICAgICBpZiAoaWQubWF0Y2goL15hdmFpbGFiaWxpdHktLykpIHtcbiAgICAgICAgICAgICAgICAvLyBVcGRhdGUgYXZhaWxhYmlsaXR5IGluZGljYXRvcnMuXG4gICAgICAgICAgICAgICAgdXBkYXRlX2F2YWlsYWJpbGl0eShpZCwgZW50aXR5X2lkcyk7XG4gICAgICAgICAgICAgIH1cbiAgICAgICAgICAgIH0pO1xuICAgICAgICAgICAgdXBkYXRlX2F2YWlsYWJpbGl0eV9yZW1vdmVfcGVuZGluZygpO1xuICAgICAgICAgIH0sXG4gICAgICAgICAgZXJyb3I6IGZ1bmN0aW9uICgpIHtcbiAgICAgICAgICAgICQoJ2Rpdi5sb2FkZXInKS5yZW1vdmUoKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0pO1xuICAgICAgfVxuICAgICAgZWxzZSB7XG4gICAgICAgIC8vIEFwcGx5IGFscmVhZHkgZmV0Y2hlZCBhdmFpbGFiaWxpdHksIGlmIGFueS5cbiAgICAgICAgaWYgKHNldHRpbmdzLmhhc093blByb3BlcnR5KCdkaW5nX2F2YWlsYWJpbGl0eScpKSB7XG4gICAgICAgICAgJC5lYWNoKHNldHRpbmdzLmRpbmdfYXZhaWxhYmlsaXR5LCBmdW5jdGlvbiAoaWQsIGVudGl0eV9pZHMpIHtcbiAgICAgICAgICAgIHVwZGF0ZV9hdmFpbGFiaWxpdHkoaWQsIGVudGl0eV9pZHMpO1xuICAgICAgICAgIH0pO1xuICAgICAgICAgIHVwZGF0ZV9hdmFpbGFiaWxpdHlfcmVtb3ZlX3BlbmRpbmcoKTtcbiAgICAgICAgfVxuICAgICAgfVxuXG4gICAgICAvKipcbiAgICAgICAqIFVwZGF0ZSBhdmFpbGFiaWxpdHkgb24gdGhlIHBhZ2UuXG4gICAgICAgKlxuICAgICAgICogVGhlIGFycmF5IG9mIGVudGl0eV9pZHMgaXMgYW4gYXJyYXkgYXMgd2Ugb25seSBzaG93IG9uZSBhdmFpbGFiaWxpdHlcbiAgICAgICAqIGxhYmVsIHBlciBtYXRlcmlhbCB0eXBlLiBTbyBpZiBvbmUgb2YgdGhlc2UgaGF2ZSBhbiBhdmFpbGFibGUgc3RhdHVzXG4gICAgICAgKiB0aGUgbGFiZWwgaGF2ZSB0byByZWZsZWN0IHRoaXMuXG4gICAgICAgKiBAcGFyYW0gaWQge251bWJlcn0gVGhlIGVsZW1lbnQgaWQgdGhhdCB0aGlzIHNob3VsZCB0YXJnZXQuXG4gICAgICAgKiBAcGFyYW0gZW50aXR5X2lkcyB7bnVtYmVyW119IEFycmF5IG9mIGVudGl0aWVzLlxuICAgICAgICovXG4gICAgICBmdW5jdGlvbiB1cGRhdGVfYXZhaWxhYmlsaXR5KGlkLCBlbnRpdHlfaWRzKSB7XG4gICAgICAgIC8vIERlZmF1bHQgdGhlIHN0YXR1cyB0byBub3QgYXZhaWxhYmxlIGFuZCBub3QgcmVzZXJ2YWJsZS5cbiAgICAgICAgdmFyIHN0YXR1cyA9IHtcbiAgICAgICAgICBhdmFpbGFibGU6IGZhbHNlLFxuICAgICAgICAgIHJlc2VydmFibGU6IGZhbHNlXG4gICAgICAgIH07XG5cbiAgICAgICAgLy8gTG9vcCBvdmVyIHRoZSBlbnRpdHkgaWRzIGFuZCBpZiBvbmUgaGFzIGF2YWlsYWJsZSBvciByZXNlcnZhYmxlXG4gICAgICAgIC8vIHRydWUgc2F2ZSB0aGF0IHZhbHVlLlxuICAgICAgICAkLmVhY2goZW50aXR5X2lkcywgZnVuY3Rpb24gKGluZGV4LCBlbnRpdHlfaWQpIHtcbiAgICAgICAgICBpZiAoRHJ1cGFsLkRBREJbZW50aXR5X2lkXSkge1xuICAgICAgICAgICAgc3RhdHVzLmF2YWlsYWJsZSA9IHN0YXR1cy5hdmFpbGFibGUgfHwgRHJ1cGFsLkRBREJbZW50aXR5X2lkXVsnYXZhaWxhYmxlJ107XG4gICAgICAgICAgICBzdGF0dXMucmVzZXJ2YWJsZSA9IHN0YXR1cy5yZXNlcnZhYmxlIHx8IERydXBhbC5EQURCW2VudGl0eV9pZF1bJ3Jlc2VydmFibGUnXTtcbiAgICAgICAgICB9XG4gICAgICAgIH0pO1xuXG4gICAgICAgIHZhciBlbGVtZW50ID0gJCgnIycgKyBpZCk7XG4gICAgICAgIGVsZW1lbnQucmVtb3ZlQ2xhc3MoJ3BlbmRpbmcnKS5hZGRDbGFzcygncHJvY2Vzc2VkJyk7XG5cbiAgICAgICAgLy8gR2V0IGhvbGQgb2YgdGhlIHJlc2VydmUgYnV0dG9uIChpdCBoaWRkZW4gYXMgZGVmYXVsdCwgc28gd2UgbWF5IG5lZWRcbiAgICAgICAgLy8gdG8gc2hvdyBpdCkuXG4gICAgICAgIHZhciByZXNlcnZlcl9idG4gPSBlbGVtZW50LnBhcmVudHMoJy50aW5nLW9iamVjdDpmaXJzdCcpLmZpbmQoJ1tpZF49ZGluZy1yZXNlcnZhdGlvbi1yZXNlcnZlLWZvcm1dJyk7XG5cbiAgICAgICAgdXBkYXRlX2F2YWlsYWJpbGl0eV9lbGVtZW50cyhlbGVtZW50LCByZXNlcnZlcl9idG4sIHN0YXR1cyk7XG4gICAgICB9XG5cbiAgICAgIC8qKlxuICAgICAgICogSGVscGVyIGZ1bmN0aW9uIHRvIG1vdmUgdGhlIG1hdGVyaWFscyBiYXNlZCBvbiBhdmFpbGFiaWxpdHkuXG4gICAgICAgKiBAcGFyYW0gZWxlbWVudCB7T2JqZWN0fSBUaGUgdGFyZ2V0IGVsZW1lbnQgKG1hdGVyaWFsIHRoYXQgc2hvdWxkIGJlIG1vdmVkKS5cbiAgICAgICAqIEBwYXJhbSBzdGF0dXMge3N0cmluZ30gU3RydWN0dXJlIHdpdGggYXZhaWxhYmxlIGFuZCByZXNlcnZhYmxlIHN0YXRlLlxuICAgICAgICovXG4gICAgICBmdW5jdGlvbiB1cGRhdGVfYXZhaWxhYmlsaXR5X3R5cGUoZWxlbWVudCwgc3RhdHVzKSB7XG4gICAgICAgIHZhciBncm91cHNfd3JhcHBlciA9IGVsZW1lbnQuY2xvc2VzdCgnLnNlYXJjaC1yZXN1bHQtLWF2YWlsYWJpbGl0eScpO1xuICAgICAgICB2YXIgcmVzZXJ2YWJsZSA9IHN0YXR1c1sncmVzZXJ2YWJsZSddO1xuICAgICAgICB2YXIgYXZhaWxhYmxlID0gc3RhdHVzWydhdmFpbGFibGUnXTtcblxuICAgICAgICB2YXIgZ3JvdXAgPSBudWxsO1xuICAgICAgICBpZiAoJCgnLmpzLW9ubGluZScsIGdyb3Vwc193cmFwcGVyKS5sZW5ndGggIT09IDApIHtcbiAgICAgICAgICBncm91cCA9ICQoJy5qcy1vbmxpbmUnLCBncm91cHNfd3JhcHBlcik7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSBpZiAoYXZhaWxhYmxlKSB7XG4gICAgICAgICAgZ3JvdXAgPSAkKCcuanMtYXZhaWxhYmxlJywgZ3JvdXBzX3dyYXBwZXIpO1xuXG4gICAgICAgICAgaWYgKGdyb3VwLmxlbmd0aCA9PT0gMCkge1xuICAgICAgICAgICAgZ3JvdXAgPSAkKCc8cCBjbGFzcz1cImpzLWF2YWlsYWJsZVwiPjwvcD4nKTtcbiAgICAgICAgICAgIGdyb3Vwc193cmFwcGVyLmFwcGVuZChncm91cCk7XG4gICAgICAgICAgfVxuICAgICAgICB9XG4gICAgICAgIGVsc2UgaWYgKHJlc2VydmFibGUpIHtcbiAgICAgICAgICBncm91cCA9ICQoJy5qcy1yZXNlcnZhYmxlJywgZ3JvdXBzX3dyYXBwZXIpO1xuICAgICAgICAgIGlmIChncm91cC5sZW5ndGggPT09IDApIHtcbiAgICAgICAgICAgIGdyb3VwID0gJCgnPHAgY2xhc3M9XCJqcy1yZXNlcnZhYmxlXCI+PC9wPicpO1xuICAgICAgICAgICAgZ3JvdXBzX3dyYXBwZXIuYXBwZW5kKGdyb3VwKTtcbiAgICAgICAgICB9XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSB7XG4gICAgICAgICAgZ3JvdXAgPSAkKCcuanMtdW5hdmFpbGFibGUnLCBncm91cHNfd3JhcHBlcik7XG5cbiAgICAgICAgICBpZiAoZ3JvdXAubGVuZ3RoID09PSAwKSB7XG4gICAgICAgICAgICBncm91cCA9ICQoJzxwIGNsYXNzPVwianMtdW5hdmFpbGFibGVcIj48L3A+Jyk7XG4gICAgICAgICAgICBncm91cHNfd3JhcHBlci5hcHBlbmQoZ3JvdXApO1xuICAgICAgICAgIH1cbiAgICAgICAgfVxuXG4gICAgICAgIC8vIE1vdmUgdGhlIGVsZW1lbnQgaW50byB0aGF0IHR5cGUuXG4gICAgICAgIGdyb3VwLmFwcGVuZChlbGVtZW50KTtcbiAgICAgIH1cblxuICAgICAgLyoqXG4gICAgICAgKiBSZW1vdmUgcGVuZGluZyBncm91cHMuXG4gICAgICAgKlxuICAgICAgICogUmVtb3ZlcyBqcy1wZW5kaW5nIGdyb3VwcyAobGFiZWxzKSBpZiB0aGV5IGFyZSBlbXB0eS4gVGhpc1xuICAgICAgICogc2hvdWxkIGJlIGNhbGxlZCBhcyB0aGUgbGFzdCBmdW5jdGlvbiBpbiB1cGRhdGluZ1xuICAgICAgICogYXZhaWxhYmlsaXR5IGluZm9ybWF0aW9uIGFuZCBzZWUgYXMgYSBjbGVhbi11cCBmdW5jdGlvbi5cbiAgICAgICAqL1xuICAgICAgZnVuY3Rpb24gdXBkYXRlX2F2YWlsYWJpbGl0eV9yZW1vdmVfcGVuZGluZygpIHtcbiAgICAgICAgLy8gTG9vcCBvdmVyIGFsbCBwZW5kaW5nIGF2YWlsYWJpbGl0eSBncm91cHMuXG4gICAgICAgICQoJy5qcy1wZW5kaW5nJykuZWFjaChmdW5jdGlvbiAoKSB7XG4gICAgICAgICAgdmFyIGVsbSA9ICQodGhpcyk7XG4gICAgICAgICAgdmFyIGNoaWxkcmVuID0gZWxtLmNoaWxkcmVuKCk7XG4gICAgICAgICAgaWYgKCFjaGlsZHJlbi5sZW5ndGgpIHtcbiAgICAgICAgICAgIC8vIFRoZSBjdXJyZW50IHBlbmRpbmcgZ3JvdXAgaXMgZW1wdHksIHNvIHNpbXBseSByZW1vdmUgaXQuXG4gICAgICAgICAgICBlbG0ucmVtb3ZlKCk7XG4gICAgICAgICAgfVxuICAgICAgICB9KTtcbiAgICAgIH1cblxuICAgICAgLyoqXG4gICAgICAgKiBBZGQgY2xhc3MgdG8gYm90aCBhbiBlbGVtZW50IGFuZCB0aGUgcmVzZXJ2YXRpb24gYnV0dG9uLlxuICAgICAgICpcbiAgICAgICAqIEBwYXJhbSBlbGVtZW50XG4gICAgICAgKiAgIGpRdWVyeSBhdmFpbGFiaWxpdHkgZWxlbWVudCB0byBhZGQgdGhlIGNsYXNzIHRvLlxuICAgICAgICogQHBhcmFtIGJ0blxuICAgICAgICogICBSZXNlcnZhdGlvbiBidXR0b24gdG8gYWRkIHRoZSBjbGFzcyB0by5cbiAgICAgICAqIEBwYXJhbSBzdGF0dXNcbiAgICAgICAqICAgU3RydWN0dXJlIHdpdGggYXZhaWxhYmxlIGFuZCByZXNlcnZhYmxlIHN0YXRlLlxuICAgICAgICovXG4gICAgICBmdW5jdGlvbiB1cGRhdGVfYXZhaWxhYmlsaXR5X2VsZW1lbnRzKGVsZW1lbnQsIGJ0biwgc3RhdHVzKSB7XG4gICAgICAgIHZhciBjbGFzc19uYW1lID0gbnVsbDtcblxuICAgICAgICBmb3IgKHZhciBpIGluIHN0YXR1cykge1xuICAgICAgICAgIGlmIChzdGF0dXNbaV0gPT09IHRydWUpIHtcbiAgICAgICAgICAgIGNsYXNzX25hbWUgPSBpO1xuICAgICAgICAgIH1cbiAgICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgIGlmIChpID09PSAnYXZhaWxhYmxlJykge1xuICAgICAgICAgICAgICBjbGFzc19uYW1lID0gJ3VuJyArIGk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBlbHNlIGlmIChpID09PSAncmVzZXJ2YWJsZScpIHtcbiAgICAgICAgICAgICAgY2xhc3NfbmFtZSA9ICdub3QtJyArIGk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgfVxuXG4gICAgICAgICAgZWxlbWVudC5hZGRDbGFzcyhjbGFzc19uYW1lKTtcbiAgICAgICAgICBpZiAoYnRuLmxlbmd0aCkge1xuICAgICAgICAgICAgYnRuLmFkZENsYXNzKGNsYXNzX25hbWUpO1xuICAgICAgICAgIH1cbiAgICAgICAgfVxuXG4gICAgICAgICQoZWxlbWVudCkub25jZSgncmVvbC1hdmFpbGFiaWxpdHknLCBmdW5jdGlvbiAoKSB7XG4gICAgICAgICAgLy8gVE9ETzogdGhpcyBpcyB2ZXJ5IGZyYWdpbGUuXG4gICAgICAgICAgdmFyIHR5cGVfbmFtZSA9IGVsZW1lbnQudGV4dCgpLnRvTG93ZXJDYXNlKCk7XG4gICAgICAgICAgdmFyIHN0cmluZztcblxuICAgICAgICAgIGlmIChEcnVwYWwuc2V0dGluZ3MuZGluZ19hdmFpbGFiaWxpdHlfdHlwZV9tYXBwaW5nW3R5cGVfbmFtZV0pIHtcbiAgICAgICAgICAgIHR5cGVfbmFtZSA9IERydXBhbC5zZXR0aW5ncy5kaW5nX2F2YWlsYWJpbGl0eV90eXBlX21hcHBpbmdbdHlwZV9uYW1lXTtcbiAgICAgICAgICB9XG5cbiAgICAgICAgICBpZiAoc3RhdHVzWydhdmFpbGFibGUnXSA9PT0gdHJ1ZSkge1xuICAgICAgICAgICAgc3RyaW5nID0gRHJ1cGFsLnNldHRpbmdzLmRpbmdfYXZhaWxhYmlsaXR5X3R5cGVfc3RyaW5nc1snYXZhaWxhYmxlJ107XG4gICAgICAgICAgICBlbGVtZW50LnRleHQoRHJ1cGFsLmZvcm1hdFN0cmluZyhzdHJpbmcsIHsnQHR5cGUnOiB0eXBlX25hbWV9KSk7XG4gICAgICAgICAgfVxuICAgICAgICAgIGVsc2UgaWYgKHN0YXR1c1sncmVzZXJ2YWJsZSddID09PSB0cnVlKSB7XG4gICAgICAgICAgICBzdHJpbmcgPSBEcnVwYWwuc2V0dGluZ3MuZGluZ19hdmFpbGFiaWxpdHlfdHlwZV9zdHJpbmdzWydyZXNlcnZhYmxlJ107XG4gICAgICAgICAgICBlbGVtZW50LnRleHQoRHJ1cGFsLmZvcm1hdFN0cmluZyhzdHJpbmcsIHsnQHR5cGUnOiB0eXBlX25hbWV9KSk7XG4gICAgICAgICAgfVxuICAgICAgICB9KTtcblxuICAgICAgICB1cGRhdGVfYXZhaWxhYmlsaXR5X3R5cGUoZWxlbWVudCwgc3RhdHVzKTtcbiAgICAgIH1cbiAgICB9XG4gIH07XG59KShqUXVlcnkpO1xuIiwiLyoqXG4gKiBAZmlsZVxuICogTWFpbiBqYXZhc2NyaXB0IGZpbGUgZm9yIFByYXRjaGV0dCB0aGVtZS5cbiAqL1xuXG4oZnVuY3Rpb24gKCQpIHtcblxuICAndXNlIHN0cmljdCc7XG5cbiAgLy8gRGlzYWJsZSBBSkFYIHJlcXVlc3QgZXJyb3IgcG9wdXAuIE9uIG1vYmlsZSBTYWZhcmkgdGhlXG4gIC8vIGF1dG9jb21wbGV0ZSBBSkFYIHJlcXVlc3QgZ2V0cyB0b3JuIGRvd24gYmVmb3JlIERydXBhbHMgZXZlbnRcbiAgLy8gaGFuZGxlciBvbiBiZWZvcmV1bmxvYWQgYW5kIHBhZ2VoaWRlIGlzIHRyaWdnZXJlZCwgc28gdGhlIGxvZ2ljXG4gIC8vIHRvIHN1cHByZXNzIGFuIGVycm9yIHBvcHVwIGlzIG5vbiB0cmlnZ2VyZWQuIEV2ZW4gdGhlIGZvcm0gc3VibWl0XG4gIC8vIGhhbmRsZXIgY2FuIGJlIGNhbGxlZCBhZnRlciB0aGUgQUpBWCByZXF1ZXN0IGlzIGtpbGxlZCwgc29cbiAgLy8gc2V0dGluZyB0aGlzIHRoZXJlIGRvZXNuJ3QgaGVscC4gQXMgZW5kIHVzZXJzIGRvbid0IHVuZGVyc3RhbmRcbiAgLy8gdGhlIHBvcHVwIGFueXdheSwgd2UgY29tcGxldGVseSBkaXNhYmxlIGl0LlxuICAvLyBTZWUgbWlzYy9kcnVwYWwuanMgdG8gaG93IHRoaXMgd29ya3MuXG4gIERydXBhbC5iZWZvcmVVbmxvYWRDYWxsZWQgPSB0cnVlO1xuXG4gIC8vIFNjcm9sbCB0byB0b3Agd2hlbiBvcGVuaW5nIGEgZGlhbG9nLiBEaWFsb2dzIG9uIHRoaXMgc2l0ZSBjYW4gZ2V0XG4gIC8vIHByZXR0eSBiaWcgLSBlLmcuIHdoZW4gdmlld2luZyBhIHJlYWRpbmcgc2FtcGxlLiBUaGlzIGlzXG4gIC8vIGZ1cnRoZXJtb3JlIHByb2JsZW1hdGljIGFzIHNjcm9sbGluZyBpcyBkaXNhYmxlZC4gSW4gX3BvcHVwLnNjc3NcbiAgLy8gd2UgZm9yY2UgdGhlIHBvcHVwIHRvIHRoZSB0b3Agb2YgdGhlIHBhZ2UuIGpRdWVyeSBVSSBzaG91bGRcbiAgLy8gc2Nyb2xsIHRoZSB2aWV3cG9ydCB0byBtYWtlIHRoZSBwb3B1cCB2aXNpYmxlIGJ1dCBzY3JvbGxpbmcgZG9lc1xuICAvLyBub3QgaGFwcGVuIG9uIE1vYmlsZSBzYWZhcmkgYW5kIHRoZSBwb3B1cCBpcyByZW5kZXJlZCBvdXQgb2ZcbiAgLy8gc2lnaHQuIFRoaXMgZm9yY2VzIHRoZSBicm93c2VyIHRvIHNjcm9sbCB0byB0aGUgdG9wIG9mIHRoZSBwYWdlXG4gIC8vIHdoZW4gYSBwb3B1cCBpcyBvcGVuZWQuXG4gIERydXBhbC5iZWhhdmlvcnMubW9kYWxTY3JvbGwgPSB7XG4gICAgYXR0YWNoIDogZnVuY3Rpb24gKCkge1xuICAgICAgJCgnYm9keScpLmJpbmQoJ2RpYWxvZ29wZW4nLCBmdW5jdGlvbiAoKSB7XG4gICAgICAgIHdpbmRvdy5zY3JvbGxUbygwLCAwKTtcbiAgICAgIH0pO1xuICAgIH1cbiAgfTtcblxuICBqUXVlcnkuZm4uZXh0ZW5kKHtcbiAgICB2aWV3UGlja2VyOiBmdW5jdGlvbiAodmlld1BpY2tlcldyYXBwZXIpIHtcblxuICAgICAgdmFyIHdyYXBwZXIgPSAkKHRoaXMpO1xuXG4gICAgICB2YXIgZ3JpZENsYXNzID0gJ2pzLXNlYXJjaC1yZXN1bHRzLWdyaWQtdmlldyc7XG4gICAgICB2YXIgdmlld1R5cGUgPSBsb2NhbFN0b3JhZ2UuZ2V0SXRlbSgnYnJlb2wtc2VhcmNoLXZpZXctdHlwZScpO1xuXG4gICAgICBpZiAodmlld1R5cGUgPT09IG51bGwpIHtcbiAgICAgICAgdmlld1R5cGUgPSAnZ3JpZCc7XG4gICAgICAgIGxvY2FsU3RvcmFnZS5zZXRJdGVtKCdicmVvbC1zZWFyY2gtdmlldy10eXBlJywgdmlld1R5cGUpO1xuICAgICAgfVxuXG4gICAgICBpZiAodmlld1R5cGUgPT09ICdncmlkJykge1xuICAgICAgICB3cmFwcGVyLmFkZENsYXNzKGdyaWRDbGFzcyk7XG4gICAgICB9XG5cbiAgICAgIC8vIElmIHRoZSBtaW5pIHBhbmVsIGV4aXN0IHdlIHdpbGwgY29udGludWUuXG4gICAgICBpZiAod3JhcHBlci5sZW5ndGggIT09IDApIHtcbiAgICAgICAgdmFyIHZpZXdQaWNrZXIgPSBnZXRWaWV3UGlja2VyKHZpZXdUeXBlKTtcblxuICAgICAgICAkKHZpZXdQaWNrZXJXcmFwcGVyKS5hZnRlcih2aWV3UGlja2VyKTtcblxuICAgICAgICAvLyBMaXN0ZW4gZm9yIHVzZXIgaW5wdXQuXG4gICAgICAgICQoJy52aWV3LXBpY2tlcl9faXRlbScpLmNsaWNrKGZ1bmN0aW9uICgpIHtcbiAgICAgICAgICB2aWV3VHlwZSA9ICQodGhpcykuYXR0cignZGF0YS12aWV3LXR5cGUnKTtcblxuICAgICAgICAgIC8vIEFwcGx5IGNsYXNzZXMgZGVwZW5kaW5nIG9uIHVzZXIgY2hvaWNlLlxuICAgICAgICAgIGlmICghJCh0aGlzKS5oYXNDbGFzcygnYWN0aXZlJykpIHtcblxuICAgICAgICAgICAgJCgnLnZpZXctcGlja2VyX19pdGVtJykudG9nZ2xlQ2xhc3MoJ2FjdGl2ZScpO1xuXG4gICAgICAgICAgICBpZiAodmlld1R5cGUgPT09ICdncmlkJykge1xuICAgICAgICAgICAgICB3cmFwcGVyLmFkZENsYXNzKGdyaWRDbGFzcyk7XG4gICAgICAgICAgICB9XG4gICAgICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgICAgd3JhcHBlci5yZW1vdmVDbGFzcyhncmlkQ2xhc3MpO1xuICAgICAgICAgICAgfVxuXG4gICAgICAgICAgICAvLyBTdG9yZSB0aGUgbGFzdCBjaG9zZW4gdmlldyB0eXBlIGluIGxvY2Fsc3RvcmFnZS5cbiAgICAgICAgICAgIGxvY2FsU3RvcmFnZS5zZXRJdGVtKCdicmVvbC1zZWFyY2gtdmlldy10eXBlJywgdmlld1R5cGUpO1xuICAgICAgICAgIH1cbiAgICAgICAgfSk7XG4gICAgICB9XG5cbiAgICAgIGZ1bmN0aW9uIGdldFZpZXdQaWNrZXIodmlld1R5cGUpIHtcbiAgICAgICAgdmFyIHZpZXdQaWNrZXIgPSAkKCc8ZGl2IGNsYXNzPVwidmlldy1waWNrZXJcIj48L2Rpdj4nKTtcbiAgICAgICAgdmFyIGxpc3RQaWNrZXIgPSAkKCc8ZGl2IGNsYXNzPVwidmlldy1waWNrZXJfX2l0ZW0gbGlzdC12aWV3XCIgZGF0YS12aWV3LXR5cGU9XCJsaXN0XCI+PC9kaXY+Jyk7XG4gICAgICAgIHZhciBncmlkUGlja2VyID0gJCgnPGRpdiBjbGFzcz1cInZpZXctcGlja2VyX19pdGVtIGdyaWQtdmlld1wiIGRhdGEtdmlldy10eXBlPVwiZ3JpZFwiPjwvZGl2PicpO1xuXG4gICAgICAgIGlmICh2aWV3VHlwZSA9PT0gJ2xpc3QnKSB7XG4gICAgICAgICAgbGlzdFBpY2tlci5hZGRDbGFzcygnYWN0aXZlJyk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSB7XG4gICAgICAgICAgZ3JpZFBpY2tlci5hZGRDbGFzcygnYWN0aXZlJyk7XG4gICAgICAgIH1cblxuICAgICAgICByZXR1cm4gdmlld1BpY2tlci5hcHBlbmQobGlzdFBpY2tlciwgZ3JpZFBpY2tlcik7XG4gICAgICB9XG4gICAgfVxuICB9KTtcblxuICAvKipcbiAgICogQWRkIGdyaWQgdmlldyBvcHRpb24uXG4gICAqL1xuICBEcnVwYWwuYmVoYXZpb3JzLmdyaWRWaWV3ID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuICAgICAgJCgnLnBhZ2Utc2VhcmNoLXRpbmcnKS52aWV3UGlja2VyKCcucGFuZS10aW5nLXNlYXJjaC1zb3J0LWZvcm0nKTtcbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIE1ha2Ugc3VyZSBvdmVybGF5IGFyZSBuZXZlciBzaG93biBvbiBpbml0aWFsIHBhZ2Ugc2hvdy5cbiAgICpcbiAgICogQmVjYXVzZSBpbmNvbnNpc3RlbnQgY3Jvc3MtYnJvd3NlciBiZWhhdmlvdXIsIHdlIHdpbGwgYWx3YXlzXG4gICAqIGNoZWNrIGlmIHRoZSBzZWFyY2ggb3ZlcmxheSBpcyBpbmplY3RlZCBpbnRvIHRoZSBkb20gYW5kIGlmIGl0XG4gICAqIGlzLCB3ZSB3aWxsIHJlbW92ZS4gVGhpcyBwcmV2ZW50cyB1c2VycyBmcm9tIHNlaW5nIHRoZSBvdmVybGF5XG4gICAqIHdoZW4gdXNpbmcgdGhlIGJhY2sgYnV0dG9uLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy5vdmVybGF5ID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuICAgICAgJCh3aW5kb3cpLmJpbmQoJ3BhZ2VzaG93JywgZnVuY3Rpb24gKCkge1xuICAgICAgICB2YXIgb3ZlcmxheSA9ICQoJy5zZWFyY2gtb3ZlcmxheS0td3JhcHBlcicpO1xuICAgICAgICBpZiAob3ZlcmxheS5sZW5ndGggIT09IDApIHtcbiAgICAgICAgICBvdmVybGF5LnJlbW92ZSgpO1xuICAgICAgICB9XG4gICAgICB9KTtcbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIERldGVjdCB0YWJsZXRzIGFuZCBtb2JpbGUgZGV2aWNlcy5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMuaXNEZXNrdG9wID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuXG4gICAgICAvLyBBZGQgY2xhc3MgaWYgd2UgYXJlIG9uIGRlc2t0b3AuXG4gICAgICBpZiAoIWlzTW9iaWxlKCkpIHtcbiAgICAgICAgJCgnYm9keScpLmFkZENsYXNzKCdpcy1kZXNrdG9wJyk7XG4gICAgICB9XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBUb2dnbGUgdGhlIGZvb3RlciBtZW51cy5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMuZm9vdGVyVG9nZ2xlID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuXG4gICAgICAkKCcuZm9vdGVyIC5wYW5lLXRpdGxlJywgY29udGV4dCkuY2xpY2soZnVuY3Rpb24gKCkge1xuXG4gICAgICAgIHZhciBlbGVtZW50ID0gJCh0aGlzKS5uZXh0KCkuZmluZCgndWwnKTtcblxuICAgICAgICAvLyBNYWtlIHN1cmUgdGhlIHJpZ2h0IGNsYXNzZXMgYXJlIGFkZGVkLCBzbyB3ZSBjYW5cbiAgICAgICAgLy8gbWFrZSBzdXJlIHRoZSBhcnJvdyBwb2ludHMgaW4gdGhlIHJpZ2h0IGRpcmVjdGlvbi5cbiAgICAgICAgaWYgKGVsZW1lbnQuY3NzKCdkaXNwbGF5JykgPT09ICdub25lJykge1xuICAgICAgICAgICQoZWxlbWVudCkuc2xpZGVEb3duKDIwMCk7XG4gICAgICAgICAgJCh0aGlzKS5hZGRDbGFzcygnb3BlbicpO1xuICAgICAgICAgICQodGhpcykucmVtb3ZlQ2xhc3MoJ2Nsb3NlZCcpO1xuICAgICAgICB9XG4gICAgICAgIGVsc2Uge1xuICAgICAgICAgICQodGhpcykucmVtb3ZlQ2xhc3MoJ29wZW4nKTtcbiAgICAgICAgICAkKHRoaXMpLmFkZENsYXNzKCdjbG9zZWQnKTtcbiAgICAgICAgICAkKGVsZW1lbnQpLnNsaWRlVXAoMjAwKTtcbiAgICAgICAgfVxuICAgICAgfSk7XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBNb2RpZnkgdGhlIERPTS5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMuYXZhaWxhYmlsaXR5QXR0YWNoID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuICAgICAgJCgnLnNlYXJjaC1zbmlwcGV0LWluZm8nKS5lYWNoKGZ1bmN0aW9uICgpIHtcbiAgICAgICAgJCh0aGlzKS5hZGRDbGFzcygnanMtcHJvY2Vzc2VkJyk7XG4gICAgICAgIHZhciBtZXRhRGF0YSA9ICQodGhpcykuZmluZCgnLnRpbmctb2JqZWN0LXJpZ2h0JywgY29udGV4dCk7XG4gICAgICAgIHZhciBhdmFpbGFiaWxpdHkgPSAkKHRoaXMpLmZpbmQoJy5zZWFyY2gtcmVzdWx0LS1hdmFpbGFiaWxpdHknKTtcbiAgICAgICAgbWV0YURhdGEuYXBwZW5kKGF2YWlsYWJpbGl0eSk7XG4gICAgICB9KTtcbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIE1ha2UgdGluZyBvYmplY3QgZGV0YWlscyBjb2xsYXBzaWJsZS5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMudGluZ09iamVjdCA9IHtcbiAgICBhdHRhY2ggOiBmdW5jdGlvbiAoY29udGV4dCwgc2V0dGluZ3MpIHtcbiAgICAgICQoJy5qcy1jb2xsYXBzJykuZWFjaChmdW5jdGlvbiAoaWQsIGVsZW1lbnQpIHtcbiAgICAgICAgJChlbGVtZW50KS5maW5kKCcudGluZy1yZWxhdGlvbnNfX2NvbnRlbnQnKS5oaWRlKCk7XG4gICAgICAgICQoZWxlbWVudCkuZmluZCgnaDInKS5maXJzdCgpLmNsaWNrKGZ1bmN0aW9uICgpIHtcbiAgICAgICAgICAkKGVsZW1lbnQpLmZpbmQoJy50aW5nLXJlbGF0aW9uc19fY29udGVudCcpLnNsaWRlVG9nZ2xlKCk7XG4gICAgICAgIH0pO1xuICAgICAgfSk7XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBEZXRlY3QgaWYganF1ZXJ5IHVpLWRpYWxvZyBpcyBvcGVuLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy51aURpYWxvZyA9IHtcbiAgICBhdHRhY2ggOiBmdW5jdGlvbiAoY29udGV4dCwgc2V0dGluZ3MpIHtcbiAgICAgIGlmICgkKCcudWktZGlhbG9nJywgY29udGV4dCkuY3NzKCdkaXNwbGF5JykgPT0gJ25vbmUnIHx8ICQoJy51aS1kaWFsb2cnKS5sZW5ndGggPT09IDApIHtcbiAgICAgICAgLy8gRmFsbGJhY2suXG4gICAgICAgICQoJ2JvZHknKS5yZW1vdmVDbGFzcygndWktZGlhbG9nLWlzLW9wZW4nKTtcbiAgICAgIH1cbiAgICAgIGVsc2Uge1xuICAgICAgICAvLyBBZGQgQ2xhc3MgdGhhdCBpbmRpY2F0ZXMgdGhlIGRpYWxvZyBpcyBvcGVuLlxuICAgICAgICAkKCdib2R5JykuYWRkQ2xhc3MoJ3VpLWRpYWxvZy1pcy1vcGVuJyk7XG5cbiAgICAgICAgLy8gTWFrZSBzdXJlIHdlIHJlbW92ZSB0aGUgY2xhc3Mgd2hlbiB1c2VycyBjbG9zZSB0aGUgZGlhbG9nLlxuICAgICAgICAkKCcudWktYnV0dG9uLWljb24tcHJpbWFyeScpLmNsaWNrKGZ1bmN0aW9uICgpIHtcbiAgICAgICAgICAkKCdib2R5JykucmVtb3ZlQ2xhc3MoJ3VpLWRpYWxvZy1pcy1vcGVuJyk7XG4gICAgICAgIH0pO1xuICAgICAgfVxuICAgIH1cbiAgfTtcblxuICAvKipcbiAgICogU2VhcmNoIGRyb3AgZG93bi5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMuc2VhcmNoRHJvcERvd24gPSB7XG4gICAgYXR0YWNoIDogZnVuY3Rpb24gKGNvbnRleHQsIHNldHRpbmdzKSB7XG4gICAgICAvLyBJZiB0aGUgYmxvY2sgaXMgbm90IHByZXNlbnQgaW4gdGhlIERPTSBhYm9ydC5cbiAgICAgIGlmICgkKCcuanMtc2VhcmNoLWZvcm0nKS5sZW5ndGggPT09IDApIHtcbiAgICAgICAgcmV0dXJuO1xuICAgICAgfVxuXG4gICAgICB2YXIgc2VhcmNoRm9ybVdyYXBwZXIgPSAkKCcuanMtc2VhcmNoLWZvcm0nLCBjb250ZXh0KTtcblxuICAgICAgJCgnLmpzLXNlYXJjaC1mb3JtLXRyaWdnZXInLCBzZWFyY2hGb3JtV3JhcHBlcikuY2xpY2soZnVuY3Rpb24gKGV2ZW50KSB7XG4gICAgICAgIGV2ZW50LnByZXZlbnREZWZhdWx0KCk7XG4gICAgICAgIHNlYXJjaEZvcm1XcmFwcGVyLnRvZ2dsZUNsYXNzKCdvcGVuJyk7XG4gICAgICAgIGlmIChzZWFyY2hGb3JtV3JhcHBlci5pcygnOnZpc2libGUnKSkge1xuICAgICAgICAgIHNlYXJjaEZvcm1XcmFwcGVyLmZpbmQoJ2lucHV0W25hbWU9c2VhcmNoX2Jsb2NrX2Zvcm1dJykuZm9jdXMoKTtcbiAgICAgICAgfVxuICAgICAgfSk7XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBEZXRlY3QgaWYgd2UgYXJlIG9uIG1vYmlsZSBkZXZpY2VzLlxuICAgKi9cbiAgZnVuY3Rpb24gaXNNb2JpbGUoKSB7XG4gICAgaWYgKG5hdmlnYXRvci51c2VyQWdlbnQubWF0Y2goL0FuZHJvaWQvaSlcbiAgICAgIHx8IG5hdmlnYXRvci51c2VyQWdlbnQubWF0Y2goL3dlYk9TL2kpXG4gICAgICB8fCBuYXZpZ2F0b3IudXNlckFnZW50Lm1hdGNoKC9pUGhvbmUvaSlcbiAgICAgIHx8IG5hdmlnYXRvci51c2VyQWdlbnQubWF0Y2goL2lQYWQvaSlcbiAgICAgIHx8IG5hdmlnYXRvci51c2VyQWdlbnQubWF0Y2goL2lQb2QvaSlcbiAgICAgIHx8IG5hdmlnYXRvci51c2VyQWdlbnQubWF0Y2goL0JsYWNrQmVycnkvaSlcbiAgICAgIHx8IG5hdmlnYXRvci51c2VyQWdlbnQubWF0Y2goL1dpbmRvd3MgUGhvbmUvaSlcbiAgICApIHtcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIH1cbiAgICBlbHNlIHtcbiAgICAgIHJldHVybiBmYWxzZTtcbiAgICB9XG4gIH1cblxufSkoalF1ZXJ5KTtcbiJdLCJzb3VyY2VSb290IjoiIn0=