'use strict';

module.exports = {
  paths: {
    lib: './lib/**/*.js',
    test: './test/**/*.spec.js',
    scripts: './scripts/**/*.js',
    gulp: ['./gulpfile.js', './gulp/**/*.js'],
    coverage: 'coverage/**/lcov.info'
  },
  manifests: ['./package.json']
};