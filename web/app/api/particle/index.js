const express = require('express');
let router = express.Router();

router.post('/panic', (req, res) => {
	console.log(req.body);

	res.send();
});

router.post('/struggle', (req, res) => {
	console.log(req.body);

	res.send();
});

module.exports = { router };
