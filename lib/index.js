'use strict';

var bindings = require('bindings');

module.exports = bindings('windows');

var child = 65552;
var parent = module.exports.createDesktopWindow();
module.exports.activate(parent);
console.log(module.exports.setParent(child, parent));

setInterval(function () {

});