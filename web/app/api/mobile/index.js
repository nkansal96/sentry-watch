const express = require('express');
let config = require('../../config');
let router = express.Router();

router.post('/configure', (req, res) => {
	config.particleSettings.name = req.body.name;
	config.particleSettings.emergencyContacts = [req.body.emergencyContact1, req.body.emergencyContact2];
	
	// Config boolean values
	config.particleSettings.alertEmergencyServices = req.body.alertEmergencyServices === 'true';
	config.particleSettings.enableStruggleDetection = req.body.enableStruggleDetection === 'true';
	config.particleSettings.enablePanicButton = req.body.enablePanicButton === 'true';
	config.particleSettings.enableLEDs = req.body.enableLEDs === 'true';
	
	// console.log(req.body);
	console.log('Configurations:');
	console.log(config.particleSettings);

	res.send();
});

module.exports = { router };
