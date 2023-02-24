#include <LOLIN_EPD.h>
#include <Adafruit_GFX.h>
#include "Application.h"

#define EPD_CS    PA4
#define EPD_DC    PA0 
#define EPD_RST   -1  // can set to -1 and share with microcontroller Reset!
#define EPD_BUSY  -1  // can set to -1 to not use a pin (will wait a fixed delay)

LOLIN_SSD1680 display(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI

teapot::Application app;
teapot::SensorData data;
int hour;
int minute;

void setup() {
  
  api.system.restoreDefault();
  Serial.begin(115200);
  Serial.println("    Simple Dashboard   ");
  Serial.println("-----------------------");

  // initialze app
  app.Initialize();
  if( app.ConfigureSensor() != teapot::ReturnCode::kOk )
  {
    Serial.println("failed to configure sensor");
    while(true) delay( 1000 );
  }
  delay( 500 );

  // blink at boot
  app.EnableLed( true );  
  delay(500);  
  app.EnableLed( false );
  
  display.begin();
}

void loop() {
  app.ResetGnssData();
  
  // power-on peripherals
  app.EnablePeripheral( true );
  app.EnableGnss( true );
  
  Serial.println("Fetching Data and Updating Screen");
  if ( app.GetSensorData(data) != teapot::ReturnCode::kOk ) 
  {
    Serial.println("Failed to perform reading BME680");
    /* power-off peripherals */
    app.EnableGnss( false );
    app.EnablePeripheral( false );
  }
  else
  {
    // get time
    teapot::ReturnCode ret = app.ProcessGnssStream(5, 1, 60 * 1000);    
    Serial.printf("process gnss stream done. err: %d\r\n", ret);
    Serial.printf("hdop: %f, sat: %d, lat: %f, long: %f\r\n", 
                  app.GetGnssData().hdop.hdop(), 
                  app.GetGnssData().satellites.value(),
                  app.GetGnssData().location.lat(),
                  app.GetGnssData().location.lng());
                  
    /* power-off peripherals */
    app.EnableGnss( false );
    app.EnablePeripheral( false );
    
    Serial.print("Temperature = ");
    Serial.print(data.temperature);
    Serial.println(" *C");
  
    Serial.print("Humidity = ");
    Serial.print(data.humidity);
    Serial.println(" %");
  
    Serial.print("Battery Voltage = ");
    Serial.print(app.ReadBatteryVoltage());
    Serial.println(" V");

    Serial.print("Current Time = ");
    Serial.print(app.GetGnssData().time.hour());
    Serial.print(":");
    Serial.println(app.GetGnssData().time.minute());

    // convert time to local time
    hour = app.GetGnssData().time.hour();
    int utc_to_local = -8; // utc to GMT-8
    int local_hour = hour + utc_to_local;
    hour = (local_hour < 0) ? 24 + local_hour : local_hour;
    minute = app.GetGnssData().time.minute();
    Serial.print("Current Local Time = ");
    Serial.print(hour);
    Serial.print(":");
    Serial.println(minute);

    /* write frame buffer */
    display.clearBuffer();
    display.setTextSize(2);
    display.setTextColor(EPD_BLACK);
    display.setCursor(3, 0);
    display.print(data.temperature,1);
    display.setTextColor(EPD_RED);
    display.print("C");
  
    display.setTextColor(EPD_BLACK);
    display.setCursor(100, 0);
    display.print(data.humidity,1);
    display.setTextColor(EPD_RED);
    display.print("%");
  
    display.setTextColor(EPD_BLACK);
    display.setCursor(190, 0);
    display.print(app.ReadBatteryVoltage(), 2);
    display.setTextColor(EPD_RED);
    display.print("V");
  
    display.setTextSize(3);
    display.setCursor( ((display.width() - 144)/2) - 20, (display.height() - 24)/2);
    display.setTextColor(EPD_RED);
    display.print("Time ");
    display.setTextColor(EPD_BLACK);
    if(hour < 10)
    {
        display.print("0");
    }
    display.print(hour);
    display.print(":");
    if(minute < 10)
    {
        display.print("0");
    }
    display.print(minute);
    
    
    display.setTextSize(2);
    display.setTextColor(EPD_BLACK);
    display.setCursor(3, display.height() - 20);
    display.print(app.GetGnssData().satellites.value());
    display.setTextColor(EPD_RED);
    display.print("Sat");
  
    display.setTextSize(2);
    display.setTextColor(EPD_BLACK);
    display.setCursor(165, display.height() - 20);
    float hdop = app.GetGnssData().hdop.hdop();
    if( hdop > 99 )
      {
        hdop = 0.00; 
      }
    display.print(hdop, 1);
    display.setTextColor(EPD_RED);
    display.print("HDOP");    
    /* end of write frame buffer */
    
    display.display();
  }

  api.system.sleep.all(5 * 60 * 1000);
}
