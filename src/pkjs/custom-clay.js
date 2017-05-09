module.exports = function() {
  var clayConfig = this;
  var windowToggle;
  var flickToHide;
  
 
  function toggleShowDuration()
  {
    if (this.get()) {
      clayConfig.getItemByMessageKey('flick_show_duration').enable();
    } else {
      clayConfig.getItemByMessageKey('flick_show_duration').disable();
    }
  }
  
  function toggleDTWindowOptions()
  { 
   if (this.get()) {  
     flickToHide.enable();  
     toggleShowDuration.call(flickToHide);
     clayConfig.getItemByMessageKey('date_format').enable();
   } 
   else {  
      flickToHide.disable();      
      clayConfig.getItemByMessageKey('flick_show_duration').disable();
      clayConfig.getItemByMessageKey('date_format').disable();
    }
  }
  
  
  
  
 
    
  
  //after page loaded
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {  
      
    //if flick to hide is disabled - disable show duration
    flickToHide = clayConfig.getItemByMessageKey('enable_flick');
    toggleShowDuration.call(flickToHide);
    flickToHide.on('change', toggleShowDuration);
    
    //if data/tiem window is disabled - disable all realted settings
    windowToggle = clayConfig.getItemByMessageKey('enable_window');      
    toggleDTWindowOptions.call(windowToggle);
    windowToggle.on('change', toggleDTWindowOptions);
    
   
  });
  

};