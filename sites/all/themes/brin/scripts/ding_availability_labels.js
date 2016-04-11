/**
 * @file
 * Override the JS behavior of ding_availability_labels.
 */
(function($) {
  "use strict";

  // Cache of fetched availability information.
  Drupal.DADB = {};

  Drupal.behaviors.dingAvailabilityAttach = {
    attach: function(context, settings) {
      var ids = [];
      var html_ids = [];

      // Extract entity ids from Drupal settings array.
      if (settings.hasOwnProperty('ding_availability')) {
        $.each(settings.ding_availability, function(id, entity_ids) {
          $.each(entity_ids, function(index, entity_id) {
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
        var mode = settings.ding_availability_mode ? settings.ding_availability_mode : 'items';
        var path = settings.basePath + 'ding_availability/' + mode + '/' + ids.join(',');
        $.ajax({
          dataType: "json",
          url: path,
          success: function(data) {
            $.each(data, function(id, item) {
              // Update cache.
              Drupal.DADB[id] = item;
            });

            $.each(settings.ding_availability, function(id, entity_ids) {
              if (id.match(/^availability-/)) {
                // Update availability indicators.
                update_availability(id, entity_ids);
              }
            });
            update_availability_remove_pending();
          }
        });
      }
      else {
        // Apply already fetched availability, if any.
        if (settings.hasOwnProperty('ding_availability')) {
          $.each(settings.ding_availability, function(id, entity_ids) {
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
       *
       * @param id
       *   The element id that this should target.
       * @param entity_ids
       *   Array of entities.
       */
      function update_availability(id, entity_ids) {
        // Default the status to not available and not reservable.
        var available = false;
        var reservable = false;

        // Loop over the entity ids and if one has available or reservable
        // true save that value.
        $.each(entity_ids, function(index, entity_id) {
          if (Drupal.DADB[entity_id]) {
            available = available || Drupal.DADB[entity_id].available;
            reservable = reservable || Drupal.DADB[entity_id].reservable;
          }
        });

        var element = $('#' + id);
        element.removeClass('pending').addClass('processed');

        // Get hold of the reserve button (it hidden as default, so we may need
        // to show it).
        var reserver_btn = element.parents('.ting-object:first').find('[id^=ding-reservation-reserve-form]');

        if (available) {
          update_availability_elements(element, reserver_btn, 'available');
        }
        else if (reservable) {
          update_availability_elements(element, reserver_btn, 'reservable');
        }
        else if (!available && !reservable) {
          update_availability_elements(element, reserver_btn, 'not-reservable');
        }
        else {
          update_availability_elements(element, reserver_btn, 'unavailable');
        }
      }

      /**
       * Removes js-pending groups (labels) if they are empty or changes the
       * label to "Can be obtained". This should be called as the last function
       * in updating availability information and see as a clean-up function.
       */
      function update_availability_remove_pending() {
        // Loop over all pending availability groups.
        $('.js-pending').each(function() {
          var elm = $(this);
          var children = elm.children();
          if (children.length) {
            // Remove the class.
            $(this).removeClass('js-pending');
          }
          else {
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
       * @param class_name
       *   The class to add to the elements.
       */
      function update_availability_elements(element, btn, class_name) {
        $(element).once('reol-availability', function() {
          element.addClass(class_name);
          // TODO: this is very fragile.
          var type_name = element.text().toLowerCase();
          var string;
          if (Drupal.settings.ding_availability_type_mapping[type_name]) {
            type_name = Drupal.settings.ding_availability_type_mapping[type_name];
          }

          if (Drupal.settings.ding_availability_type_strings[class_name]) {
            string = Drupal.settings.ding_availability_type_strings[class_name];
            element.text(Drupal.formatString(string, {'@type': type_name}));
          }
          if (btn.length) {
            btn.addClass(class_name);
          }
        });
      }
    }
  };
})(jQuery);
