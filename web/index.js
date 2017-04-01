const express = require('express');
const bodyParser = require('body-parser');
const compression = require('compression');
let app = require('./app');
let server = express();

server.use(compression());
server.use(bodyParser.json());
server.use(express.static('www/public', { maxAge: 1000 * 60 * 60 * 24 * 30 }));

server.listen(app.config.port, () => {
    console.log("Started server on port", app.config.port);
});