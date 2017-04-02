var accountSid = 'AC13d81364e0e7c9b07ae5e8407ef966cc';
var authToken = '00920e566b42c3f90f1d5b3874c52229';

var twilio = require('twilio');
var client = new twilio.RestClient(accountSid, authToken);

function sendText(text, receiver, callback){
	client.messages.create({
		body: text,
		to: receiver,
		from: '15108172421'
	}, function(err, message) {
		callback(err, message);
	});
}

module.exports = { sendText };
