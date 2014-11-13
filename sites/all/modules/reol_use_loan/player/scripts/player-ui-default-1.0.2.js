(function ($) {
    $.fn.playable = function(options) {
        return this.each(function() {
            var $window, $body, $audioContainer, $audioPlayer, audioPlayer, timer, dragPosition, loading = true, fastforwardSlider = null, progress; //, autoupdate, currentXCoordInProgressBar;
            var $progressBar, $progressAvailable, $progressTime, $progressButton, $toolTip, $playBtn, $playLbl, $take1Btn, $skip1Btn, $take5Btn, $skip5Btn, $nightBtn, $sleepBtn, $sleepLbl, $speedBtn, $speedLbl, $speedSlider, $volumeSlider, $progress, $current, $total;
            var $this = $(this);

            initElements(this);
            initAudioPlayer();
            initFastforwardSlider();

            $window.on('resize', function() { centerAudioPlayer(); });
            $window.on('orientationchange', function() { centerAudioPlayer(); });

            $playBtn.on('tap', function() {
                if ($playLbl.hasClass('glyphicon-play')) {
                    $playBtn.setPlaying();
                    setTimeout(audioPlayer.play, 1);
                    //updatebar();
                } else {
                    $playBtn.setPaused();
                    setTimeout(audioPlayer.pause, 1);
                }
            });

            $playBtn.setPlaying = function() {
                $playLbl.removeClass('glyphicon-play').addClass('glyphicon-pause');
                return this;
            };

            $playBtn.setPaused = function() {
                $playLbl.removeClass('glyphicon-pause').addClass('glyphicon-play');
                return this;
            }

            $take1Btn.on('tap', function() {
                audioPlayer.skip(-60);
            });

            $skip1Btn.on('tap', function() {
                audioPlayer.skip(60);
            });

            $take5Btn.on('tap', function() {
                audioPlayer.skip(-300);
            });

            $skip5Btn.on('tap', function() {
                audioPlayer.skip(300);
            });

            $nightBtn.on('tap', function() {
                $audioContainer.toggleClass('nightmode');
                var nightMode = $audioContainer.hasClass('nightmode');
                audioPlayer.setNightMode(nightMode);

                if (!nightMode) {
                    $body.css('background', "#ffffff");
                } else {
                    $body.css('background', '#404040');
                }
            });

            $sleepBtn.on('tap', function() {
                var sleepSeconds = $sleepLbl.data('seconds');
                // NOTE: Use if clause for easy start increments
                if (!sleepSeconds || sleepSeconds <= 240) {
                    sleepSeconds = sleepSeconds ? sleepSeconds + 60 : 60;
                    sleepSeconds = Math.ceil(sleepSeconds / 60) * 60;
                } else {
                    sleepSeconds = sleepSeconds ? sleepSeconds * 2 : 900;
                    if (sleepSeconds > 3600) sleepSeconds = null;
                    else sleepSeconds = Math.ceil(sleepSeconds / 900) * 900;
                }

                if (sleepSeconds) {
                    $sleepLbl.html('<p>' + (sleepSeconds / 60) + 'm</p>');
                    $sleepLbl.data('seconds', sleepSeconds);
                } else {
                    $sleepLbl.html('');
                    $sleepLbl.data('seconds', null);
                }

                audioPlayer.sleep(sleepSeconds);
            });

            $speedBtn.on('tap', function() {
                $speedSlider.parent().toggle();
            });

            var progressDragging = false;
            $progressButton.on('mousedown touchstart', function(e) {
                if (!progressDragging) {
                    progressDragging = true;
                    $progressButton.addClass('active');

                    $body.on('touchmove mousemove', function(e) {
                        if (progressDragging) {
                            var pageX = e.originalEvent.changedTouches && e.originalEvent.changedTouches[0].pageX || e.originalEvent.pageX;
                            var xCoord = pageX - $progressBar.offset().left;
                            updatebar(xCoord);
                        }

                        if (bowser.android || bowser.ios) {
                            e.preventDefault();
                        }
                    });

                    if (bowser.android) {
                        e.preventDefault();
                    }
                }
            });

            $body.on('mouseup touchend', function(e) {
                if (progressDragging) {
                    progressDragging = false;
                    $progressButton.removeClass('active');
                    $body.off('touchmove mousemove');
                    audioPlayer.position(dragPosition);
                }
            });

            $speedSlider.slider({
                min: 0.5,
                max: 1.5,
                step: 0.1,
                value: 1,
                tooltip: 'hide'
            }).on('slide', function(ev) {
                audioPlayer.speed(ev.value);
                if (ev.value == 1) {
                    $speedLbl.html('');
                } else {
                    $speedLbl.html('<p>' + Math.round(ev.value * 10) / 10 + '</p>');
                }
            }).parent().hide();

            $volumeSlider.slider({
                min: 0,
                max: 1,
                step: 0.01,
                value: 1,
                tooltip: 'show',
                formater: function(a, b) {
                    return Math.round(a * 100) + ' %';
                }
            }).on('slide', function(ev) {
                audioPlayer.volume(ev.value);
            });

            $audioPlayer.on('autosave', function (e, currentState) {
                $this.trigger('autosave', currentState);
            });

            $audioPlayer.on('drained', function(e, drainedArgs) {
                setCurrentAndTotal();
                $this.trigger('drained', drainedArgs);
            });

            $audioPlayer.on('soondrained', function (e, soonDrainedArgs) {
                $this.trigger('soondrained', soonDrainedArgs);
            });

            $audioPlayer.on('playercursorupdate', function(e) {
                setCurrentAndTotal();
            });

            $audioPlayer.on('seek', function(e, position) {
                setCurrentAndTotal(audioPlayer.played());
                $this.trigger('seek', position);
            });

            $audioPlayer.on('playing play', function() {
                $playBtn.setPlaying();
            });

            $audioPlayer.on('playerpause', function() {
                $playBtn.setPaused();
            });

            $audioPlayer.on('playersleepexpired', function() {
                audioPlayer.pause();
                $sleepLbl.html('');
                $sleepLbl.data('seconds', null);
            });

            if (!options.tracks) {
                // Show loading animations in online mode only

                $audioPlayer.on('seeked playing suspend error playerready', function() {
                    $progressBar.removeClass('loading');
                });

                $audioPlayer.on('waiting seeking playerloading', function() {
                    $progressBar.addClass('loading');
                });
            }

            function setCurrentAndTotal() {
                if (fastforwardSlider && (fastforwardSlider.dragging || fastforwardSlider.tapping) || progressDragging || audioPlayer.seeking) {
                    return;
                }

                var played = audioPlayer.played();
                var duration = audioPlayer.totalDuration();

                if (isNaN(played.h) || isNaN(duration.h)) {
                    return;
                }

                var playedVal = ((parseInt(played.h, 10) * 60 * 60) + (parseInt(played.m, 10) * 60) + parseInt(played.s, 10));
                var durationVal = ((parseInt(duration.h, 10) * 60 * 60) + (parseInt(duration.m, 10) * 60) + parseInt(duration.s, 10));
                var percentval = (playedVal / durationVal) * 100;

                if (isNaN(playedVal)) {
                    return;
                }

                dragPosition = playedVal;

                $current.html(played.h + ':' + played.m + ':' + played.s);
                $total.html((duration.h) + ':' + (duration.m) + ':' + (duration.s));

                $progress.css('width', percentval.toFixed(2) + '%');
            }

            var updatebar = function(position, updatePlayer) {
                var width = $progressBar.width();
                var percentage = 100 * position / width;
                if (percentage > 100) percentage = 100;
                if (percentage < 0) percentage = 0;

                var duration = audioPlayer.totalDuration();
                var destSecond = duration.totalSeconds * percentage / 100;

                if (updatePlayer) {
                    audioPlayer.position(destSecond);
                }

                updateBarToSecond(destSecond);

                return destSecond;
            };

            function updateBarToSecond(destSecond) {
                var duration = audioPlayer.totalDuration();
                if (isNaN(destSecond)) {
                    return;
                }

                dragPosition = destSecond;

                var percentage = 100 * (destSecond / duration.totalSeconds);

                $progress.css('width', percentage.toFixed(2) + '%');
                var hours = Math.floor(destSecond / 3600, 10);
                var minutes = Math.floor(destSecond / 60, 10) % 60;
                var seconds = Math.floor(destSecond % 60, 10);

                hours = hours < 10 ? '0' + hours : hours;
                minutes = minutes < 10 ? '0' + minutes : minutes;
                seconds = seconds < 10 ? '0' + seconds : seconds;

                $toolTip.html(hours + ':' + minutes + ':' + seconds);
                $current.html(hours + ':' + minutes + ':' + seconds);
                $total.html((duration.h) + ':' + (duration.m) + ':' + (duration.s));
            }

            function initElements(container) {
                $window = $(window);
                $body = $('body');

                $audioContainer = $(container);

                $audioContainer.append('<div id="title">' + options.metadata.artist + ' - ' + options.metadata.title + '</div>');
                $audioContainer.append('<div id="time" >' +
                    '<div class="progress" id="progress" rel="tooltip">' +
                    '<div id="progressbar-tracks"></div>' +
                    '<div id="progressbar-progress">' +
                    '<div class="progress-bar status" role="progressbar"></div>' +
                    '<span class="progress-button-wrapper"><span class="progress-button slider-handle"></span></span>' +
                    '</div>' +
                    '</div>' +
                    '<div id="fastforward-slider">' +
                    '<div class="fastforward-handle-wrapper"><div class="fastforward-handle"><span class="glyphicon glyphicon-backward"></span><span><span class="glyphicon glyphicon-forward right"></span></span></div></div>' +
                    '</div>' +
                    '<div class="progress-time"><p><span class="current">00:00:00</span><span class="total">00:00:00</span></p></div></div>');
                $audioContainer.append('<div id="buttonRow1" class="row">' +
                    '<div id="left-row" style="padding-right: 3px;">' +
                    '<button class="btn btn-default take5" type="button" rel="tooltip" title="5 minutter tilbage"><span class="glyphicon glyphicon-fast-backward"></span></button>' +
                    '<button class="btn btn-default take1" type="button" rel="tooltip" title="1 minut tilbage"><span class="glyphicon glyphicon-backward"></span></button>' +
                    '<button class="btn btn-default play" type="button" rel="tooltip" title="Afspil/Pause"><span class="glyphicon glyphicon-play"></span></button>' +
                    '<button class="btn btn-default skip1" type="button" rel="tooltip" title="1 minut frem"><span class="glyphicon glyphicon-forward"></span></button>' +
                    '<button class="btn btn-default skip5" type="button" rel="tooltip" title="5 minutter frem"><span class="glyphicon glyphicon-fast-forward"></span></button>' +
                    '</div>' +
                    '<div id="right-row" class="col-xs-4 col-md-4" style="padding-top: 9px;padding-left:0">' +
                    '<div style="display: table; width:100%" id="volume"><span class="glyphicon glyphicon-volume-up" style="display: table-cell;width:1%;padding-right: 15px;vertical-align: middle;"></span>' +
                    '<div style="display: table-cell; width: 100%"><div id="volume-slider"></div></div>' +
                    '</div>' +
                    '</div>' +
                    '</div>');

                $audioContainer.append('<div id="buttonRow2">' +
                    '<button class="btn btn-default night" type="button" rel="tooltip" title="Nattilstand"><span class="glyphicon glyphicon-adjust"></span></button>' +
                    '<button class="btn btn-default sleep" type="button" rel="tooltip" title="Sleeptimer (klik for at ændre tiden)"><span class="glyphicon glyphicon-time"></span></button>' +
                    '<button class="btn btn-default speed" type="button" rel="tooltip" title="Ændre hastighed"><span class="glyphicon glyphicon-dashboard"></span></button>' +
                    '<div class="speed-slider"></div>' +
                    '</div>');

                if (bowser.android || bowser.ios) {
                    $('#speed-slider').css('display', 'none');
                    $('.speed').css('display', 'none');
                    $('#right-row').css('display', 'none');
                } else {
                    $('#left-row').addClass('col-xs-8 col-md-8');
                }

                $progressBar = $('#progress');
                $progressAvailable = $progressBar.find('.available');
                $progress = $('#progressbar-progress');
                $progressTime = $('.progress-time');
                $current = $progressTime.find('.current');
                $total = $progressTime.find('.total');
                $progressButton = $('.progress-button-wrapper');
                $toolTip = $('#tooltip'); // TODO: Implement tooltip (?)
                $playBtn = $('.play');
                $playLbl = $playBtn.find('span');
                $take1Btn = $('.take1');
                $take5Btn = $('.take5');
                $skip1Btn = $('.skip1');
                $skip5Btn = $('.skip5');
                $nightBtn = $('.night');
                $sleepBtn = $('.sleep');
                $sleepLbl = $sleepBtn.find('span');
                $speedBtn = $('.speed');
                $speedLbl = $speedBtn.find('span');
                $speedSlider = $('.speed-slider');
                $volumeSlider = $('#volume-slider');
            };

            function initFastforwardSlider() {
                // Progress bar updates per second:
                var updateRate = 35;
                // How much of the total duration to forward per frame when the slider is dragged all the way to one of the sides:
                // Current value means that it'd take 8 seconds to go all the way to the right
                var speed = 100 / (updateRate * Math.min(audioPlayer.duration, 700)); //Math.min(1 / (8 * updateRate), 999990.002); //, updateRate / options.metadata.duration);
                var updateTimeout = null;
                var rAF = window.requestAnimationFrame ||
                    window.webkitRequestAnimationFrame ||
                    window.mozRequestAnimationFrame ||
                    window.oRequestAnimationFrame ||
                    window.msRequestAnimationFrame ||
                    function(callback) { window.setTimeout(callback, 1000 / 60); };
                var dragSpeed = 0;
                if (isNaN(speed)) {
                    return;
                }

                var timeoutFunc = function() {
                    updateTimeout = setTimeout(function() {
                        rAF(function() {
                            if (updateTimeout == null) {
                                // Cancel animation if timeout has been cancelled
                                return;
                            }
                            var destSecond = Math.min(Math.max(dragPosition + dragSpeed, 0), audioPlayer.duration);
                            updateBarToSecond(destSecond);

                            timeoutFunc();
                        });
                    }, 1000 / updateRate);
                }

                fastforwardSlider = new Dragdealer('fastforward-slider', {
                    handleClass: 'fastforward-handle-wrapper',
                    x: .5,
                    steps: 3,
                    animationCallback: function(x) {
                        if (this.dragging || this.tapping) {
                            x = 2 * x - 1;
                            // Make the fast-forward time increase exponentially:
                            x *= Math.abs(x);

                            dragSpeed = audioPlayer.duration * speed * x;
                            if (!updateTimeout) {
                                timeoutFunc();
                            }
                        }
                    },
                    callback: function(x) {
                        clearTimeout(updateTimeout);
                        updateTimeout = null;
                        audioPlayer.position(dragPosition);
                    }
                });

                // Override steps to only snap to the middle
                fastforwardSlider.stepRatios = [0.5];
            }

            function initAudioPlayer() {

                if (!options)
                    throw Error('Player options was null or undefined');

                timer = null;
                dragPosition = false;
                audioPlayer = new Player({
                    key: options.metadata.key,
                    order: options.metadata.order,
                    isbn: options.metadata.isbn,
                    state: options.state,
                    autosave: options.metadata.autosave,
                    tracks: options.tracks,
                    duration: options.metadata.duration,
                    streamServer: options.streamServer,
                    controls: options.controls,
                    sleepHandler: options.sleepHandler,
                });

                $audioPlayer = $(audioPlayer);


                if (options.state) {
                    if (options.state.nightmode) {
                        $audioContainer.addClass('nightmode');
                        $body.css('background-color', '#404040');
                    }
                }

                setAvailableAreas();

                var thumb = $('#thumb');
                if (thumb.length > 0) {
                    $("#thumb").load(function() {
                        centerAudioPlayer();
                    });
                } else {
                    centerAudioPlayer();
                }

                setCurrentAndTotal();
            };

            function setAvailableAreas() {
                if (!audioPlayer.tracks) {
                    var $part = $('<div class="progress-bar progress-bar-striped available active" role="progressbar" style="width: 100%"></div>');
                    $('#progressbar-tracks').append($part);
                    return;
                }

                // Merge tracks of same availability
                var progressParts = [];
                for (var i = 0; i < audioPlayer.tracks.length; i++) {
                    var track = {
                        start: audioPlayer.tracks[i].position,
                        end: audioPlayer.tracks[i].position + audioPlayer.tracks[i].duration,
                        available: !(typeof audioPlayer.tracks[i].src == 'undefined' || audioPlayer.tracks[i].src == null)
                    };

                    if (progressParts[progressParts.length - 1] && progressParts[progressParts.length - 1].end == track.start && progressParts[progressParts.length - 1].available == track.available) {
                        progressParts[progressParts.length - 1].end = track.end;
                    } else {
                        progressParts[progressParts.length] = track;
                    }
                }

                // Create HTML elements for the track parts       
                for (var i = 0; i < progressParts.length; i++) {
                    var part = progressParts[i];
                    var startPct = 100 * part.start / audioPlayer.duration;
                    var endPct = 100 * (part.end - part.start) / audioPlayer.duration;

                    var $part;
                    if (part.available) {
                        // Available part
                        $part = $('<div class="progress-bar progress-bar-striped available" role="progressbar""></div>');
                    } else {
                        // Unavailable part
                        $part = $('<div class="progress-bar unavailable" role="progressbar"></div>');
                    }

                    $part.css('left', startPct + '%').css('width', endPct + '%');
                    $('#progressbar-tracks').append($part);
                }
            }

            function centerAudioPlayer() {
                var size = (window.innerHeight / 2) - ($audioContainer.height() / 2);

                if (size > 0)
                    $audioContainer.css('margin-top', size);
            }

            return this;
        });
    };
}(jQuery));


