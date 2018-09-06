#include <LCD_JDI_176.h>

#define SS                      4
#define LCD_DISP_WIDTH          176
#define LCD_DISP_HEIGHT         176

const uint8_t color[8] = {JDI_BLUE, JDI_CYAN, JDI_BLACK, JDI_GREEN, JDI_MAGENTA, JDI_WHITE, JDI_RED, JDI_YELLOW};

LCD_JDI display(SS);

uint8_t move    = 0;
uint8_t block   = LCD_DISP_HEIGHT / 8;
uint8_t counter = 0;

void setup(void)
{
  display.begin();
}

void loop(void)
{
  ++counter;

  drawEightColor();

  display.fillScreen(JDI_WHITE);
  display.refresh();

  drawRainMan();

  display.fillScreen(JDI_WHITE);
  display.refresh();

  drawText("Thank You", "Adafruit!", 3);

  display.fillScreen(JDI_WHITE);
  display.refresh();

  if(counter%2){
    display.invertDisplay(true);
  }
  else{
    display.invertDisplay(false);
    counter = 0;
  }
}

void drawText(char *text1, char *text2, uint8_t textSize){
  for(int i =0; i < 8; ++i){
    if(color[i]==JDI_WHITE){
      continue;
    }
    display.setTextColor(color[i]);
    display.setCursor(5,55);
    display.setTextSize(textSize);
    display.print(text1);
    display.setCursor(8,90);
    display.setTextSize(3);
    display.print(text2);
    display.refresh();
    delay(400);
  }
}

void drawEightColor(){
  for(int i = 0; i < 8; ++i){
    display.fillRect(0, block*i, LCD_DISP_WIDTH, block, color[i]);
    display.refresh();
    delay(200);
  }
  delay(600);
  for(int i = 8; i > 0; --i){
    display.fillRect(0, block*i, LCD_DISP_WIDTH, block, JDI_WHITE);
    display.refresh();
    delay(200);
  }
}

void drawRainMan(){
  for(int i = 0; i < 16; ++i){
    move = 10*i;
    for(int x =0; x < LCD_DISP_HEIGHT; x+=LCD_DISP_HEIGHT/8){
      for(int y =0; y < LCD_DISP_WIDTH; y+=20){
        if(i%2){
          display.fillCircle(y, x, 1, JDI_BLACK);
        }
        else{
          display.fillCircle(y + 10, x + 10, 1, JDI_BLACK);
        }
      }
    }
    display.fillCircle(LCD_DISP_WIDTH/8 + 12 + move, 5*LCD_DISP_HEIGHT/8 - 37, LCD_DISP_HEIGHT/6, JDI_BLACK);
    display.fillCircle(LCD_DISP_WIDTH/8 + 12 + move, 5*LCD_DISP_HEIGHT/8 - 22, LCD_DISP_HEIGHT/6, JDI_WHITE);
    display.fillCircle(LCD_DISP_WIDTH/8 + move, LCD_DISP_HEIGHT/2, LCD_DISP_HEIGHT/16, JDI_BLACK);
    display.fillRect(LCD_DISP_WIDTH/8 - 2 + move, LCD_DISP_HEIGHT/2, 5, 60, JDI_BLACK);
    display.fillRect(LCD_DISP_WIDTH/8 + 5 + move, LCD_DISP_HEIGHT/2 + 20 , 30, 80, JDI_WHITE);
    display.fillRect(LCD_DISP_WIDTH/8 - 20 + move, LCD_DISP_HEIGHT/2 + 20 , 10, 80, JDI_WHITE);

    display.drawLine(LCD_DISP_WIDTH/8 - 2 + move, 10*LCD_DISP_HEIGHT/16, LCD_DISP_WIDTH/8 + 6 + move, 5*LCD_DISP_HEIGHT/8 + 10, JDI_BLACK);
    display.drawLine(LCD_DISP_WIDTH/8 + 6 + move, 5*LCD_DISP_HEIGHT/8 + 10, LCD_DISP_WIDTH/8 + 15 + move, 10*LCD_DISP_HEIGHT/16, JDI_BLACK);
    display.drawLine(LCD_DISP_WIDTH/8 + 15 + move, 10*LCD_DISP_HEIGHT/16, LCD_DISP_WIDTH/8 + 15 + move, 5*LCD_DISP_HEIGHT/8 - 50, JDI_BLACK);

    if(i%2){
      display.drawLine(LCD_DISP_WIDTH/8 + move, 13*LCD_DISP_HEIGHT/16, LCD_DISP_WIDTH/8 - 15 + move, 5*LCD_DISP_HEIGHT/8 + 60, JDI_BLACK);
      display.drawLine(LCD_DISP_WIDTH/8 + move, 13*LCD_DISP_HEIGHT/16, LCD_DISP_WIDTH/8 + 15 + move, 5*LCD_DISP_HEIGHT/8 + 60, JDI_BLACK);
    }
    else{
      display.drawLine(LCD_DISP_WIDTH/8 + move, 13*LCD_DISP_HEIGHT/16, LCD_DISP_WIDTH/8 + move, 5*LCD_DISP_HEIGHT/8 + 60, JDI_BLACK);
    }
    display.refresh();

    delay(300);
    display.fillScreen(JDI_WHITE);
    display.refresh();
  }
}