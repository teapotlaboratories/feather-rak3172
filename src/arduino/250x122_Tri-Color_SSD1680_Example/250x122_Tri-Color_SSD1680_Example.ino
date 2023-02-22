#include "Adafruit_ThinkInk.h"

#define EPD_CS      PA4
#define EPD_DC      PA0  
#define EPD_RESET   -1 // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY    -1 // can set to -1 to not use a pin (will wait a fixed delay)
#define SRAM_CS     -1 // disable using SRAM chip.
                       // currently RUI3 uses hw pin to drive SPI CS, which conflicts
                       // with the SRAM_CS when SPI transfer is in process.

ThinkInk_213_Tricolor_RW display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

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
