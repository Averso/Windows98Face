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
        "type": "color",
        "messageKey": "bg_color",
        "defaultValue": "0x00AAAA",
        "label": "Background Color"
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
        "defaultValue": "Position",       
      },
      {
        "type": "toggle",
        "messageKey": "center_pos",
        "label": "Center window",
        "defaultValue": false
      },
      {
        "type": "input",
        "messageKey": "window_x",
        "defaultValue": "23",
        "description": "Defaults 23",
        "label": "X position",
        "attributes": {
        "type": "number",
        "max":"28",
        "min":"0"
      }
      },
      {
        "type": "input",
        "messageKey": "window_y",
        "defaultValue": "23",
        "description": "Default 23",
        "label": "Y position",
        "attributes": {
        "type": "number",
        "max":"32",
        "min":"0"
      }
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
        "defaultValue": false
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];