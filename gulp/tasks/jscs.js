'use strict';

var jscs = require('gulp-jscs');
var config = require('../config');

module.exports = function (gulp) {
  gulp.task('jscs', ['jscs:lib', 'jscs:test', 'jscs:gulp', 'jscs:scripts']);

  gulp.task('jscs:lib', function () {
    return gulp.src(config.paths.lib)
      .pipe(jscs());
  });

  gulp.task('jscs:test', function () {
    return gulp.src(config.paths.test)
      .pipe(jscs());
  });

  gulp.task('jscs:gulp', function () {
    return gulp.src(config.paths.gulp)
      .pipe(jscs());
  });

  gulp.task('jscs:scripts', function () {
    return gulp.src(config.paths.scripts)
      .pipe(jscs());
  });
};
