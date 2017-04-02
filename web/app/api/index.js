const express = require('express');
let router = express.Router();

router.use('/mobile', require('./mobile').router);
router.use('/particle', require('./particle').router);

module.exports = { router };
