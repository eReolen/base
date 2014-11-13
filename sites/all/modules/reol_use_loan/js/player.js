(function($) {
  $(document).ready(function () {
    var key = getQueryStringArgument('k');
    var order = getQueryStringArgument('o');
    var isbn = getQueryStringArgument('i');

    var streamServer = 'https://audio.api.streaming.pubhub.dk/';
    var metadata = null;
    var state = { nightmode: false, position: 0 };

    if (typeof isbn != 'undefined' && isbn.length > 0) {
      // ISBN is defined, load sample
      var metadataUrl = streamServer + 'v1/samples/' + isbn;
      $.when(loadMetadata(metadataUrl)).then(function () {
        initPlayer({
          metadata: {
            isbn: isbn,
            autosave: false
          }
        });
      }, function (data) {
        console.log('Fejl: ' + data.responseText);
      });
    } else {
      // Load order
      var metadataUrl = streamServer + 'v1/orders/' + order;
      var stateUrl = streamServer + 'v1/states/' + order;

      $.when(loadMetadata(metadataUrl), loadState(stateUrl)).then(function () {
        initPlayer({
          metadata: {
            key: key,
            order: order
          }
        });
      }, function (data) {
        console.log('Fejl: ' + data.responseText);
      });
    }

    function loadMetadata(url) {
      return $.ajax({
        type: 'GET',
        headers: { 'x-service-key': key },
        contentType: 'application/json',
        url: url,
        success: function (data) {
          metadata = data;
          document.title += ' - ' + metadata.title;
        }
      });
    }

    function loadState(url) {
      return $.ajax({
        type: 'GET',
        headers: { 'x-service-key': key },
        contentType: 'application/json',
        url: url,
        success: function (data) {
          state = data;
        }
      });
    }
    
    function initPlayer(settings) {
      $('#container').playable($.extend(true, {
          metadata: {
            title: metadata.title,
            artist: metadata.artist,
            duration: metadata.duration,
            available: metadata.duration,
            autosave: true
          },
          state: {
            nightmode: state.nightmode,
            position: state.position
          }
        }, settings)
      )
      .on('autosave', function (e, currentState) {
        $.ajax({
          type: 'POST',
          headers: { 'x-service-key': key },
          contentType: 'application/json',
          data: JSON.stringify(currentState),
          url: stateUrl
        });
      });
    }
  });

  function getQueryStringArgument(key) {
    var re = new RegExp('(?:\\?|&)' + key + '=(.*?)(?=&|$)', 'gi');
    var r = [], m;
    while ((m = re.exec(document.location.search)) != null) r.push(m[1]);
    return r;
  }
})(jQuery);
