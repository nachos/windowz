'use strict';

var exec = require('child_process').exec;
var Q = require('q');
var path = require('path');

var whichNativeNodish = require('which-native-nodish');

var execQ = function (command, opts) {
  return Q.nfcall(exec, command, opts);
};

var nwVersion = null;
var asVersion = null;

return whichNativeNodish('..')
  .then(function (results) {
    nwVersion = results.nwVersion;
    asVersion = results.asVersion;
  })
  .then(function () {
    if (nwVersion) {
      console.info('Need to build for node-webkit/nw.js');

      return build();
    }
    else if (asVersion) {
      console.info('Need to build for atom-shell');

      return build();
    }

    if (process.env.BUILD_DEBUG) {
      console.info('Doing a debug build, no fetching allowed.');

      return build();
    }

    if (process.env.BUILD_ONLY) {
      console.info('BUILD_ONLY is set to true, no fetching allowed.');

      return build();
    }

    console.info('Fetching binary from S3.');

    return execQ('node-pre-gyp install')
      .then(
      function () {
        console.info('Completed installation successfully.');
      },
      function () {
        console.info('Failed to install prebuilt binary, building manually.');

        return build();
      }
    );
  });

function build() {
  console.info('Starting compilation');

  if (nwVersion) {
    console.info('Building native node-webkit module.');
  }
  else {
    console.info('Building native node module.');
  }

  var opts = {
    cwd: '.',
    maxBuffer: Number.MAX_VALUE,
    env: process.env
  };

  var prefix = '';
  var target = '';
  var debug = (process.env.BUILD_DEBUG ? ' --debug' : '');
  var builder = 'pangyp';
  var distUrl = '';

  if (asVersion) {
    prefix = (process.platform === 'win32' ?
      'SET HOME=%HOME%\\.atom-shell-gyp&& ' :
      'HOME=~/.atom-shell-gyp');

    target = '--target=' + asVersion;
    distUrl = '--dist-url=https://atom.io/download/atom-shell';
  }
  else if (nwVersion) {
    builder = 'nw-gyp';
    target = '--target=' + nwVersion;
  }

  return execQ('npm install --ignore-scripts')
    .then(function () {
      builder = path.resolve('.', 'node_modules', '.bin', builder);
      builder = builder.replace(/\s/g, '\\$&');
      var cmd = [prefix, builder, 'rebuild', target, debug, distUrl]
        .join(' ').trim();

      return execQ(cmd, opts);
    })
    .then(function () {
      console.info('Compilation complete.');
      console.info('Completed installation successfully.');
    },
    function (err, stderr) {
      console.error(err);
      console.error(stderr);
    });
}