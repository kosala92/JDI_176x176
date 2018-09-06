#define JDI_BLACK     0x00
#define JDI_BLUE      0x02
#define JDI_GREEN     0x04
#define JDI_CYAN      0x06
#define JDI_RED       0x08
#define JDI_MAGENTA   0x0a
#define JDI_YELLOW    0x0c
#define JDI_WHITE     0x0e

#define JDI_CMD_UPDATE            0x90
#define JDI_CMD_ALL_CLEAR         0x20
#define JDI_CMD_NO_UPDATE         0x00
#define JDI_CMD_INVERSION         0x14
#define JDI_CMD_VCOM              0x40

#ifndef _LCD_JDI_176_H
#define _LCD_JDI_176_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <SPI.h>
#include <Adafruit_GFX.h>

class LCD_JDI : public Adafruit_GFX{
 public:
  LCD_JDI(uint8_t ss, uint16_t width = 176, uint16_t height = 176);
  boolean begin();
  void refresh(void);
  void background(uint16_t color);
  void mode(char mode);
  void invertDisplay(boolean isInvert);
  void clearDisplay(boolean isClear);

 private:
  uint8_t   _ss;
  uint16_t  _background;
  uint32_t  _vcom;
  char cmd_buf[88];
  char disp_buf[88*176];
  void sendLineCommand(char* line_cmd, int line);
  void drawPixel(int16_t x, int16_t y, uint16_t color);
};

#endif