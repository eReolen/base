var gulp = require('gulp'),
    sass = require('gulp-sass')
    notify = require('gulp-notify'),
    autoprefixer = require('gulp-autoprefixer'),
    sourcemaps = require('gulp-sourcemaps');

// Sass.
gulp.task('sass', function () {
  return gulp.src('./sass/*.scss')
    .pipe(sourcemaps.init())
    .pipe(sass({
      outputStyle: 'expanded'
    }).on('error', notify.onError(function (error) {
      return 'SASS error: ' + error.message;
    })))
    .pipe(autoprefixer({
      browsers: ['last 4 versions'],
      cascade: false
    }))
    .pipe(sourcemaps.write('sourcemaps'))
    .pipe(gulp.dest('./css'));
});

// Sass watch.
gulp.task('sass:watch', function () {
  gulp.watch('./sass/*.scss', ['sass']);
});

// Register workers.
gulp.task('default', ['sass', 'sass:watch']);
