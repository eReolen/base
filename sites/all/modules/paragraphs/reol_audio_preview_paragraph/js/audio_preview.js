/**
 * @file
 * Audio preview box JavaScript.
 */

var $ = jQuery;

(function ($) {
  'use strict';

  /**
   * Format time.
   */
  var formatTime = function (time) {
    var minutes = Math.floor(time / 60);
    var seconds = time % 60;
    return ('0000' + minutes).slice(-2) + '.' + ('0000' + seconds).slice(-2);
  };

  var initPlayer = function (element, isbn, metadata) {
    var playerKernel = new PlayerKernel({
      isbn: isbn,
      duration: metadata.duration,
      streamServer: 'https://audio.api.streaming.pubhub.dk/',
      title: metadata.artist + ' - ' + metadata.title,
    });

    var $playerKernel = $(playerKernel);
    var $btn = $('.audio-preview__button', element);

    // Update the duration.
    $('.audio-preview__duration', element).html(formatTime(playerKernel.totalDuration()));

    $playerKernel
      .on('playerplay', function () {
        $btn.text('Pause').data('playing', true);
      })
      .on('playerpause', function () {
        $btn.text('Play').data('playing', false);
      })
      .on('playercursorupdate', function () {
        var playedVal = playerKernel.played();
        var durationVal = playerKernel.totalDuration();

        if (isNaN(playedVal) || isNaN(durationVal)) {
          return;
        }

        $('.audio-preview__played', element).html(formatTime(playedVal));

        var percentVal = (playedVal / durationVal) * 100;

        $('.audio-preview__progress__complete', element).css({'width': percentVal + "%"});
      });

    $btn
      .on('click', function () {
        if ($(this).data('playing')) {
          playerKernel.pause();
          $(this).removeClass('playing');
        }
        else {
          playerKernel.play();
          $(this).addClass('playing');
        }
      });

  };

  // Create the audio player for previews.
  Drupal.behaviors.audioPreview = {
    attach: function (context) {
      $('.audio-preview__player').once(function () {
        var isbn = $(this).data('isbn');
        var self = $(this);

        $.ajax({
          type: 'GET',
          contentType: 'application/json',
          url: 'https://audio.api.streaming.pubhub.dk/v1/samples/' + isbn,
          success: function (metadata) {
            initPlayer(self, isbn, metadata);
          }
        });
      });
    }
  }
})(jQuery);
