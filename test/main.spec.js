'use strict';

var chai = require('chai');
var expect = chai.expect;

describe('windowz', function () {
  var windowz = require('../lib');

  describe('exports', function () {
    it('should expose api', function () {
      expect(windowz.getAll).to.be.a('function');
      expect(windowz.getTitle).to.be.a('function');
      expect(windowz.setToForeground).to.be.a('function');
      expect(windowz.minimize).to.be.a('function');
      expect(windowz.activate).to.be.a('function');
      expect(windowz.show).to.be.a('function');
      expect(windowz.maximize).to.be.a('function');
      expect(windowz.isForeground).to.be.a('function');
      expect(windowz.isMinimized).to.be.a('function');
      expect(windowz.setTopMost).to.be.a('function');
      expect(windowz.close).to.be.a('function');
      expect(windowz.getCurrent).to.be.a('function');
    });
  });
});