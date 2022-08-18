(function($) {
  'use strict';

  $(document).ready(function () {
    var url = document.getElementById('reader-container').getAttribute('data-url');
    var imagesUrl = document.getElementById('reader-container').getAttribute('data-images-url');
    var readerVersion = document.getElementById('reader-container').getAttribute('data-reader-version');

    var settings = {
      elementId: 'reader-container',
      sessionKeyUrl: '/reol_use_loan/reader/session/renew/{0}',
      imageBasePath: imagesUrl + '/images/' + readerVersion + '/',
      notesEnabled: false,
      streamPackageBaseUri: url + '/',
      streamingServiceBaseUri: url + '/publicstreaming/v3/',
      sampleStreamingServiceBaseUri: url + '/samplestreaming/v3/',
    };

    var isbn = document.getElementById('reader-container').getAttribute('data-isbn');
    if (isbn !== undefined) {
      settings.isbn = isbn;
    }

    var order = document.getElementById('reader-container').getAttribute('data-id');
    if (order !== undefined) {
      settings.orderId = order;
    }

    // Initialize the reader.
    Reader.init(settings);

    // Add class to root element so the we can style everything acordingly.
    $('html').addClass('reader-is-open');

    // Add back button that works on click and touchstart(mobile).
    var trigger = $('<a class="reader__back-button js-back-button"></a>');
    $('#reader-menu-wrapper').prepend(trigger);

    trigger.on('click touchstart', function(event) {
      window.history.back();
    });
  });

})(jQuery);
