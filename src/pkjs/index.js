var Clay = require('pebble-clay');
var clayConfig = require('./config');
var customClay = require('./custom-clay');
var clay = new Clay(clayConfig, customClay);
// // Import the Clay package
// var Clay = require('pebble-clay');
// // Load our Clay configuration file
// var clayConfig = require('./config');
// // Initialize Clay
// var clay = new Clay(clayConfig);

var claySettings = JSON.parse(localStorage.getItem('clay-settings'));

var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};

function locationSuccess(pos) {
  // Construct URL
  console.log("TEST" + claySettings.weather_api_key);
  var url = "http://api.openweathermap.org/data/2.5/weather?lat=-0.13&lon=51.51&APPID=" + claySettings.weather_api_key;

  // Send request
  xhrRequest(url, 'GET', 
    function(responseText) {
      var json = JSON.parse(responseText);

      // Temperature (in Celsius, because it doesn't suck)
      var temperature = Math.round(json.main.temp - 273.15);
      console.log("Temperature is " + temperature);
      
      // Push into a dictionary
      var dictionary = {
        "TEMPERATURE": temperature
      };

      // Send to Pebble
      MessageQueue.sendAppMessage(dictionary,
        function(e) {
          console.log("Weather info sent to Pebble successfully!");
        },
        function(e) {
          console.log("Error sending weather info to Pebble!");
        }
      );
    }      
  );
}

function locationError(err) {
  console.log("Error requesting location!");
}

function getWeather() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}

// Check when watch face opens
Pebble.addEventListener('ready', 
  function(e) {
    console.log("PebbleKit JS ready!");

    // Get weather immediately
    getWeather();
  }
);

// Check when the message is received
Pebble.addEventListener('appmessage',
  function(e) {
    var goal = e.payload.GOAL
    console.log("AppMessage received!");
    
  getWeather();
});