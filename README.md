# Mini Moving Head

Design for a small moving head with a 3W RGB LED, controlled by DMX, and powered with an ESP8266.

## Firmware
Firmware is written using the ESP8266 Arduino integration.

Libraries used:
* [LXESP8266DMX](https://github.com/claudeheintz/LXESP8266DMX) for DMX input
* ESP8266 standard Servo library

## Electronics
Schematics are designed in KiCAD.

The LED driver design is based on [this design](http://www.tbideas.com/blog/build-an-arduino-shield-to-drive-high-power-rgb-led/) by TBIdeas.

Component Libraries:
* [ESP8266](https://github.com/jdunmire/kicad-ESP8266)
