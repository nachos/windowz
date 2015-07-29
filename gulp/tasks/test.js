'use strict';

var mocha = require('gulp-mocha');
var istanbul = require('gulp-istanbul');
var config = require('../config');

module.exports = function (gulp) {
  gulp.task('test', ['lint'], function (cb) {
    gulp.src(config.paths.lib)
      .pipe(istanbul({
        includeUntested: true
      }))
      .pipe(istanbul.hookRequire())
      .on('finish', function () {
        gulp.src(config.paths.test)
          .pipe(mocha({reporter: 'spec'}))
          .pipe(istanbul.writeReports())
          .pipe(istanbul.enforceThresholds({thresholds: {global: 100}}))
          .on('end', function () {
            cb();
            process.exit(0);
          });
      });
  });
};
