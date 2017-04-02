const express = require('express');
let config = require('../../config');
let twilio = require('../../twilio');
let router = express.Router();

var lastNotified = 0;

var locations = ['https://goo.gl/maps/cDHMxfLpdiy', 'https://goo.gl/maps/G2fkpjN3e6R2', 'https://goo.gl/maps/gwdg8zG5jo52', 'https://goo.gl/maps/RQHihxYEdYR2'];
var emergencyServicesPhone = '6267203271';		// Temp phone number

var minIndex = 0;
var maxIndex = 3;

router.post('/panic', (req, res) => {
	console.log('Panic:')

	if (Date.now() < lastNotified+20000) {
		console.log("Already sent a notification in the last 20 seconds");
		return res.json({});
	}

	var randIndex = Math.floor(Math.random() * (maxIndex - minIndex + 1)) + minIndex;
	console.log('randIndex: ' + randIndex);

	let msg = config.particleSettings.name + " has sent you a panic alert. His/her last known location was at: " + locations[randIndex];
	
	var emergencyContacts = config.particleSettings.emergencyContacts;
	var toSend = config.particleSettings.enablePanicButton;
	var alertEmergencyServices = config.particleSettings.alertEmergencyServices;

	for (var i = 0; i < emergencyContacts.length; i++) {
		if (toSend && emergencyContacts[i] !== undefined && emergencyContacts[i].length !== 0)
			twilio.sendText(msg, emergencyContacts[i], (err, message) => {
				// console.log(err, message);
				console.log('Panic alert sent, at ' + Date.now());
				lastNotified = Date.now();
			});
	}

	if (alertEmergencyServices) {
		var emergencyMsg = config.particleSettings.name + " has sent out a panic alert and is requesting emergency services. His/her last known location was at: " + locations[randIndex];
		twilio.sendText(emergencyMsg, emergencyServicesPhone, (err, message) => {
			// console.log(err, message);
			console.log('Panic alert sent to emergency services');
		});
	}

	res.json({});
});

router.post('/struggle', (req, res) => {
	console.log('Struggle:')

	if (Date.now() < lastNotified+20000) {
		console.log("Already sent a notification in the last 20 seconds");
		return res.json({});
	}

	var randIndex = Math.random() % 4;
	console.log('randIndex: ' + randIndex);

	let msg = config.particleSettings.name + "\'s behavior indicates that he/she is in a physical struggle. His/her last known location was at: " + locations[randIndex];
	
	var emergencyContacts = config.particleSettings.emergencyContacts;
	var toSend = config.particleSettings.enableStruggleDetection;
	var alertEmergencyServices = config.particleSettings.alertEmergencyServices;

	for (var i = 0; i < emergencyContacts.length; i++) {
		if (toSend && emergencyContacts[i] !== undefined && emergencyContacts[i].length !== 0)
			twilio.sendText(msg, emergencyContacts[i], (err, message) => {
				// console.log(err, message);
				console.log('Struggle alert sent, at ' + Date.now());
				lastNotified = Date.now();
			});
	}

	if (alertEmergencyServices) {
		var emergencyMsg = config.particleSettings.name + "\'s behavior indicates that he/she is in a physical struggle and emergency services are being requested. His/her last known location was at: " + locations[randIndex];
		twilio.sendText(emergencyMsg, emergencyServicesPhone, (err, message) => {
			// console.log(err, message);
			console.log('Struggle alert sent to emergency services');
		});
	}

	res.json({});
});

module.exports = { router };
