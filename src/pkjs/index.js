//CLAY
var Clay = require('pebble-clay');
var clayConfig = require('./config');
var customClay = require('./custom-clay');
var clay = new Clay(clayConfig, customClay);


//WEATHER
var claySettings = JSON.parse(localStorage.getItem('clay-settings'));


var xhrRequest = function (url, type, callback) {
  var xhr = new XMLHttpRequest();
  xhr.onload = function () {
    callback(this.responseText);
  };
  xhr.open(type, url);
  xhr.send();
};


function fetchWeatherGps(lat, lang)
{
   var url = "http://api.openweathermap.org/data/2.5/weather?lat="+lat+"&lon="+lang+"&cnt=1&APPID=db8a85437a0dab1e93d39ca60326d0a1";// + claySettings.weather_api_key;
   console.log(url);
   fetchWeather(url);
}

function fetchWeatherFxdLocation(location)
{
   
   var url = "http://api.openweathermap.org/data/2.5/weather?q="+ location +"&APPID=db8a85437a0dab1e93d39ca60326d0a1";// + claySettings.weather_api_key;
   console.log(url);
   fetchWeather(url);
}

function iconFromWeatherIcon(iconId) {
  //no breaks because we put same icon for day & night
  switch(iconId) {
		case "01d":
		case "01n": return 1; // Clear day
		case "02d":
		case "02n": return 2; // few clouds
		case "03d":
		case "03n":  // scattered  clouds
		case "04d":
		case "04n": return 3; // broken clouds
		case "09d":
		case "09n":
		case "10d":
		case "10n": return 4; // Rain
		case "11d":
		case "11n": return 5; // Thunder
		case "13d":
		case "13n": return 6; // Snow
		case "50d":
		case "50n": return 7; // mist
		default: return 0; // Not available
	}
}
  
//   if (weatherId < 233) { //thunderstorm
//     return 1;
//   } else if (weatherId < 532) { //shower rain/rain
//     return 2;
//   } else if (weatherId < 623) { //snow
//     return 3;
//   } else if (weatherId < 782) { //mist
//     return 4;
//   } else if (weatherId == 800) { //clear sky
//     return 5;
//   } else if (weatherId == 801) { //few clouds
//     return 6;
//   } else if (weatherId == 802) { //scattered clouds
//     return 7;
//   } else if (weatherId == 803 || weatherId == 804) { //broken clouds
//     return 8;
//   } else {
//     return 0;
//   }



function fetchWeather(url)
{
  // Send request
  xhrRequest(url, 'GET', 
    function(responseText) {
      var json = JSON.parse(responseText);
      //console.log(responseText);
      
      //if we received weather information
      if(json.cod == 200)
      {
          // Temperature (in Celsius, because it doesn't suck)
          var temperature = Math.round(json.main.temp - 273.15);
          console.log("Temperature is " + temperature);
      
          // Conditions
          var icon = iconFromWeatherIcon(json.weather[0].icon);
         
          // Push into a dictionary
          var dictionary = {
            "weather_temperature": temperature  + '\xB0C',
            "weather_icon": icon
          };

          // Send to Pebble
          Pebble.sendAppMessage(dictionary,
            function(e) {
              console.log("Weather info sent to Pebble successfully!");
            },
            function(e) {
              console.log("Error sending weather info to Pebble!");
            }
          );
      }
      
    }      
  );
}



function locationSuccess(pos) {
  var coords = pos.coords;
  fetchWeatherGps(coords.latitude, coords.longitude);    
}

function locationError(err) {
  console.log("Error requesting location!");
  Pebble.sendAppMessage({
     "weather_temperature": 'N/A',
     "weather_icon": 0
  });
}

function getWeatherWithGps() {
  navigator.geolocation.getCurrentPosition(
    locationSuccess,
    locationError,
    {timeout: 15000, maximumAge: 60000}
  );
}



// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
  function(e) {
    console.log("PebbleKit JS ready!");
    
    // Get the initial weather
    // if it is enabled in settings
    // comparision with null because user may skip clas settings window
    // and setting will be uninicialized
    //Pebble.showSimpleNotificationOnPebble("problem", "problem");
   
    if(claySettings === null || claySettings.weather_enabled)
    {
      // use gps or fixed location based on settings
      if(claySettings === null || claySettings.weather_gps_on)
      {
        console.log("Gps");    
        getWeatherWithGps();
      }      
      else
      {
        console.log("Fixed location");
        //get fixed location from settings    
        var location = claySettings.weather_fixed_location;
        fetchWeatherFxdLocation(location);
        
      }
    }
   
   
      
  }
);


// Check when the message is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log("AppMessage received!");    
    if(claySettings.weather_gps_on)
      getWeatherWithGps();
    else
    {
      //get fixed location from settings    
      var location = claySettings.weather_fixed_location;
      fetchWeatherFxdLocation(location);
      
    }
});