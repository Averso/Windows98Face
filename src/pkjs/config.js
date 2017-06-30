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
        "type": "input",
        "messageKey": "flick_display_duration",
        "defaultValue": "10",
        "description": "How long date&time window will be displayed after flick (in seconds).",
        "label": "Display duration.",
        "attributes": {
        "type": "number",
        "max":"60",
        "min":"1"
        }
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
        "type": "toggle",
        "messageKey": "weather_enabled",
        "label": "Enable weather",
        "defaultValue": true
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
          "type": "input",
          "messageKey": "battery_warning_level",
          "defaultValue": "40",
          "label": "Baterry warning level",
          "description": "On what battery percentage warning will indicate.",
          "attributes": {
          "type": "number",
          "max":"100",
          "min":"1"
          }
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