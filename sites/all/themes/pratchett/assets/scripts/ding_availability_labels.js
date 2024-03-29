/**
 * @file
 * Override the JS behavior of ding_availability_labels.
 */

(function ($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

  Drupal.behaviors.dingAvailabilityAttach = {
    attach: function (context, settings) {
      var ids = [];
      var html_ids = [];

      // Extract entity ids from Drupal settings array.
      if (settings.hasOwnProperty("ding_availability")) {
        $.each(settings.ding_availability, function (id, entity_ids) {
          $.each(entity_ids, function (index, entity_id) {
            if (Drupal.DADB[entity_id] === undefined) {
              Drupal.DADB[entity_id] = null;
              ids.push(entity_id);
              html_ids.push(id);
            }
          });
        });
      }

      // Fetch availability.
      if (ids.length > 0) {
        var mode = settings.ding_availability_mode
          ? settings.ding_availability_mode
          : "items";
        var path =
          settings.basePath + "ding_availability/" + mode + "/" + ids.join(",");
        $.ajax({
          dataType: "json",
          url: path,
          success: function (data) {
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
          error: function () {
            $("div.loader").remove();
          },
        });
      } else {
        // Apply already fetched availability, if any.
        if (settings.hasOwnProperty("ding_availability")) {
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
          reservable: false,
        };

        // Loop over the entity ids and if one has available or reservable
        // true save that value.
        $.each(entity_ids, function (index, entity_id) {
          if (Drupal.DADB[entity_id]) {
            status.available =
              status.available || Drupal.DADB[entity_id]["available"];
            status.reservable =
              status.reservable || Drupal.DADB[entity_id]["reservable"];
          }
        });

        var element = $("#" + id);
        element.removeClass("pending").addClass("processed");

        // Get hold of the reserve button (it hidden as default, so we may need
        // to show it).
        var reserver_btn = element
          .parents(".ting-object:first")
          .find("[id^=ding-reservation-reserve-form]");

        update_availability_elements(element, reserver_btn, status);
      }

      /**
       * Helper function to move the materials based on availability.
       * @param element {Object} The target element (material that should be moved).
       * @param status {string} Structure with available and reservable state.
       */
      function update_availability_type(element, status) {
        var groups_wrapper = element.closest(".search-result--availability");
        var reservable = status["reservable"];
        var available = status["available"];

        var group = null;
        if ($(".js-online", groups_wrapper).length !== 0) {
          group = $(".js-online", groups_wrapper);
        } else if (available) {
          group = $(".js-available", groups_wrapper);

          if (group.length === 0) {
            group = $('<p class="js-available"></p>');
            groups_wrapper.append(group);
          }
        } else if (reservable) {
          group = $(".js-reservable", groups_wrapper);
          if (group.length === 0) {
            group = $('<p class="js-reservable"></p>');
            groups_wrapper.append(group);
          }
        } else {
          group = $(".js-unavailable", groups_wrapper);

          if (group.length === 0) {
            group = $('<p class="js-unavailable"></p>');
            groups_wrapper.append(group);
          }
        }

        // Move the element into that type.
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
        $(".js-pending").each(function () {
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
            if (i === "available") {
              class_name = "un" + i;
            } else if (i === "reservable") {
              class_name = "not-" + i;
            }
          }

          element.addClass(class_name);
          if (btn.length) {
            btn.addClass(class_name);
          }
        }

        $(element).once("reol-availability", function () {
          // TODO: this is very fragile.
          var type_name = element.text().toLowerCase();
          var string;

          if (Drupal.settings.ding_availability_type_mapping[type_name]) {
            type_name =
              Drupal.settings.ding_availability_type_mapping[type_name];
          }

          if (status["available"] === true) {
            string =
              Drupal.settings.ding_availability_type_strings["available"];
            element.text(Drupal.formatString(string, { "@type": type_name }));
          } else if (status["reservable"] === true) {
            string =
              Drupal.settings.ding_availability_type_strings["reservable"];
            element.text(Drupal.formatString(string, { "@type": type_name }));
          }
        });

        update_availability_type(element, status);
      }
    },
  };
})(jQuery);
