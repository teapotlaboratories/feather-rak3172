#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>

#include "image.h"

/*D1 mini*/
#define EPD_CS D0
#define EPD_DC D8
#define EPD_RST -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)

/*D32 Pro*/
// #define EPD_CS 14
// #define EPD_DC 27
// #define EPD_RST 33  // can set to -1 and share with microcontroller Reset!
// #define EPD_BUSY -1 // can set to -1 to not use a pin (will wait a fixed delay)

LOLIN_UC8151D EPD(212, 104, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

// #define EPD_MOSI D7
// #define EPD_CLK D5
// LOLIN_UC8151D EPD(212,104, EPD_MOSI, EPD_CLK, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //IO

void setup()
{

    EPD.begin();

    EPD.clearBuffer();
    EPD.fillbuffer(gImage_black, gImage_red);
    EPD.display();

    EPD.deepSleep();
}

void loop()
{
}
