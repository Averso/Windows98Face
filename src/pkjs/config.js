module.exports = [
  
  //---heading---//
  {
    "type": "heading",
    "defaultValue": "WINDOWS 98"
  },
  
  //---colors---//
  {
    "type": "section",
    "items":
    [
      {
        "type": "heading",
        "defaultValue": "Colors"
      },
      {
        "type": "toggle",
        "messageKey": "color_background_bw",
        "label": "Desktop color black/white",
        "defaultValue": true,
        "capabilities": ["BW"]
      },
      {
        "type": "color",
        "messageKey": "color_background",
        "defaultValue": "0x00AAAA",
        "label": "Background Color",
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "color_text",
        "defaultValue": "0xFFFFFF",
        "label": "Desktop text color",
        "capabilities": ["COLOR"]
      }
    ]
  },
  
  //---datetime windows---//
  {
    "type": "section",
    "items" :
    [
      {
        "type": "heading",
        "defaultValue": "Date&time window"
      },
      {
        "type": "toggle",
        "messageKey": "date_format",
        "label": "Date format",
        "description": "dd-mm-yyyy/mm-dd-yyyy",
        "defaultValue": false
      },
      {
        "type":"slider",
        "messageKey": "flick_display_duration",
        "defaultValue": 10,
        "label": "Display duration",
        "description": "How long date&time window will be displayed after flick (in seconds).",
        "min": 1,
        "max": 60,
        "step": 1 
      }                 
    ]
  },
  
  //---weather---//
  {
    "type": "section",      
    "items": 
    [
      {
      "type": "heading",
      "defaultValue": "Weather"
      },                   
      {
        "type": "toggle",
        "messageKey": "weather_enabled",
        "label": "Enable weather",
        "defaultValue": true
      },
      {
        "type": "input",
        "messageKey": "weather_api_key",
        "defaultValue": "",
        "label": "OpenWeatherMaps API key",
      },
      {
        "type": "toggle",
        "messageKey": "weather_units",
        "label": "Units",
        "description": "Fahrenheit/Celsius",
        "defaultValue": true
      },
      {
        "type": "toggle",
        "messageKey": "weather_gps_on",
        "label": "Use GPS",
        "defaultValue": true
      },
      {
        "type": "input",
        "messageKey": "weather_fixed_location",
        "defaultValue": "",
        "label": "Fixed location",
        "attributes": {
          "placeholder": "City,Counry Code",        
        }        
      },
      {
        "type":"slider",
        "messageKey": "weather_update_interval",
        "defaultValue": "30",
        "label": "Update interval",
        "description": "Weather update interval in minutes",
        "min": 15,
        "max": 60,
        "step": 5 
      }
      
    ]
  },
  
  //---battery---//
  {
    "type":"section",
    "items": 
    [
      {
        "type":"heading",
        "defaultValue":"Battery"
      },
      {
        "type": "toggle",
        "messageKey": "battery_mode",
        "label": "Battery mode",
        "description": "Recycle Bin/Battery Icon",
        "defaultValue": false
      },
      {
        //---recycle bin---//
        "type": "section",
        "items": 
        [
          {
          "type": "heading",
          "defaultValue": "Recycle Bin",       
          },
          {
          "type": "toggle",
          "messageKey": "switch_bin_state",
          "label": "Switch bin state",
          "description": "Switch low battery warning state for recycle bin. Set: low = empty; Unset: low = full bin.",
          "defaultValue": false
         },
         {
          "type": "slider",
          "messageKey": "battery_warning_level",
          "defaultValue": 40,
          "label": "Baterry warning level",
          "description": "On what battery percentage warning will indicate.",
          "min": 10,
          "max": 100,
          "step": 10          
         }     
        ]
      }
      
    ]
  },
  
  //---others---//
  {
    "type": "section",      
    "items": 
    [
      {
      "type": "heading",
      "defaultValue": "Others"
      },               
      {
        "type": "toggle",
        "messageKey": "vibe_on_disconnect",
        "label": "Vibrate on disconnect",
        "defaultValue": true
      }
    ]
  },
  
  //---submit---//
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
  
  
];