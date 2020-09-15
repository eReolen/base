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
/* harmony import */ var _scripts_wille_main_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./scripts/wille.main.js */ "./assets/scripts/wille.main.js");
/* harmony import */ var _scripts_wille_main_js__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_scripts_wille_main_js__WEBPACK_IMPORTED_MODULE_2__);
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

/***/ "./assets/scripts/wille.main.js":
/*!**************************************!*\
  !*** ./assets/scripts/wille.main.js ***!
  \**************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

/* WEBPACK VAR INJECTION */(function(jQuery) {__webpack_require__(/*! core-js/modules/es.array.find */ "./node_modules/core-js/modules/es.array.find.js");

__webpack_require__(/*! core-js/modules/es.regexp.exec */ "./node_modules/core-js/modules/es.regexp.exec.js");

__webpack_require__(/*! core-js/modules/es.string.match */ "./node_modules/core-js/modules/es.string.match.js");

__webpack_require__(/*! core-js/modules/web.timers */ "./node_modules/core-js/modules/web.timers.js");

/**
 * @file
 * Main javascript file for Wille theme.
 */
(function ($) {
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
   * Toggle burger menu.
   */

  Drupal.behaviors.burgerMenu = {
    attach: function attach(context, settings) {
      var phoneBreakPoint = 667;
      $('.icon-menu', context).click(function () {
        $('.topbar .menu').slideToggle(200);
      });
      $('.menu-name-main-menu .menu a', context).click(function () {
        if ($(window).width() < phoneBreakPoint) {
          $('.topbar .menu').slideUp(500); // Goto top of page.

          window.scrollTo(0, 0);
        }
      });
    }
  };
  /**
   * Facets.
   */

  Drupal.behaviors.facets = {
    attach: function attach(context, settings) {
      $('#ding-facetbrowser-form', context).each(function () {
        $('fieldset', this).each(function () {
          var dropdown = $(this).find('.fieldset-wrapper').addClass('js-processed');
          $(this).click(function () {
            dropdown.slideToggle(200).toggleClass('open');
          });
        });
      });

      if ($('#ding-facetbrowser-form').length !== 0) {
        var html = $('<div class="js-toggle-facets">' + Drupal.t('Limit search results') + '</div>');
        $('.pane-panels-mini.pane-search').prepend(html);
        $('.js-toggle-facets').click(function () {
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
    attach: function attach(context, settings) {
      // If the block is not present in the DOM abort.
      if ($('.pane-search-form').length === 0) {
        return;
      } // If we are on the search page we dont want to hide the form,
      // but still don't want users to be able to follow the search link.


      if ($('body.page-search').length !== 0) {
        // Show search form.
        $('.pane-search-form').show();
        $('.menu-name-main-menu ul li.last a', context).click(function (event) {
          event.preventDefault();
        });
      } else {
        var searchFormWrapper = $('.pane-search-form', context);
        searchFormWrapper.hide(); // We assume that search is the fifth element. This would be preferable
        // if it was more dynamic.

        $('.menu-name-main-menu ul li.last a', context).click(function (event) {
          event.preventDefault(); // The slide animation sets overflow: hidden, but the
          // autocomplete on the search field requires overflow to
          // be visible, so we reset it when the animation
          // completes.

          searchFormWrapper.slideToggle(400, function () {
            $(this).css({
              overflow: 'visible'
            });
          });
        });
      }
    }
  };
  /**
   * Make ting object details collapsible.
   */

  Drupal.behaviors.tingObject = {
    attach: function attach(context, settings) {
      var fields = ['.group-material-details', '.ting-object-related-item', '.pane-ting-ting-object-types'];
      $(fields).each(function (id, field) {
        $(field).each(function (id, element) {
          $(element).addClass('ting-object-collapsible-enabled').addClass('open').find('h2').nextAll().wrapAll('<div class="collapsible-content-wrapper" />');
          $('.collapsible-content-wrapper').hide();
          $(element).find('h2').click(function () {
            $(element).toggleClass('open').find('.collapsible-content-wrapper').slideToggle();
          });
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
   * Add grid view option.
   */

  Drupal.behaviors.gridView = {
    attach: function attach(context, settings) {
      $('.pane-panels-mini.pane-search').viewPicker('.pane-ting-search-sort-form');
    }
  };
  var resizeTimer;

  function resizeFunction() {
    var windowWidth = window.innerWidth;

    if (windowWidth > 1024) {
      $('.pane-breol-facetbrowser, .before-content').show();
    }
  }

  ; // On resize, run the function and reset the timeout
  // 250 is the delay in milliseconds. Change as you see fit.

  $(window).resize(function () {
    clearTimeout(resizeTimer);
    resizeTimer = setTimeout(resizeFunction, 250);
  });
  resizeFunction();
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
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9hc3NldHMvYXBwLmpzIiwid2VicGFjazovLy8uL2Fzc2V0cy9hcHAuc2NzcyIsIndlYnBhY2s6Ly8vLi9hc3NldHMvc2NyaXB0cy93aWxsZS5tYWluLmpzIl0sIm5hbWVzIjpbIiQiLCJEcnVwYWwiLCJiZWhhdmlvcnMiLCJpc0Rlc2t0b3AiLCJhdHRhY2giLCJjb250ZXh0Iiwic2V0dGluZ3MiLCJpc01vYmlsZSIsImFkZENsYXNzIiwiZm9vdGVyVG9nZ2xlIiwiY2xpY2siLCJlbGVtZW50IiwibmV4dCIsImZpbmQiLCJjc3MiLCJzbGlkZURvd24iLCJyZW1vdmVDbGFzcyIsInNsaWRlVXAiLCJidXJnZXJNZW51IiwicGhvbmVCcmVha1BvaW50Iiwic2xpZGVUb2dnbGUiLCJ3aW5kb3ciLCJ3aWR0aCIsInNjcm9sbFRvIiwiZmFjZXRzIiwiZWFjaCIsImRyb3Bkb3duIiwidG9nZ2xlQ2xhc3MiLCJsZW5ndGgiLCJodG1sIiwidCIsInByZXBlbmQiLCJ0b2dnbGUiLCJzZWFyY2hEcm9wRG93biIsInNob3ciLCJldmVudCIsInByZXZlbnREZWZhdWx0Iiwic2VhcmNoRm9ybVdyYXBwZXIiLCJoaWRlIiwib3ZlcmZsb3ciLCJ0aW5nT2JqZWN0IiwiZmllbGRzIiwiaWQiLCJmaWVsZCIsIm5leHRBbGwiLCJ3cmFwQWxsIiwidWlEaWFsb2ciLCJncmlkVmlldyIsInZpZXdQaWNrZXIiLCJyZXNpemVUaW1lciIsInJlc2l6ZUZ1bmN0aW9uIiwid2luZG93V2lkdGgiLCJpbm5lcldpZHRoIiwicmVzaXplIiwiY2xlYXJUaW1lb3V0Iiwic2V0VGltZW91dCIsIm5hdmlnYXRvciIsInVzZXJBZ2VudCIsIm1hdGNoIiwialF1ZXJ5Il0sIm1hcHBpbmdzIjoiOzs7Ozs7Ozs7O0FBQ0E7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQTs7QUFDQTs7Ozs7O0FBT0E7Q0FHQTs7QUFDQTs7Ozs7Ozs7Ozs7O0FDYkEsdUM7Ozs7Ozs7Ozs7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c291cmNlc0NvbnRlbnQiOlsiXG4vLyBhc3NldHMvanMvYXBwLmpzXG4vKlxuICogV2VsY29tZSB0byB5b3VyIGFwcCdzIG1haW4gSmF2YVNjcmlwdCBmaWxlIVxuICpcbiAqIFdlIHJlY29tbWVuZCBpbmNsdWRpbmcgdGhlIGJ1aWx0IHZlcnNpb24gb2YgdGhpcyBKYXZhU2NyaXB0IGZpbGVcbiAqIChhbmQgaXRzIENTUyBmaWxlKSBpbiB5b3VyIGJhc2UgbGF5b3V0IChiYXNlLmh0bWwudHdpZykuXG4gKi9cblxuLy8gYW55IENTUyB5b3UgaW1wb3J0IHdpbGwgb3V0cHV0IGludG8gYSBzaW5nbGUgY3NzIGZpbGUgKGFwcC5jc3MgaW4gdGhpcyBjYXNlKVxuaW1wb3J0ICcuL2FwcC5zY3NzJztcblxuLy8gTmVlZCBqUXVlcnk/IEluc3RhbGwgaXQgd2l0aCBcInlhcm4gYWRkIGpxdWVyeVwiLCB0aGVuIHVuY29tbWVudCB0byBpbXBvcnQgaXQuXG5pbXBvcnQgJCBmcm9tICdqcXVlcnknO1xuXG5pbXBvcnQgJy4vc2NyaXB0cy93aWxsZS5tYWluLmpzJztcbiIsIi8vIGV4dHJhY3RlZCBieSBtaW5pLWNzcy1leHRyYWN0LXBsdWdpbiIsIi8qKlxuICogQGZpbGVcbiAqIE1haW4gamF2YXNjcmlwdCBmaWxlIGZvciBXaWxsZSB0aGVtZS5cbiAqL1xuXG4oZnVuY3Rpb24gKCQpIHtcblxuICAvKipcbiAgICogRGV0ZWN0IHRhYmxldHMgYW5kIG1vYmlsZSBkZXZpY2VzLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy5pc0Rlc2t0b3AgPSB7XG4gICAgYXR0YWNoIDogZnVuY3Rpb24gKGNvbnRleHQsIHNldHRpbmdzKSB7XG5cbiAgICAgIC8vIEFkZCBjbGFzcyBpZiB3ZSBhcmUgb24gZGVza3RvcC5cbiAgICAgIGlmICghaXNNb2JpbGUoKSkge1xuICAgICAgICAkKCdib2R5JykuYWRkQ2xhc3MoJ2lzLWRlc2t0b3AnKTtcbiAgICAgIH1cbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIFRvZ2dsZSB0aGUgZm9vdGVyIG1lbnVzLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy5mb290ZXJUb2dnbGUgPSB7XG4gICAgYXR0YWNoIDogZnVuY3Rpb24gKGNvbnRleHQsIHNldHRpbmdzKSB7XG5cbiAgICAgICQoJy5mb290ZXIgLnBhbmUtdGl0bGUnLCBjb250ZXh0KS5jbGljayhmdW5jdGlvbiAoKSB7XG5cbiAgICAgICAgdmFyIGVsZW1lbnQgPSAkKHRoaXMpLm5leHQoKS5maW5kKCd1bCcpO1xuXG4gICAgICAgIC8vIE1ha2Ugc3VyZSB0aGUgcmlnaHQgY2xhc3NlcyBhcmUgYWRkZWQsIHNvIHdlIGNhblxuICAgICAgICAvLyBtYWtlIHN1cmUgdGhlIGFycm93IHBvaW50cyBpbiB0aGUgcmlnaHQgZGlyZWN0aW9uLlxuICAgICAgICBpZiAoZWxlbWVudC5jc3MoJ2Rpc3BsYXknKSA9PT0gJ25vbmUnKSB7XG4gICAgICAgICAgJChlbGVtZW50KS5zbGlkZURvd24oMjAwKTtcbiAgICAgICAgICAkKHRoaXMpLmFkZENsYXNzKCdvcGVuJyk7XG4gICAgICAgICAgJCh0aGlzKS5yZW1vdmVDbGFzcygnY2xvc2VkJyk7XG4gICAgICAgIH1cbiAgICAgICAgZWxzZSB7XG4gICAgICAgICAgJCh0aGlzKS5yZW1vdmVDbGFzcygnb3BlbicpO1xuICAgICAgICAgICQodGhpcykuYWRkQ2xhc3MoJ2Nsb3NlZCcpO1xuICAgICAgICAgICQoZWxlbWVudCkuc2xpZGVVcCgyMDApO1xuICAgICAgICB9XG4gICAgICB9KTtcbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIFRvZ2dsZSBidXJnZXIgbWVudS5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMuYnVyZ2VyTWVudSA9IHtcbiAgICBhdHRhY2ggOiBmdW5jdGlvbiAoY29udGV4dCwgc2V0dGluZ3MpIHtcblxuICAgICAgdmFyIHBob25lQnJlYWtQb2ludCA9IDY2NztcblxuICAgICAgJCgnLmljb24tbWVudScsIGNvbnRleHQpLmNsaWNrKGZ1bmN0aW9uICgpIHtcbiAgICAgICAgJCgnLnRvcGJhciAubWVudScpLnNsaWRlVG9nZ2xlKDIwMCk7XG4gICAgICB9KTtcblxuICAgICAgJCgnLm1lbnUtbmFtZS1tYWluLW1lbnUgLm1lbnUgYScsIGNvbnRleHQpLmNsaWNrKGZ1bmN0aW9uICgpIHtcbiAgICAgICAgaWYgKCQod2luZG93KS53aWR0aCgpIDwgcGhvbmVCcmVha1BvaW50KSB7XG4gICAgICAgICAgJCgnLnRvcGJhciAubWVudScpLnNsaWRlVXAoNTAwKTtcblxuICAgICAgICAgIC8vIEdvdG8gdG9wIG9mIHBhZ2UuXG4gICAgICAgICAgd2luZG93LnNjcm9sbFRvKDAsIDApO1xuICAgICAgICB9XG4gICAgICB9KTtcbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIEZhY2V0cy5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMuZmFjZXRzID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuXG4gICAgICAkKCcjZGluZy1mYWNldGJyb3dzZXItZm9ybScsIGNvbnRleHQpLmVhY2goZnVuY3Rpb24gKCkge1xuICAgICAgICAkKCdmaWVsZHNldCcsIHRoaXMpLmVhY2goZnVuY3Rpb24gKCkge1xuXG4gICAgICAgICAgdmFyIGRyb3Bkb3duID0gJCh0aGlzKS5maW5kKCcuZmllbGRzZXQtd3JhcHBlcicpLmFkZENsYXNzKCdqcy1wcm9jZXNzZWQnKTtcblxuICAgICAgICAgICQodGhpcykuY2xpY2soZnVuY3Rpb24gKCkge1xuICAgICAgICAgICAgZHJvcGRvd24uc2xpZGVUb2dnbGUoMjAwKS50b2dnbGVDbGFzcygnb3BlbicpO1xuICAgICAgICAgIH0pO1xuICAgICAgICB9KTtcbiAgICAgIH0pO1xuXG4gICAgICBpZiAoJCgnI2RpbmctZmFjZXRicm93c2VyLWZvcm0nKS5sZW5ndGggIT09IDApIHtcblxuICAgICAgICB2YXIgaHRtbCA9ICQoJzxkaXYgY2xhc3M9XCJqcy10b2dnbGUtZmFjZXRzXCI+JyArIERydXBhbC50KCdMaW1pdCBzZWFyY2ggcmVzdWx0cycpICsgJzwvZGl2PicpO1xuXG4gICAgICAgICQoJy5wYW5lLXBhbmVscy1taW5pLnBhbmUtc2VhcmNoJykucHJlcGVuZChodG1sKTtcblxuICAgICAgICAkKCcuanMtdG9nZ2xlLWZhY2V0cycpLmNsaWNrKGZ1bmN0aW9uICgpIHtcblxuICAgICAgICAgICQodGhpcykudG9nZ2xlQ2xhc3MoJ29wZW4nKTtcblxuICAgICAgICAgICQoJy5wYW5lLWJyZW9sLWZhY2V0YnJvd3NlcicpLnRvZ2dsZSgpO1xuICAgICAgICAgICQoJy5iZWZvcmUtY29udGVudCcpLnRvZ2dsZSgpO1xuICAgICAgICB9KTtcbiAgICAgIH1cbiAgICB9XG4gIH07XG5cbiAgLyoqXG4gICAqIFNlYXJjaCBkcm9wIGRvd24uXG4gICAqL1xuICBEcnVwYWwuYmVoYXZpb3JzLnNlYXJjaERyb3BEb3duID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuICAgICAgLy8gSWYgdGhlIGJsb2NrIGlzIG5vdCBwcmVzZW50IGluIHRoZSBET00gYWJvcnQuXG4gICAgICBpZiAoJCgnLnBhbmUtc2VhcmNoLWZvcm0nKS5sZW5ndGggPT09IDApIHtcbiAgICAgICAgcmV0dXJuO1xuICAgICAgfVxuXG4gICAgICAvLyBJZiB3ZSBhcmUgb24gdGhlIHNlYXJjaCBwYWdlIHdlIGRvbnQgd2FudCB0byBoaWRlIHRoZSBmb3JtLFxuICAgICAgLy8gYnV0IHN0aWxsIGRvbid0IHdhbnQgdXNlcnMgdG8gYmUgYWJsZSB0byBmb2xsb3cgdGhlIHNlYXJjaCBsaW5rLlxuICAgICAgaWYgKCQoJ2JvZHkucGFnZS1zZWFyY2gnKS5sZW5ndGggIT09IDApIHtcblxuICAgICAgICAvLyBTaG93IHNlYXJjaCBmb3JtLlxuICAgICAgICAkKCcucGFuZS1zZWFyY2gtZm9ybScpLnNob3coKTtcblxuICAgICAgICAkKCcubWVudS1uYW1lLW1haW4tbWVudSB1bCBsaS5sYXN0IGEnLCBjb250ZXh0KVxuICAgICAgICAgIC5jbGljayhmdW5jdGlvbiAoZXZlbnQpIHtcbiAgICAgICAgICAgIGV2ZW50LnByZXZlbnREZWZhdWx0KCk7XG4gICAgICAgICAgfSk7XG4gICAgICB9XG4gICAgICBlbHNlIHtcbiAgICAgICAgdmFyIHNlYXJjaEZvcm1XcmFwcGVyID0gJCgnLnBhbmUtc2VhcmNoLWZvcm0nLCBjb250ZXh0KTtcbiAgICAgICAgc2VhcmNoRm9ybVdyYXBwZXIuaGlkZSgpO1xuXG4gICAgICAgIC8vIFdlIGFzc3VtZSB0aGF0IHNlYXJjaCBpcyB0aGUgZmlmdGggZWxlbWVudC4gVGhpcyB3b3VsZCBiZSBwcmVmZXJhYmxlXG4gICAgICAgIC8vIGlmIGl0IHdhcyBtb3JlIGR5bmFtaWMuXG4gICAgICAgICQoJy5tZW51LW5hbWUtbWFpbi1tZW51IHVsIGxpLmxhc3QgYScsIGNvbnRleHQpXG4gICAgICAgICAgLmNsaWNrKGZ1bmN0aW9uIChldmVudCkge1xuICAgICAgICAgICAgZXZlbnQucHJldmVudERlZmF1bHQoKTtcbiAgICAgICAgICAgIC8vIFRoZSBzbGlkZSBhbmltYXRpb24gc2V0cyBvdmVyZmxvdzogaGlkZGVuLCBidXQgdGhlXG4gICAgICAgICAgICAvLyBhdXRvY29tcGxldGUgb24gdGhlIHNlYXJjaCBmaWVsZCByZXF1aXJlcyBvdmVyZmxvdyB0b1xuICAgICAgICAgICAgLy8gYmUgdmlzaWJsZSwgc28gd2UgcmVzZXQgaXQgd2hlbiB0aGUgYW5pbWF0aW9uXG4gICAgICAgICAgICAvLyBjb21wbGV0ZXMuXG4gICAgICAgICAgICBzZWFyY2hGb3JtV3JhcHBlci5zbGlkZVRvZ2dsZSg0MDAsIGZ1bmN0aW9uICgpIHtcbiAgICAgICAgICAgICAgJCh0aGlzKS5jc3Moe292ZXJmbG93OiAndmlzaWJsZSd9KTtcbiAgICAgICAgICAgIH0pO1xuICAgICAgICAgIH0pO1xuICAgICAgfVxuICAgIH1cbiAgfTtcblxuICAvKipcbiAgICogTWFrZSB0aW5nIG9iamVjdCBkZXRhaWxzIGNvbGxhcHNpYmxlLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy50aW5nT2JqZWN0ID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuXG4gICAgICB2YXIgZmllbGRzID0gW1xuICAgICAgICAnLmdyb3VwLW1hdGVyaWFsLWRldGFpbHMnLFxuICAgICAgICAnLnRpbmctb2JqZWN0LXJlbGF0ZWQtaXRlbScsXG4gICAgICAgICcucGFuZS10aW5nLXRpbmctb2JqZWN0LXR5cGVzJ1xuICAgICAgXTtcblxuICAgICAgJChmaWVsZHMpLmVhY2goZnVuY3Rpb24gKGlkLCBmaWVsZCkge1xuXG4gICAgICAgICQoZmllbGQpLmVhY2goZnVuY3Rpb24gKGlkLCBlbGVtZW50KSB7XG4gICAgICAgICAgJChlbGVtZW50KVxuICAgICAgICAgICAgLmFkZENsYXNzKCd0aW5nLW9iamVjdC1jb2xsYXBzaWJsZS1lbmFibGVkJylcbiAgICAgICAgICAgIC5hZGRDbGFzcygnb3BlbicpXG4gICAgICAgICAgICAuZmluZCgnaDInKVxuICAgICAgICAgICAgLm5leHRBbGwoKVxuICAgICAgICAgICAgLndyYXBBbGwoJzxkaXYgY2xhc3M9XCJjb2xsYXBzaWJsZS1jb250ZW50LXdyYXBwZXJcIiAvPicpO1xuXG4gICAgICAgICAgJCgnLmNvbGxhcHNpYmxlLWNvbnRlbnQtd3JhcHBlcicpLmhpZGUoKTtcblxuICAgICAgICAgICQoZWxlbWVudCkuZmluZCgnaDInKS5jbGljayhmdW5jdGlvbiAoKSB7XG4gICAgICAgICAgICAkKGVsZW1lbnQpXG4gICAgICAgICAgICAgIC50b2dnbGVDbGFzcygnb3BlbicpXG4gICAgICAgICAgICAgIC5maW5kKCcuY29sbGFwc2libGUtY29udGVudC13cmFwcGVyJylcbiAgICAgICAgICAgICAgLnNsaWRlVG9nZ2xlKCk7XG4gICAgICAgICAgfSk7XG4gICAgICAgIH0pO1xuICAgICAgfSk7XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBEZXRlY3QgaWYganF1ZXJ5IHVpLWRpYWxvZyBpcyBvcGVuLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy51aURpYWxvZyA9IHtcbiAgICBhdHRhY2ggOiBmdW5jdGlvbiAoY29udGV4dCwgc2V0dGluZ3MpIHtcbiAgICAgIGlmICgkKCcudWktZGlhbG9nJywgY29udGV4dCkuY3NzKCdkaXNwbGF5JykgPT0gJ25vbmUnIHx8ICQoJy51aS1kaWFsb2cnKS5sZW5ndGggPT09IDApIHtcbiAgICAgICAgLy8gRmFsbGJhY2suXG4gICAgICAgICQoJ2JvZHknKS5yZW1vdmVDbGFzcygndWktZGlhbG9nLWlzLW9wZW4nKTtcbiAgICAgIH1cbiAgICAgIGVsc2Uge1xuICAgICAgICAvLyBBZGQgQ2xhc3MgdGhhdCBpbmRpY2F0ZXMgdGhlIGRpYWxvZyBpcyBvcGVuLlxuICAgICAgICAkKCdib2R5JykuYWRkQ2xhc3MoJ3VpLWRpYWxvZy1pcy1vcGVuJyk7XG5cbiAgICAgICAgLy8gTWFrZSBzdXJlIHdlIHJlbW92ZSB0aGUgY2xhc3Mgd2hlbiB1c2VycyBjbG9zZSB0aGUgZGlhbG9nLlxuICAgICAgICAkKCcudWktYnV0dG9uLWljb24tcHJpbWFyeScpLmNsaWNrKGZ1bmN0aW9uICgpIHtcbiAgICAgICAgICAkKCdib2R5JykucmVtb3ZlQ2xhc3MoJ3VpLWRpYWxvZy1pcy1vcGVuJyk7XG4gICAgICAgIH0pO1xuICAgICAgfVxuICAgIH1cbiAgfTtcblxuICAvKipcbiAgICogQWRkIGdyaWQgdmlldyBvcHRpb24uXG4gICAqL1xuICBEcnVwYWwuYmVoYXZpb3JzLmdyaWRWaWV3ID0ge1xuICAgIGF0dGFjaCA6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuICAgICAgJCgnLnBhbmUtcGFuZWxzLW1pbmkucGFuZS1zZWFyY2gnKS52aWV3UGlja2VyKCcucGFuZS10aW5nLXNlYXJjaC1zb3J0LWZvcm0nKTtcbiAgICB9XG4gIH07XG5cbiAgdmFyIHJlc2l6ZVRpbWVyO1xuXG4gIGZ1bmN0aW9uIHJlc2l6ZUZ1bmN0aW9uKCkge1xuICAgIHZhciB3aW5kb3dXaWR0aCA9IHdpbmRvdy5pbm5lcldpZHRoO1xuXG4gICAgaWYgKHdpbmRvd1dpZHRoID4gMTAyNCkge1xuICAgICAgJCgnLnBhbmUtYnJlb2wtZmFjZXRicm93c2VyLCAuYmVmb3JlLWNvbnRlbnQnKS5zaG93KCk7XG4gICAgfVxuICB9O1xuXG4gIC8vIE9uIHJlc2l6ZSwgcnVuIHRoZSBmdW5jdGlvbiBhbmQgcmVzZXQgdGhlIHRpbWVvdXRcbiAgLy8gMjUwIGlzIHRoZSBkZWxheSBpbiBtaWxsaXNlY29uZHMuIENoYW5nZSBhcyB5b3Ugc2VlIGZpdC5cbiAgJCh3aW5kb3cpLnJlc2l6ZShmdW5jdGlvbiAoKSB7XG4gICAgY2xlYXJUaW1lb3V0KHJlc2l6ZVRpbWVyKTtcbiAgICByZXNpemVUaW1lciA9IHNldFRpbWVvdXQocmVzaXplRnVuY3Rpb24sIDI1MCk7XG4gIH0pO1xuXG4gIHJlc2l6ZUZ1bmN0aW9uKCk7XG5cbiAgLyoqXG4gICAqIERldGVjdCBpZiB3ZSBhcmUgb24gbW9iaWxlIGRldmljZXMuXG4gICAqL1xuICBmdW5jdGlvbiBpc01vYmlsZSgpIHtcbiAgICBpZiAobmF2aWdhdG9yLnVzZXJBZ2VudC5tYXRjaCgvQW5kcm9pZC9pKVxuICAgICAgfHwgbmF2aWdhdG9yLnVzZXJBZ2VudC5tYXRjaCgvd2ViT1MvaSlcbiAgICAgIHx8IG5hdmlnYXRvci51c2VyQWdlbnQubWF0Y2goL2lQaG9uZS9pKVxuICAgICAgfHwgbmF2aWdhdG9yLnVzZXJBZ2VudC5tYXRjaCgvaVBhZC9pKVxuICAgICAgfHwgbmF2aWdhdG9yLnVzZXJBZ2VudC5tYXRjaCgvaVBvZC9pKVxuICAgICAgfHwgbmF2aWdhdG9yLnVzZXJBZ2VudC5tYXRjaCgvQmxhY2tCZXJyeS9pKVxuICAgICAgfHwgbmF2aWdhdG9yLnVzZXJBZ2VudC5tYXRjaCgvV2luZG93cyBQaG9uZS9pKVxuICAgICkge1xuICAgICAgcmV0dXJuIHRydWU7XG4gICAgfVxuICAgIGVsc2Uge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cbiAgfVxuXG59KShqUXVlcnkpO1xuIl0sInNvdXJjZVJvb3QiOiIifQ==