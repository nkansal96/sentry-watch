const express = require('express');
let config = require('../../config');
let router = express.Router();

router.post('/configure', (req, res) => {
	// Emergency contact strings
	config.particleSettings.emergencyContacts = [req.body.emergencyContact1, req.body.emergencyContact2];
	
	// Config boolean values
	config.particleSettings.alertEMS = req.body.alertEmergencyServices;
	config.particleSettings.enableStruggleDetection = req.body.enableStruggleDetection;
	config.particleSettings.enablePanicButton = req.body.enablePanicButton;
	config.particleSettings.enableSound = req.body.enableSound;
	config.particleSettings.enableLEDs = req.body.enableLEDs;

	console.log(req.body);
	console.log(config.particleSettings);

	res.send();
});

module.exports = { router };
