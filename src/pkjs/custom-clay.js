module.exports = function() {
  var clayConfig = this;
  var batteryModeToggle;
  var weatherToggle;
  var weatherGpsToggle;
  
  function toggleRBinSettings()
  {
    if(this.get())
    {
      clayConfig.getItemByMessageKey('switch_bin_state').disable();
      clayConfig.getItemByMessageKey('battery_warning_level').disable();
    }
    else 
    {
      clayConfig.getItemByMessageKey('switch_bin_state').enable();
      clayConfig.getItemByMessageKey('battery_warning_level').enable();
    }
  }
  
  function toggleFxdLocSettings()
  {
    if(this.get())
    {
      clayConfig.getItemByMessageKey('weather_fixed_location').disable();
    }
    else 
    {
      clayConfig.getItemByMessageKey('weather_fixed_location').enable();
    }
  }
  
  function toggleWeatherSettings()
  {
    if(this.get())
    {
      clayConfig.getItemByMessageKey('weather_units').show();
      clayConfig.getItemByMessageKey('weather_gps_on').show();
      clayConfig.getItemByMessageKey('weather_fixed_location').show();
      clayConfig.getItemByMessageKey('weather_update_interval').show();
      clayConfig.getItemByMessageKey('weather_api_key').show();
    }
    else 
    {
      clayConfig.getItemByMessageKey('weather_units').hide();
      clayConfig.getItemByMessageKey('weather_gps_on').hide();
      clayConfig.getItemByMessageKey('weather_fixed_location').hide();
      clayConfig.getItemByMessageKey('weather_update_interval').hide();      
      clayConfig.getItemByMessageKey('weather_api_key').hide();
    }
  }
    
  //after page loaded
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {  
      
    //if battery mode is enabled (in battery icon mode), disable recycle bin settings
    batteryModeToggle = clayConfig.getItemByMessageKey('battery_mode');
    toggleRBinSettings.call(batteryModeToggle);
    batteryModeToggle.on('change',toggleRBinSettings);
   
    //if gps is enabled, disable fixed location
    weatherGpsToggle = clayConfig.getItemByMessageKey('weather_gps_on');
    toggleFxdLocSettings.call(weatherGpsToggle);
    weatherGpsToggle.on('change',toggleFxdLocSettings);
    
    //if weather settings are disabled, hide section
    weatherToggle = clayConfig.getItemByMessageKey('weather_enabled');
    toggleWeatherSettings.call(weatherToggle);
    weatherToggle.on('change', toggleWeatherSettings);
    
  });
  

};