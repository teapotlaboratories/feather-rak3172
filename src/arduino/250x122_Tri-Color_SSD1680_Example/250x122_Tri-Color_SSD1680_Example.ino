#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>

#define EPD_CS    PA4
#define EPD_DC    PA0 
#define EPD_RST   -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY  -1  // can set to -1 to not use a pin (will wait a fixed delay)

LOLIN_SSD1680 display(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

void setup() {
  Serial.println(" EPD Display Demo ");
  Serial.println("------------------");
  api.system.restoreDefault();
  display.begin();
  
  display.clearBuffer();
  display.setTextSize(3);
  display.setCursor( ((display.width() - 144)/2) - 15, (display.height() - 24)/2);
  display.setTextColor(EPD_BLACK);
  display.print("Teapot");  
  display.setTextColor(EPD_RED);
  display.print("Labs");
  display.display();

}

void loop() {
  //don't do anything!
}
