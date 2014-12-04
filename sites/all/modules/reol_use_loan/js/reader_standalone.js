var url = document.getElementById('reader-container').getAttribute('data-url');
var imagesUrl = document.getElementById('reader-container').getAttribute('data-images-url');
var settings = {
  elementId: 'reader-container',
  streamPackageBaseUri: url,
  streamingServiceBaseUri: url + '/publicstreaming_v2/v2/',
  sampleStreamingServiceBaseUri: url + '/samplestreaming_v2/v2/',
  sessionKeyUrl: '/reol_use_loan/reader/session/renew/{0}',
  imageBasePath: imagesUrl + '/images/1.4.4/'
}

var isbn = document.getElementById('reader-container').getAttribute('data-isbn');
if (isbn != undefined) {
  settings.isbn = isbn;
}

var order = document.getElementById('reader-container').getAttribute('data-id');
if (order != undefined) {
  settings.orderId = order;
}
Reader.init(settings);
