'use strict';

var chai = require('chai');
var expect = chai.expect;

var windowsMgr = require('../lib');

describe('windows-manager', function () {
  describe('exports', function () {
    expect(windowsMgr.getAll).to.be.a('function');
    expect(windowsMgr.getTitle).to.be.a('function');
    expect(windowsMgr.setToForeground).to.be.a('function');
    expect(windowsMgr.minimize).to.be.a('function');
    expect(windowsMgr.activate).to.be.a('function');
    expect(windowsMgr.restore).to.be.a('function');
    expect(windowsMgr.show).to.be.a('function');
    expect(windowsMgr.maximize).to.be.a('function');
    expect(windowsMgr.isForeground).to.be.a('function');
    expect(windowsMgr.isMinimized).to.be.a('function');
    expect(windowsMgr.setTopMost).to.be.a('function');
    expect(windowsMgr.close).to.be.a('function');
    expect(windowsMgr.getCurrent).to.be.a('function');
  });
});