(function($) {
  Drupal.behaviors.player = {
    attach : function() {
      // Go through all players.
      $('[data-role=audiobook-player]').each(function() {
        var clientId = Drupal.settings.publizon.clientId;
        var order = $(this).data('id');

        // First load metadata and state from API.
        $.when(Drupal.behaviors.player.loadMetadata(clientId, order), Drupal.behaviors.player.loadState(clientId, order)).then(function (metadata, state) {
          // Initialize the player.
          $('[data-role=player]').playable({
            metadata: {
              title: metadata.title,
              artist: metadata.artist,
              duration: metadata.duration,
              available: metadata.duration,
              autosave: true,
              key: clientId,
              order: order
            },
            state: {
              nightmode: state.nightmode,
              position: state.position
            }
          })
          .on('autosave', function (e, currentState) {
            $.ajax({
              type: 'POST',
              headers: { 'x-service-key': clientId },
              contentType: 'application/json',
              data: JSON.stringify(currentState),
              url: stateUrl
            });
          });
        }, function (data) {
          console.log('Error: ' + data.responseText);
        });
      });
    },

    /**
     * Load metadata from API.
     */
    loadMetadata : function(clientId, order) {
      var url = Drupal.settings.publizon.playerServer + 'v1/orders/' + order;
      return $.ajax({
        type: 'GET',
        headers: { 'x-service-key': clientId },
        contentType: 'application/json',
        url: url,
        success: function (data) {
          metadata = data;
        }
      });
    },

    /**
     * Load state from API.
     */
    loadState : function(clientId, order) {
      var url = Drupal.settings.publizon.playerServer + 'v1/states/' + order;
      return $.ajax({
        type: 'GET',
        headers: { 'x-service-key': clientId },
        contentType: 'application/json',
        url: url,
        success: function (data) {
          state = data;
        }
      });
    }
  };
})(jQuery);
