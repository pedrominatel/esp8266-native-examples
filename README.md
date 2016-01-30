# ESP8266 Native Examples

[My Blog](http://pedrominatel.com.br)

ESP8266 Native development examples

Those examples was developed to be used with the Native development in C language for the open-SDK.
The SDK installation can be found [here](https://github.com/pfalcon/esp-open-sdk).

If you want to add your example here, please, do not hesitate to pull request!

## Example Projects
================

* **blank-project**: Used for new projects with the drivers libs
* **wifi-connect**: Allow the simple WiFi connection as STATION
* **blink-os-task**: A simple LED blink using OS task
* **blink-os-timer**: A simple LED blink using timer
* **web-server**: Soon!
* **sensor-sht21**: An example to how to use the SHT21 on ESP8266
 
## Supported Boards and Modules
================

This code was tested in the [nodeLHC](https://hackaday.io/project/7763-nodelhc-esp8266-development-board) project that uses the ESP-07 module.

It shoud run on any ESP8266 version!

**Please, in case of any problem, open a bug!**

## Build and Flash
================

To build the projects, each project have the Makefile

To build and flash to the device:

* **$ make clean & make & make flash**
