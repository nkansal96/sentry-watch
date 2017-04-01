const production = (process.env.NODE_ENV === "production");
let config = {};

if (production) {
    config.port = process.env.PORT;
    config.host = process.env.HOST;
} else {
    config.port = 3000;
    config.host = "localhost";
}

config.particleSettings = {};

module.exports = config;