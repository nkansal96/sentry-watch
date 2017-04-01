const express = require('express');
let router = express.Router();

router.use('/mobile', require('./mobile'));
// router.use('/particle', require('./particle'));

module.exports = { router };