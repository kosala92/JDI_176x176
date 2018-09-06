#include "LCD_JDI_176.h"

#define TOGGLE_VCOM                     do { _vcom = _vcom ? 0x00 : JDI_CMD_VCOM; } while(0);

LCD_JDI::LCD_JDI(uint8_t ss, uint16_t width, uint16_t height)
:Adafruit_GFX(width, height){
  _ss   = ss;
}

boolean LCD_JDI::begin(void) {
  digitalWrite(_ss, LOW);
  pinMode(_ss, OUTPUT);

  SPI.begin();

  _background = JDI_BLACK;
  _vcom = JDI_CMD_VCOM;

  memset(&cmd_buf[0], 0, sizeof(cmd_buf));
  memset(&disp_buf[0], (char)((_background & 0x0F) | ((_background & 0x0F) << 4)), sizeof(disp_buf));

  clearDisplay(true);
  return true;
}

void LCD_JDI::refresh(void)
{
  for(int i=0; i < HEIGHT; i++){
    memset(&cmd_buf[0], (char)((_background & 0x0F) | ((_background & 0x0F) << 4)), sizeof(cmd_buf));
    memcpy(&cmd_buf[0], &disp_buf[(WIDTH/2) * i], WIDTH/2);
    sendLineCommand(&cmd_buf[0], i);
  }
}

void LCD_JDI::sendLineCommand(char* line_cmd, int line){
  int32_t j;

  if((line < 0) || (line >= HEIGHT)){
    return;
  }

  digitalWrite(_ss, HIGH);
  SPI.transfer(JDI_CMD_UPDATE | _vcom);
  TOGGLE_VCOM;
  SPI.transfer(line + 1);

  for(j = 0; j < (WIDTH/2); j++){
    SPI.transfer(line_cmd[j]);
  }

  for( ; j < (WIDTH/2) ; j++){
    SPI.transfer( 0x00 );
  }

  SPI.transfer(0x00);
  SPI.transfer(0x00);
  digitalWrite(_ss, LOW);
}

void LCD_JDI::drawPixel(int16_t x, int16_t y, uint16_t color)
{
  if((x >= WIDTH) || (y >= HEIGHT)){
    return;
  }

  if(x%2 == 0){
    disp_buf[((WIDTH/2)*y) + (x/2)] &= 0x0F;
    disp_buf[((WIDTH/2)*y) + (x/2)] |= (color & 0x0F) << 4;
  }
  else{
    disp_buf[((WIDTH/2)*y) + (x/2)] &= 0xF0;
    disp_buf[((WIDTH/2)*y) + (x/2)] |= color & 0x0F;
  }
}

void LCD_JDI::clearDisplay(boolean isClear)
{
  digitalWrite(_ss, HIGH);
  SPI.transfer(_vcom | (isClear ? JDI_CMD_ALL_CLEAR : JDI_CMD_NO_UPDATE));
  SPI.transfer(0x00);
  TOGGLE_VCOM;
  digitalWrite(_ss, LOW);
}

void LCD_JDI::invertDisplay(boolean isInvert)
{
  digitalWrite(_ss, HIGH);
  SPI.transfer(_vcom | (isInvert ? JDI_CMD_INVERSION : JDI_CMD_NO_UPDATE));
  SPI.transfer(0x00);
  TOGGLE_VCOM;
  digitalWrite(_ss, LOW);
}