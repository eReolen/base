// Get modules.
var gulp = require('gulp');
var notify = require('gulp-notify');
var sass = require('gulp-sass');
var jshint = require('gulp-jshint');
var stylish = require('jshint-stylish');
var autoprefixer = require('gulp-autoprefixer');
var sourcemaps = require('gulp-sourcemaps');

// Sass.
gulp.task('sass', function () {
  var neatRequire = require('node-neat').includePaths,
    bourbonRequire = require('node-bourbon').includePaths;

  return gulp.src('./sass/*.scss')
    .pipe(sourcemaps.init())
    .pipe(sass({
      includePaths: [].concat(neatRequire, bourbonRequire),
      outputStyle: 'compressed'
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

// Watch
gulp.task('watch', function() {
  gulp.watch('./sass/**/*.scss', {interval: 1000}, ['sass']);
  gulp.watch(['gulpfile.js', './js/*.js'], { interval: 1000 }, ['jshint']);
});

// default
gulp.task('default',
  gulp.parallel('jshint', 'sass')
);