/*! Tappy! - a lightweight normalized tap event. Copyright 2013 @scottjehl, Filament Group, Inc. Licensed MIT */
(function (w, $, undefined) {

    // handling flag is true when an event sequence is in progress (thx androood)
    w.tapHandling = false;

    var tap = function ($els) {
        return $els.each(function () {

            var $el = $(this),
				resetTimer,
				startY = null,
				startX = null,
				cancel,
				scrollTolerance = 10;

            function trigger(e) {
                var coords = getCoords(e);
                $(e.target).trigger("tap", [e, $(e.target).attr("href")]);
                e.stopImmediatePropagation();
            }

            function getCoords(e) {
                var ev = e.originalEvent || e,
					touches;
                touches = ev.touches && ev.touches[0] || ev.targetTouches && ev.targetTouches[0] || ev;

                if (touches) {
                    return [touches.pageX, touches.pageY];
                }
                else {
                    return null;
                }
            }

            function start(e) {
                if (e.touches && e.touches.length > 1 || e.targetTouches && e.targetTouches.length > 1) {
                    return false;
                }

                var coords = getCoords(e);
                startX = coords[0];
                startY = coords[1];

                $el.off("touchmove MSPointerMove", move);
                $el.on("touchmove MSPointerMove", move);
            }

            // any touchscroll that results in > tolerance should cancel the tap
            function move(e) {
                if (!cancel) {
                    var coords = getCoords(e);
                    if (coords && (Math.abs(startY - coords[1]) > scrollTolerance || Math.abs(startX - coords[0]) > scrollTolerance)) {
                        cancel = true;
                        $el.off("touchmove MSPointerMove", move);
                    }
                }
            }

            function end(e) {
                $el.off("touchmove MSPointerMove", move);
                clearTimeout(resetTimer);
                resetTimer = setTimeout(function () {
                    w.tapHandling = false;
                    cancel = false;
                }, 1000);

                // make sure no modifiers are present. thx http://www.jacklmoore.com/notes/click-events/
                if ((e.which && e.which > 1) || e.shiftKey || e.altKey || e.metaKey || e.ctrlKey) {
                    return;
                }

                e.preventDefault();

                // this part prevents a double callback from touch and mouse on the same tap

                // if a scroll happened between touchstart and touchend
                if (cancel || w.tapHandling && w.tapHandling !== e.type || (startX == null && e.type != "click")) {
                    cancel = false;
                    return;
                }

                startY = null;
                startX = null;
                w.tapHandling = e.type;
                trigger(e);
            }

            $el
				.on("touchstart MSPointerDown", start)
				.on("touchend MSPointerUp", end)
				.on("click", end);
        });
    };

    // use special events api
    if ($.event && $.event.special) {
        $.event.special.tap = {
            add: function (handleObj) {
                tap($(this), true);
            },
            remove: function (handleObj) {
                tap($(this), false);
            }
        };
    }
    else {
        // monkeybind
        var oldBind = $.fn.bind;
        $.fn.bind = function (evt) {
            if (/(^| )tap( |$)/.test(evt)) {
                tap(this);
            }
            return oldBind.apply(this, arguments);
        };
    }

}(this, jQuery));