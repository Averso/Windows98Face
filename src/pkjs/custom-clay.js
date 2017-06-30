module.exports = function() {
  var clayConfig = this;
  var batteryModeToggle;

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
    
  //after page loaded
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {  
   
    
    //if battery mode is enabled (in battery icon mode), disable recycle bin settings
    batteryModeToggle = clayConfig.getItemByMessageKey('battery_mode');
    toggleRBinSettings.call(batteryModeToggle);
    batteryModeToggle.on('change',toggleRBinSettings);
   
  });
  

};