const express = require('express');
let router = express.Router();

router.post('/panic', (req, res) => {
	console.log(req.body);

	res.json({});
});

router.post('/struggle', (req, res) => {
	console.log(req.body);

	res.json({});
});

module.exports = { router };
