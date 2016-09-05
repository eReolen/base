// Get modules.
var gulp = require('gulp');
var notify = require('gulp-notify');
var compass = require('gulp-compass');
var jshint = require('gulp-jshint');
var stylish = require('jshint-stylish');
var autoprefixer = require('gulp-autoprefixer');
var sourcemaps = require('gulp-sourcemaps');

// Compass.
gulp.task('compass', function () {
  return gulp.src('./sass/*.scss')
    .pipe(sourcemaps.init())
    .pipe(compass({
      includePaths: require('node-neat').includePaths,
      outputStyle: 'expanded'
    }).on('error', notify.onError(function (error) {
      return 'SASS error: ' + error.message;
    })))
    .pipe(autoprefixer({
      browsers: ['last 4 versions'],
      cascade: false
    }))
    .pipe(sourcemaps.write())
    .pipe(gulp.dest('./css'));
});

// Compass watch.
gulp.task('compass:watch', function () {
  gulp.watch('./sass/**/*.scss', ['compass']);
});

// JsHint.
gulp.task('jshint', function () {
  return gulp.src(['gulpfile.js', './js/*.js'])
    .pipe(jshint())
  // Get stylish output.
    .pipe(jshint.reporter(stylish))
  // Add fail reporter and send it to notification API.
    .pipe(jshint.reporter('fail'))
    .on('error', notify.onError(function (error) {
      return 'JSHint error: ' + error.message;
    }));
});

// JsHint watch.
gulp.task('jshint:watch', function () {
  gulp.watch(['gulpfile.js', './js/*.js'], ['jshint']);
});

// Register workers.
gulp.task('default', ['jshint', 'compass', 'jshint:watch', 'compass:watch']);
