const express = require('express');
let config = require('../../config');
let twilio = require('../../twilio');
let router = express.Router();

router.post('/panic', (req, res) => {
	console.log('Panic:')
	console.log(req.body);

	let msg = config.particleSettings.name + " has sent you a panic alert. His/her last known location was .";
	var emergencyContacts = config.particleSettings.emergencyContacts;

	for (var i = 0; i < emergencyContacts.length; i++) {
		if (emergencyContacts[i] !== undefined && emergencyContacts[i].length !== 0)
			twilio.sendText(msg, emergencyContacts[i], (err, message) => {
				console.log(err, message);
				console.log('Panic alert sent');
			});
	}

	res.json({});
});

router.post('/struggle', (req, res) => {
	console.log('Struggle:')
	console.log(req.body);

	let msg = config.particleSettings.name + "\'s behavior indicates that he/she is in a physical struggle. His/her last known location was .";
	var emergencyContacts = config.particleSettings.emergencyContacts;

	for (var i = 0; i < emergencyContacts.length; i++) {
		if (emergencyContacts[i] !== undefined && emergencyContacts[i].length !== 0)
			twilio.sendText(msg, emergencyContacts[i], (err, message) => {
				console.log(err, message);
				console.log('Struggle alert sent');
			});
	}

	res.json({});
});

module.exports = { router };
