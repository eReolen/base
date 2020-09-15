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
/* harmony import */ var _scripts_orwell_main_js__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./scripts/orwell.main.js */ "./assets/scripts/orwell.main.js");
/* harmony import */ var _scripts_orwell_main_js__WEBPACK_IMPORTED_MODULE_2___default = /*#__PURE__*/__webpack_require__.n(_scripts_orwell_main_js__WEBPACK_IMPORTED_MODULE_2__);
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

/***/ "./assets/scripts/orwell.main.js":
/*!***************************************!*\
  !*** ./assets/scripts/orwell.main.js ***!
  \***************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

/* WEBPACK VAR INJECTION */(function(jQuery) {__webpack_require__(/*! core-js/modules/es.array.find */ "./node_modules/core-js/modules/es.array.find.js");

__webpack_require__(/*! core-js/modules/es.array.index-of */ "./node_modules/core-js/modules/es.array.index-of.js");

__webpack_require__(/*! core-js/modules/es.date.to-string */ "./node_modules/core-js/modules/es.date.to-string.js");

__webpack_require__(/*! core-js/modules/es.regexp.exec */ "./node_modules/core-js/modules/es.regexp.exec.js");

__webpack_require__(/*! core-js/modules/es.string.replace */ "./node_modules/core-js/modules/es.string.replace.js");

__webpack_require__(/*! core-js/modules/es.string.split */ "./node_modules/core-js/modules/es.string.split.js");

/**
 * @file
 * Main javascript file for Pratchett theme.
 */
(function ($) {
  'use strict'; // Cookie set/get functions.

  function setCookie(c_name, value, exdays) {
    var exdate = new Date();
    exdate.setDate(exdate.getDate() + exdays);
    var c_value = escape(value) + (exdays === null ? '' : '; expires=' + exdate.toUTCString());
    document.cookie = c_name + '=' + c_value;
  }

  function getCookie(c_name) {
    var i;
    var x;
    var y;
    var ARRcookies = document.cookie.split(';');

    for (i = 0; i < ARRcookies.length; i++) {
      x = ARRcookies[i].substr(0, ARRcookies[i].indexOf('='));
      y = ARRcookies[i].substr(ARRcookies[i].indexOf('=') + 1);
      x = x.replace(/^\s+|\s+$/g, '');

      if (x === c_name) {
        return unescape(y);
      }
    }
  }
  /**
   * Toggle between grid and list view on results page.
   */


  Drupal.behaviors.searchResultsGridToggle = {
    attach: function attach(context) {
      var cookieName = 'eReol_2__searchResultArrangement';
      var expires = 1; // Determine if we're on results page.

      if ($('.search-results').length && $('.panel-col-first').length) {
        var list_toggle = $('<div class="arrangement-toggles"><div class="arrangement-toggle toggle-list"></div><div class="arrangement-toggle toggle-grid"></div></div>');
        $('.panel-col-first').prepend(list_toggle);
        var $toggle = $('.arrangement-toggle'); // Set initial view to what's stored in the cookie, otherwise
        // set to list-view.

        if (getCookie(cookieName) === 'list-view') {
          $('.search-results').addClass('list-view');
          $('.arrangement-toggle.toggle-list').addClass('toggle-active');
        } else {
          $('.search-results').addClass('grid-view');
          $('.arrangement-toggle.toggle-grid').addClass('toggle-active');
        } // When either toggle is clicked.


        $toggle.on('click', function () {
          var $this = $(this); // Visually toggle button states.

          $('.arrangement-toggle').removeClass('toggle-active');
          $this.addClass('toggle-active'); // Set/update cookie to arrangement/view type.

          if ($this.hasClass('toggle-list')) {
            setCookie(cookieName, 'list-view', expires);
            $('.search-results').addClass('list-view').removeClass('grid-view');
          } else {
            setCookie(cookieName, 'grid-view', expires);
            $('.search-results').addClass('grid-view').removeClass('list-view');
          }
        });
      }
    }
  };
  /**
   * Slide toggle facets on search page on mobile.
   */

  Drupal.behaviors.searchPageFacets = {
    attach: function attach(context, settings) {
      if ($('body.page-search').length) {
        var trigger = $('<div class="facets-trigger-wrapper"><div class="js-facets-trigger"></div><div>');
        $('.panel-col-first').prepend(trigger);
        trigger.on('click', function () {
          $('.panel-col-first').find('.inside').slideToggle();
        });
      }
    }
  };
  /**
   * Menu dropdown behavior.
   */

  Drupal.behaviors.menuDropdown = {
    attach: function attach(context) {
      $('.menu-level-2 li.expanded').once(function () {
        var menu = $(this);
        var trigger = menu.find('> a');
        var submenu = menu.find('ul');
        trigger.on('click', function (e) {
          e.preventDefault(); // Stop propagation, so we don't immediately trigger the
          // click event we attach to the body.

          e.stopPropagation(); // Close any other open submenus.

          menu.parent().find('.js-active').not(menu).click();

          if (!menu.hasClass('js-active')) {
            menu.addClass('js-active'); // Dismiss the submenu when the mouse leaves it.

            submenu.on('mouseleave.ereolen', function () {
              trigger.click();
            }); // Add a click handler to body to dismiss the submenu.

            $('body').on('click.ereolen', function (e) {
              trigger.click();
            });
          } else {
            menu.removeClass('js-active');
            submenu.off('mouseleave.ereolen');
            $('body').off('click.ereolen');
          }
        });
      });
    }
  };
  /**
   * Toggle show/hide more content on material abstract.
   */

  $(function () {
    $('.material__abstract').each(function () {
      var $minHeight = 140;

      if ($(this).height() > $minHeight) {
        $(this).addClass('showmore');
      }
    });
    $('.material__abstract.showmore').on('click', function () {
      $(this).toggleClass('visible');
    });
  });
})(jQuery);
/* WEBPACK VAR INJECTION */}.call(this, __webpack_require__(/*! jquery */ "./node_modules/jquery/dist/jquery.js")))

