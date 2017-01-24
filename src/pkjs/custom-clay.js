module.exports = function() {
  var clayConfig = this;
  var windowToggle;
  var centerPosToggle;
  var flickToHide;
  
   function toggleXYPosition()
  { 
   if (this.get()) {
      clayConfig.getItemByMessageKey('window_x').disable();
     clayConfig.getItemByMessageKey('window_y').disable();
    } else {
      clayConfig.getItemByMessageKey('window_x').enable();
     clayConfig.getItemByMessageKey('window_y').enable();
    }
  }
  
  function toggleShowDuration()
  {
    if (this.get()) {
      clayConfig.getItemByMessageKey('flick_show_duration').enable();
    } else {
      clayConfig.getItemByMessageKey('flick_show_duration').disable();
    }
  }
  
  function togglePosition()
  { 
   if (this.get()) {
     centerPosToggle.enable();
     flickToHide.enable();
     toggleXYPosition.call(centerPosToggle);
     toggleShowDuration.call(flickToHide);
     clayConfig.getItemByMessageKey('date_format').enable();
   } 
   else {
      centerPosToggle.disable();
      flickToHide.disable();      
      clayConfig.getItemByMessageKey('flick_show_duration').disable();
      clayConfig.getItemByMessageKey('window_x').disable();
      clayConfig.getItemByMessageKey('window_y').disable();
      clayConfig.getItemByMessageKey('date_format').disable();
    }
  }
  
  
  
  
 
    
  
  //after page loaded
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {  
    //if center position is enabled - diable manual position settings
    centerPosToggle = clayConfig.getItemByMessageKey('center_pos');
    toggleXYPosition.call(centerPosToggle);
    centerPosToggle.on('change', toggleXYPosition);
    
    //if flick to hide is disabled - disable show duration
    flickToHide = clayConfig.getItemByMessageKey('enable_flick');
    toggleShowDuration.call(flickToHide);
    flickToHide.on('change', toggleShowDuration);
    
    //if data/tiem window is disabled - disable all realted settings
    windowToggle = clayConfig.getItemByMessageKey('enable_window');      
    togglePosition.call(windowToggle);
    windowToggle.on('change', togglePosition);
    
   
  });
  

};