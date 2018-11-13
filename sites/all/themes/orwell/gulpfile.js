var gulp = require('gulp'),
    sass = require('gulp-sass')
    notify = require('gulp-notify'),
    autoprefixer = require('gulp-autoprefixer'),
    bourbon = require('node-bourbon'),
    neat = require('node-neat'),
    sourcemaps = require('gulp-sourcemaps');

// Sass.
gulp.task('sass', function () {
  var neatRequire = require('node-neat').includePaths,
      bourbonRequire = require('node-bourbon').includePaths;

  return gulp.src('./sass/**/*.scss')
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
    .pipe(sourcemaps.write('sourcemaps'))
    .pipe(gulp.dest('./css'));
});

// Sass watch.
gulp.task('sass:watch', function () {
  gulp.watch('./sass/**/*.scss', { interval: 1000 }, ['sass']);
});

// Register workers.
gulp.task('default', ['sass', 'sass:watch']);
