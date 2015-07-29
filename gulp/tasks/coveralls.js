'use strict';

var config = require('../config');
var coveralls = require('gulp-coveralls');

module.exports = function (gulp) {
  gulp.task('coveralls', function () {
    return gulp.src(config.paths.coverage)
      .pipe(coveralls());
  });
};