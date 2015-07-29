'use strict';

var runSequence = require('run-sequence');

module.exports = function (gulp) {
  gulp.task('lint', ['lint:lib', 'lint:test', 'lint:gulp', 'lint:scripts']);

  gulp.task('lint:lib', function (cb) {
    runSequence(
      'jshint:lib',
      'jscs:lib',
      cb
    );
  });

  gulp.task('lint:test', function (cb) {
    runSequence(
      'jshint:test',
      'jscs:test',
      cb
    );
  });

  gulp.task('lint:gulp', function (cb) {
    runSequence(
      'jshint:gulp',
      'jscs:gulp',
      cb
    );
  });

  gulp.task('lint:scripts', function (cb) {
    runSequence(
      'jshint:scripts',
      'jscs:scripts',
      cb
    );
  });
};