/***/ })

},[["./assets/app.js","runtime","vendors~app"]]]);
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9hc3NldHMvYXBwLmpzIiwid2VicGFjazovLy8uL2Fzc2V0cy9hcHAuc2NzcyIsIndlYnBhY2s6Ly8vLi9hc3NldHMvc2NyaXB0cy9vcndlbGwubWFpbi5qcyJdLCJuYW1lcyI6WyIkIiwic2V0Q29va2llIiwiY19uYW1lIiwidmFsdWUiLCJleGRheXMiLCJleGRhdGUiLCJEYXRlIiwic2V0RGF0ZSIsImdldERhdGUiLCJjX3ZhbHVlIiwiZXNjYXBlIiwidG9VVENTdHJpbmciLCJkb2N1bWVudCIsImNvb2tpZSIsImdldENvb2tpZSIsImkiLCJ4IiwieSIsIkFSUmNvb2tpZXMiLCJzcGxpdCIsImxlbmd0aCIsInN1YnN0ciIsImluZGV4T2YiLCJyZXBsYWNlIiwidW5lc2NhcGUiLCJEcnVwYWwiLCJiZWhhdmlvcnMiLCJzZWFyY2hSZXN1bHRzR3JpZFRvZ2dsZSIsImF0dGFjaCIsImNvbnRleHQiLCJjb29raWVOYW1lIiwiZXhwaXJlcyIsImxpc3RfdG9nZ2xlIiwicHJlcGVuZCIsIiR0b2dnbGUiLCJhZGRDbGFzcyIsIm9uIiwiJHRoaXMiLCJyZW1vdmVDbGFzcyIsImhhc0NsYXNzIiwic2VhcmNoUGFnZUZhY2V0cyIsInNldHRpbmdzIiwidHJpZ2dlciIsImZpbmQiLCJzbGlkZVRvZ2dsZSIsIm1lbnVEcm9wZG93biIsIm9uY2UiLCJtZW51Iiwic3VibWVudSIsImUiLCJwcmV2ZW50RGVmYXVsdCIsInN0b3BQcm9wYWdhdGlvbiIsInBhcmVudCIsIm5vdCIsImNsaWNrIiwib2ZmIiwiZWFjaCIsIiRtaW5IZWlnaHQiLCJoZWlnaHQiLCJ0b2dnbGVDbGFzcyIsImpRdWVyeSJdLCJtYXBwaW5ncyI6Ijs7Ozs7Ozs7OztBQUNBO0FBQUE7QUFBQTtBQUFBO0FBQUE7QUFBQTtBQUFBO0FBQUE7O0FBQ0E7Ozs7OztBQU9BO0NBR0E7O0FBQ0E7Ozs7Ozs7Ozs7OztBQ2JBLHVDOzs7Ozs7Ozs7Ozs7Ozs7Ozs7Ozs7OztBQ0FBOzs7O0FBS0Es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QUFkO0FBQ0Q7QUFDRixTQTFCRDtBQTJCRCxPQWhDRDtBQWlDRDtBQW5DNkIsR0FBaEM7QUFzQ0E7Ozs7QUFHQXZELEdBQUMsQ0FBQyxZQUFZO0FBQ1pBLEtBQUMsQ0FBQyxxQkFBRCxDQUFELENBQXlCd0QsSUFBekIsQ0FBOEIsWUFBWTtBQUN4QyxVQUFJQyxVQUFVLEdBQUcsR0FBakI7O0FBQ0EsVUFBSXpELENBQUMsQ0FBQyxJQUFELENBQUQsQ0FBUTBELE1BQVIsS0FBbUJELFVBQXZCLEVBQW1DO0FBQ2pDekQsU0FBQyxDQUFDLElBQUQsQ0FBRCxDQUFRbUMsUUFBUixDQUFpQixVQUFqQjtBQUNEO0FBQ0YsS0FMRDtBQU9BbkMsS0FBQyxDQUFDLDhCQUFELENBQUQsQ0FBa0NvQyxFQUFsQyxDQUFxQyxPQUFyQyxFQUE4QyxZQUFXO0FBQ3ZEcEMsT0FBQyxDQUFDLElBQUQsQ0FBRCxDQUFRMkQsV0FBUixDQUFvQixTQUFwQjtBQUNELEtBRkQ7QUFHRCxHQVhBLENBQUQ7QUFhRCxDQTdJRCxFQTZJR0MsTUE3SUgsRSIsImZpbGUiOiJhcHAuanMiLCJzb3VyY2VzQ29udGVudCI6WyJcbi8vIGFzc2V0cy9qcy9hcHAuanNcbi8qXG4gKiBXZWxjb21lIHRvIHlvdXIgYXBwJ3MgbWFpbiBKYXZhU2NyaXB0IGZpbGUhXG4gKlxuICogV2UgcmVjb21tZW5kIGluY2x1ZGluZyB0aGUgYnVpbHQgdmVyc2lvbiBvZiB0aGlzIEphdmFTY3JpcHQgZmlsZVxuICogKGFuZCBpdHMgQ1NTIGZpbGUpIGluIHlvdXIgYmFzZSBsYXlvdXQgKGJhc2UuaHRtbC50d2lnKS5cbiAqL1xuXG4vLyBhbnkgQ1NTIHlvdSBpbXBvcnQgd2lsbCBvdXRwdXQgaW50byBhIHNpbmdsZSBjc3MgZmlsZSAoYXBwLmNzcyBpbiB0aGlzIGNhc2UpXG5pbXBvcnQgJy4vYXBwLnNjc3MnO1xuXG4vLyBOZWVkIGpRdWVyeT8gSW5zdGFsbCBpdCB3aXRoIFwieWFybiBhZGQganF1ZXJ5XCIsIHRoZW4gdW5jb21tZW50IHRvIGltcG9ydCBpdC5cbmltcG9ydCAkIGZyb20gJ2pxdWVyeSc7XG5cbmltcG9ydCAnLi9zY3JpcHRzL29yd2VsbC5tYWluLmpzJztcbiIsIi8vIGV4dHJhY3RlZCBieSBtaW5pLWNzcy1leHRyYWN0LXBsdWdpbiIsIi8qKlxuICogQGZpbGVcbiAqIE1haW4gamF2YXNjcmlwdCBmaWxlIGZvciBQcmF0Y2hldHQgdGhlbWUuXG4gKi9cblxuKGZ1bmN0aW9uICgkKSB7XG4gICd1c2Ugc3RyaWN0JztcblxuICAvLyBDb29raWUgc2V0L2dldCBmdW5jdGlvbnMuXG4gIGZ1bmN0aW9uIHNldENvb2tpZShjX25hbWUsIHZhbHVlLCBleGRheXMpIHtcbiAgICB2YXIgZXhkYXRlID0gbmV3IERhdGUoKTtcbiAgICBleGRhdGUuc2V0RGF0ZShleGRhdGUuZ2V0RGF0ZSgpICsgZXhkYXlzKTtcbiAgICB2YXIgY192YWx1ZSA9IGVzY2FwZSh2YWx1ZSkgKyAoKGV4ZGF5cyA9PT0gbnVsbCkgPyAnJyA6ICgnOyBleHBpcmVzPScgKyBleGRhdGUudG9VVENTdHJpbmcoKSkpO1xuICAgIGRvY3VtZW50LmNvb2tpZSA9IGNfbmFtZSArICc9JyArIGNfdmFsdWU7XG4gIH1cbiAgZnVuY3Rpb24gZ2V0Q29va2llKGNfbmFtZSkge1xuICAgIHZhciBpO1xuICAgIHZhciB4O1xuICAgIHZhciB5O1xuICAgIHZhciBBUlJjb29raWVzID0gZG9jdW1lbnQuY29va2llLnNwbGl0KCc7Jyk7XG4gICAgZm9yIChpID0gMDsgaSA8IEFSUmNvb2tpZXMubGVuZ3RoOyBpKyspIHtcbiAgICAgIHggPSBBUlJjb29raWVzW2ldLnN1YnN0cigwLCBBUlJjb29raWVzW2ldLmluZGV4T2YoJz0nKSk7XG4gICAgICB5ID0gQVJSY29va2llc1tpXS5zdWJzdHIoQVJSY29va2llc1tpXS5pbmRleE9mKCc9JykgKyAxKTtcbiAgICAgIHggPSB4LnJlcGxhY2UoL15cXHMrfFxccyskL2csICcnKTtcbiAgICAgIGlmICh4ID09PSBjX25hbWUpIHtcbiAgICAgICAgcmV0dXJuIHVuZXNjYXBlKHkpO1xuICAgICAgfVxuICAgIH1cbiAgfVxuXG4gIC8qKlxuICAgKiBUb2dnbGUgYmV0d2VlbiBncmlkIGFuZCBsaXN0IHZpZXcgb24gcmVzdWx0cyBwYWdlLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy5zZWFyY2hSZXN1bHRzR3JpZFRvZ2dsZSA9IHtcbiAgICBhdHRhY2g6IGZ1bmN0aW9uIChjb250ZXh0KSB7XG4gICAgICB2YXIgY29va2llTmFtZSA9ICdlUmVvbF8yX19zZWFyY2hSZXN1bHRBcnJhbmdlbWVudCc7XG4gICAgICB2YXIgZXhwaXJlcyA9IDE7XG4gICAgICAvLyBEZXRlcm1pbmUgaWYgd2UncmUgb24gcmVzdWx0cyBwYWdlLlxuICAgICAgaWYgKCQoJy5zZWFyY2gtcmVzdWx0cycpLmxlbmd0aCAmJiAkKCcucGFuZWwtY29sLWZpcnN0JykubGVuZ3RoKSB7XG4gICAgICAgIHZhciBsaXN0X3RvZ2dsZSA9ICQoJzxkaXYgY2xhc3M9XCJhcnJhbmdlbWVudC10b2dnbGVzXCI+PGRpdiBjbGFzcz1cImFycmFuZ2VtZW50LXRvZ2dsZSB0b2dnbGUtbGlzdFwiPjwvZGl2PjxkaXYgY2xhc3M9XCJhcnJhbmdlbWVudC10b2dnbGUgdG9nZ2xlLWdyaWRcIj48L2Rpdj48L2Rpdj4nKTtcbiAgICAgICAgJCgnLnBhbmVsLWNvbC1maXJzdCcpLnByZXBlbmQobGlzdF90b2dnbGUpO1xuXG4gICAgICAgIHZhciAkdG9nZ2xlID0gJCgnLmFycmFuZ2VtZW50LXRvZ2dsZScpO1xuICAgICAgICAvLyBTZXQgaW5pdGlhbCB2aWV3IHRvIHdoYXQncyBzdG9yZWQgaW4gdGhlIGNvb2tpZSwgb3RoZXJ3aXNlXG4gICAgICAgIC8vIHNldCB0byBsaXN0LXZpZXcuXG4gICAgICAgIGlmIChnZXRDb29raWUoY29va2llTmFtZSkgPT09ICdsaXN0LXZpZXcnKSB7XG4gICAgICAgICAgJCgnLnNlYXJjaC1yZXN1bHRzJykuYWRkQ2xhc3MoJ2xpc3QtdmlldycpO1xuICAgICAgICAgICQoJy5hcnJhbmdlbWVudC10b2dnbGUudG9nZ2xlLWxpc3QnKS5hZGRDbGFzcygndG9nZ2xlLWFjdGl2ZScpO1xuICAgICAgICB9XG4gICAgICAgIGVsc2Uge1xuICAgICAgICAgICQoJy5zZWFyY2gtcmVzdWx0cycpLmFkZENsYXNzKCdncmlkLXZpZXcnKTtcbiAgICAgICAgICAkKCcuYXJyYW5nZW1lbnQtdG9nZ2xlLnRvZ2dsZS1ncmlkJykuYWRkQ2xhc3MoJ3RvZ2dsZS1hY3RpdmUnKTtcbiAgICAgICAgfVxuICAgICAgICAvLyBXaGVuIGVpdGhlciB0b2dnbGUgaXMgY2xpY2tlZC5cbiAgICAgICAgJHRvZ2dsZS5vbignY2xpY2snLCBmdW5jdGlvbiAoKSB7XG4gICAgICAgICAgdmFyICR0aGlzID0gJCh0aGlzKTtcbiAgICAgICAgICAvLyBWaXN1YWxseSB0b2dnbGUgYnV0dG9uIHN0YXRlcy5cbiAgICAgICAgICAkKCcuYXJyYW5nZW1lbnQtdG9nZ2xlJykucmVtb3ZlQ2xhc3MoJ3RvZ2dsZS1hY3RpdmUnKTtcbiAgICAgICAgICAkdGhpcy5hZGRDbGFzcygndG9nZ2xlLWFjdGl2ZScpO1xuICAgICAgICAgIC8vIFNldC91cGRhdGUgY29va2llIHRvIGFycmFuZ2VtZW50L3ZpZXcgdHlwZS5cbiAgICAgICAgICBpZiAoJHRoaXMuaGFzQ2xhc3MoJ3RvZ2dsZS1saXN0JykpIHtcbiAgICAgICAgICAgIHNldENvb2tpZShjb29raWVOYW1lLCAnbGlzdC12aWV3JywgZXhwaXJlcyk7XG4gICAgICAgICAgICAkKCcuc2VhcmNoLXJlc3VsdHMnKS5hZGRDbGFzcygnbGlzdC12aWV3JykucmVtb3ZlQ2xhc3MoJ2dyaWQtdmlldycpO1xuICAgICAgICAgIH1cbiAgICAgICAgICBlbHNlIHtcbiAgICAgICAgICAgIHNldENvb2tpZShjb29raWVOYW1lLCAnZ3JpZC12aWV3JywgZXhwaXJlcyk7XG4gICAgICAgICAgICAkKCcuc2VhcmNoLXJlc3VsdHMnKS5hZGRDbGFzcygnZ3JpZC12aWV3JykucmVtb3ZlQ2xhc3MoJ2xpc3QtdmlldycpO1xuICAgICAgICAgIH1cbiAgICAgICAgfSk7XG4gICAgICB9XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBTbGlkZSB0b2dnbGUgZmFjZXRzIG9uIHNlYXJjaCBwYWdlIG9uIG1vYmlsZS5cbiAgICovXG4gIERydXBhbC5iZWhhdmlvcnMuc2VhcmNoUGFnZUZhY2V0cyA9IHtcbiAgICBhdHRhY2g6IGZ1bmN0aW9uIChjb250ZXh0LCBzZXR0aW5ncykge1xuICAgICAgaWYgKCQoJ2JvZHkucGFnZS1zZWFyY2gnKS5sZW5ndGgpIHtcbiAgICAgICAgdmFyIHRyaWdnZXIgPSAkKCc8ZGl2IGNsYXNzPVwiZmFjZXRzLXRyaWdnZXItd3JhcHBlclwiPjxkaXYgY2xhc3M9XCJqcy1mYWNldHMtdHJpZ2dlclwiPjwvZGl2PjxkaXY+Jyk7XG4gICAgICAgICQoJy5wYW5lbC1jb2wtZmlyc3QnKS5wcmVwZW5kKHRyaWdnZXIpO1xuXG4gICAgICAgIHRyaWdnZXIub24oJ2NsaWNrJywgZnVuY3Rpb24gKCkge1xuICAgICAgICAgICQoJy5wYW5lbC1jb2wtZmlyc3QnKS5maW5kKCcuaW5zaWRlJykuc2xpZGVUb2dnbGUoKTtcbiAgICAgICAgfSk7XG4gICAgICB9XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBNZW51IGRyb3Bkb3duIGJlaGF2aW9yLlxuICAgKi9cbiAgRHJ1cGFsLmJlaGF2aW9ycy5tZW51RHJvcGRvd24gPSB7XG4gICAgYXR0YWNoOiBmdW5jdGlvbiAoY29udGV4dCkge1xuICAgICAgJCgnLm1lbnUtbGV2ZWwtMiBsaS5leHBhbmRlZCcpLm9uY2UoZnVuY3Rpb24gKCkge1xuICAgICAgICB2YXIgbWVudSA9ICQodGhpcyk7XG4gICAgICAgIHZhciB0cmlnZ2VyID0gbWVudS5maW5kKCc+IGEnKTtcbiAgICAgICAgdmFyIHN1Ym1lbnUgPSBtZW51LmZpbmQoJ3VsJyk7XG5cbiAgICAgICAgdHJpZ2dlci5vbignY2xpY2snLCBmdW5jdGlvbiAoZSkge1xuICAgICAgICAgIGUucHJldmVudERlZmF1bHQoKTtcbiAgICAgICAgICAvLyBTdG9wIHByb3BhZ2F0aW9uLCBzbyB3ZSBkb24ndCBpbW1lZGlhdGVseSB0cmlnZ2VyIHRoZVxuICAgICAgICAgIC8vIGNsaWNrIGV2ZW50IHdlIGF0dGFjaCB0byB0aGUgYm9keS5cbiAgICAgICAgICBlLnN0b3BQcm9wYWdhdGlvbigpO1xuXG4gICAgICAgICAgLy8gQ2xvc2UgYW55IG90aGVyIG9wZW4gc3VibWVudXMuXG4gICAgICAgICAgbWVudS5wYXJlbnQoKS5maW5kKCcuanMtYWN0aXZlJykubm90KG1lbnUpLmNsaWNrKCk7XG5cbiAgICAgICAgICBpZiAoIW1lbnUuaGFzQ2xhc3MoJ2pzLWFjdGl2ZScpKSB7XG4gICAgICAgICAgICBtZW51LmFkZENsYXNzKCdqcy1hY3RpdmUnKTtcbiAgICAgICAgICAgIC8vIERpc21pc3MgdGhlIHN1Ym1lbnUgd2hlbiB0aGUgbW91c2UgbGVhdmVzIGl0LlxuICAgICAgICAgICAgc3VibWVudS5vbignbW91c2VsZWF2ZS5lcmVvbGVuJywgZnVuY3Rpb24gKCkge1xuICAgICAgICAgICAgICB0cmlnZ2VyLmNsaWNrKCk7XG4gICAgICAgICAgICB9KTtcblxuICAgICAgICAgICAgLy8gQWRkIGEgY2xpY2sgaGFuZGxlciB0byBib2R5IHRvIGRpc21pc3MgdGhlIHN1Ym1lbnUuXG4gICAgICAgICAgICAkKCdib2R5Jykub24oJ2NsaWNrLmVyZW9sZW4nLCBmdW5jdGlvbiAoZSkge1xuICAgICAgICAgICAgICB0cmlnZ2VyLmNsaWNrKCk7XG4gICAgICAgICAgICB9KTtcbiAgICAgICAgICB9XG4gICAgICAgICAgZWxzZSB7XG4gICAgICAgICAgICBtZW51LnJlbW92ZUNsYXNzKCdqcy1hY3RpdmUnKTtcbiAgICAgICAgICAgIHN1Ym1lbnUub2ZmKCdtb3VzZWxlYXZlLmVyZW9sZW4nKTtcbiAgICAgICAgICAgICQoJ2JvZHknKS5vZmYoJ2NsaWNrLmVyZW9sZW4nKTtcbiAgICAgICAgICB9XG4gICAgICAgIH0pO1xuICAgICAgfSk7XG4gICAgfVxuICB9O1xuXG4gIC8qKlxuICAgKiBUb2dnbGUgc2hvdy9oaWRlIG1vcmUgY29udGVudCBvbiBtYXRlcmlhbCBhYnN0cmFjdC5cbiAgICovXG4gICQoZnVuY3Rpb24gKCkge1xuICAgICQoJy5tYXRlcmlhbF9fYWJzdHJhY3QnKS5lYWNoKGZ1bmN0aW9uICgpIHtcbiAgICAgIHZhciAkbWluSGVpZ2h0ID0gMTQwO1xuICAgICAgaWYgKCQodGhpcykuaGVpZ2h0KCkgPiAkbWluSGVpZ2h0KSB7XG4gICAgICAgICQodGhpcykuYWRkQ2xhc3MoJ3Nob3dtb3JlJyk7XG4gICAgICB9XG4gICAgfSk7XG5cbiAgICAkKCcubWF0ZXJpYWxfX2Fic3RyYWN0LnNob3dtb3JlJykub24oJ2NsaWNrJywgZnVuY3Rpb24oKSB7XG4gICAgICAkKHRoaXMpLnRvZ2dsZUNsYXNzKCd2aXNpYmxlJyk7XG4gICAgfSk7XG4gIH0pO1xuXG59KShqUXVlcnkpO1xuIl0sInNvdXJjZVJvb3QiOiIifQ==