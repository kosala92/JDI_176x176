/* 
	Editor: http://www.visualmicro.com
			visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
			the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
			all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
			note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Adafruit Metro M0 Express, Platform=samd, Package=adafruit
*/

#define ARDUINO 10805
#define ARDUINO_MAIN
#define F_CPU 48000000L
#define printf iprintf
#define __SAMD__
#define F_CPU 48000000L
#define ARDUINO 10805
#define ARDUINO_SAMD_ZERO
#define ARDUINO_ARCH_SAMD
#define __SAMD21G18A__
#define ARM_MATH_CM0PLUS
#define ADAFRUIT_METRO_M0_EXPRESS
#define USB_VID 0x239A
#define USB_PID 0x8013
#define USBCON
void setup(void);
void loop(void);
void drawText(char *text1, char *text2, uint8_t textSize);
void drawEightColor();
void drawRainMan();
void pollingTimerHandler();

#include "pins_arduino.h" 
#include "variant.h" 
#include "Arduino.h"
#include "LCD_JDI_example.ino"
