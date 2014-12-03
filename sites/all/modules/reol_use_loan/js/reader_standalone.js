var url = document.getElementById('reader-container').getAttribute('data-url');
var imagesUrl = document.getElementById('reader-container').getAttribute('data-images-url');
Reader.init({
  elementId: 'reader-container',
  orderId: document.getElementById('reader-container').getAttribute('data-id'),
  streamPackageBaseUri: url,
  streamingServiceBaseUri: url + '/publicstreaming_v2/v2/',
  sampleStreamingServiceBaseUri: url + '/samplestreaming_v2/v2/',
  sessionKeyUrl: '/reol_use_loan/reader/session/renew/{0}',
  imageBasePath: imagesUrl + '/images/1.4.4/'
});
