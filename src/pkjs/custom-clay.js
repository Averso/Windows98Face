module.exports = function() {
  var clayConfig = this;
  var windowToggle;
  var centerPosToggle;
  
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
  
  function togglePosition()
  { 
   if (this.get()) {
     centerPosToggle.enable();
     toggleXYPosition.call(centerPosToggle);
     clayConfig.getItemByMessageKey('date_format').enable();
    } else {
     centerPosToggle.disable();
      clayConfig.getItemByMessageKey('window_x').disable();
     clayConfig.getItemByMessageKey('window_y').disable();
      clayConfig.getItemByMessageKey('date_format').disable();
    }
  }
  
  
 
    
  
  //after page loaded
  clayConfig.on(clayConfig.EVENTS.AFTER_BUILD, function() {  
    centerPosToggle = clayConfig.getItemByMessageKey('center_pos');
    toggleXYPosition.call(centerPosToggle);
    centerPosToggle.on('change', toggleXYPosition);
    
    windowToggle = clayConfig.getItemByMessageKey('enable_window');      
    togglePosition.call(windowToggle);
    windowToggle.on('change', togglePosition);
    
   
  });
  

};