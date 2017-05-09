module.exports = [
  {
    "type": "heading",
    "defaultValue": "WINDOWS 98"
  },
  {
    "type": "section",
    
    "items": [
      {
        "type": "heading",
        "defaultValue": "Colors"
      },
      {
        "type": "toggle",
        "messageKey": "bg_color_bw",
        "label": "Desktop color black/white",
        "defaultValue": false,
        "capabilities": ["BW"]
      },
      {
        "type": "toggle",
        "messageKey": "monochrome_enabled",
        "label": "Monochrome",
        "description": "Turns on monochrome theme. You can still change background and text color.",
        "defaultValue": false,
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "bg_color",
        "defaultValue": "0x00AAAA",
        "label": "Background Color",
        "capabilities": ["COLOR"]
      },
      {
        "type": "color",
        "messageKey": "text_color",
        "defaultValue": "0xFFFFFF",
        "label": "Desktop text color",
        "capabilities": ["COLOR"]
      }
    ]
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Data/time window settings"
      },
      {
        "type": "toggle",
        "messageKey": "enable_window",
        "label": "Enable data/time window",
        "defaultValue": false
      },      
      {
      "type": "section",
      "items": [
      {
        "type": "heading",
        "defaultValue": "Flick",       
      },
      {
        "type": "toggle",
        "messageKey": "enable_flick",
        "label": "Enable flick to show/hide data/time window",
        "defaultValue": false
      },
      {
        "type": "input",
        "messageKey": "flick_show_duration",
        "defaultValue": "10",
        "description": "Default: 10s. Max: 60s ",
        "label": "Show duration.",
        "attributes": {
        "type": "number",
        "max":"60",
        "min":"1"
        }
      }
      
      ]},
      
      {
      "type": "section",
      "items": [
      {
        "type": "heading",
        "defaultValue": "Others",       
      },
      {
        "type": "toggle",
        "messageKey": "date_format",
        "label": "Date format",
        "description": "dd-mm-yyyy/mm-dd-yyyy",
        "defaultValue": false
      }   
      
      ]}
       
    ]
  },
  {
    "type": "section",      
    "items": [
      {
      "type": "heading",
      "defaultValue": "Others"
      },
      {
        "type": "toggle",
        "messageKey": "switch_bin_state",
        "label": "Switch bin states",
        "description": "Switch default low battery warning states for recycle bin. Set: low = empty; Unset: low = full.",
        "defaultValue": false
      },
      {
        "type": "input",
        "messageKey": "battery_warning_level",
        "defaultValue": "40",
        "label": "Baterry warning level",
        "attributes": {
        "type": "number",
        "max":"100",
        "min":"1"
        }
      },
      {
        "type": "toggle",
        "messageKey": "vibe_disconnect",
        "label": "Vibrate on disconnect",
        "defaultValue": true
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];