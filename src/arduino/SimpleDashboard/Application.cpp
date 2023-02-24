#include "Application.h"
#include <CRC32.h>

/* application implementation */
namespace teapot {

  Sensor operator|(Sensor m, Sensor n){
    return m;
  }
  
  Application::Application(){}
  void Application::Initialize()
  {    
    // setup battery read measure
    analogReadResolution(14);
    pinMode(BATT_MEASURE, INPUT);
    
    // initialize GPS
    EnablePeripheral(true);
    delay( 1000 );
    EnableGnss( false );
    delay( 1000 );
    
    // power-off all peripheral
    EnablePeripheral(false);
    delay( 1000 );
  }

  int Application::ReadBatteryAdc()
  {
    // TODO: investigate. it seems pin always disabled at every loop.
    //       always set to output at every ADC read.
    return analogRead( BATT_MEASURE );
  }

  float Application::ReadBatteryVoltage()
  {
    return ((float) ReadBatteryAdc()) * ADC_TO_BATTERY;
  }

  void Application::ResetGnssData()
  {
    this->l86 = TinyGPSPlus();
  }
  
  ReturnCode Application::EnableGnss( bool enable )
  {
    if( !this->enable_peripheral )
    {
      return ReturnCode::kPeripheralOff;
    }
    
    if( enable )
    {
      // wake gps, incase it's off
//      pinMode(GPS_FORCE_ON, OUTPUT);
//      digitalWrite(GPS_FORCE_ON, HIGH);
    }
    else 
    {
      // open pin to allow GPS to go to sleep (backup mode)
//      pinMode(GPS_FORCE_ON, INPUT);
      
      // prepare command
//      unsigned char backup_mode_command[15];
//      String base_backup_mode_command = ("$PMTK225,4*2F"); 
//      const char tr[] = {0xD, 0xA};
//      base_backup_mode_command.getBytes(backup_mode_command, sizeof(backup_mode_command));
//      memcpy(backup_mode_command+13, tr, 2); 
//
//      // send sleep command to gps
//      Serial1.write(backup_mode_command, sizeof(backup_mode_command));

      // clear incoming uart data
      Serial1.flush();
      while (Serial1.available()) Serial1.read();
    }
    
    return ReturnCode::kOk;
  }
  
  ReturnCode Application::EnableLed( bool enable )
  {
    digitalWrite( BLUE_LED, (enable ? HIGH : LOW) );
    return ReturnCode::kOk;
  }
  
  void Application::EnablePeripheral(bool enable)
  {
    this->enable_peripheral = enable;
    if( enable )
    {  
      // enable GPS serial
      Serial1.begin(9600);
      
      // enable sensor I2C bus
      Wire.begin();
    } 
    else 
    {
      // disable GPS serial
      Serial1.end();
      pinMode(GPS_TXD, INPUT);
      pinMode(GPS_RXD, INPUT);
    
      // disable I2C
      Wire.end();
      pinMode(I2C_SDA, INPUT);
      pinMode(I2C_SCL, INPUT);
    }
  }
  
  void Application::SetupBme68x()
  {  
    // Set up oversampling and filter initialization
    this->bme68x.setTemperatureOversampling(BME680_OS_8X);
    this->bme68x.setHumidityOversampling(BME680_OS_2X);
    this->bme68x.setPressureOversampling(BME680_OS_4X);
    this->bme68x.setIIRFilterSize(BME680_FILTER_SIZE_3);
    this->bme68x.setGasHeater(320, 150); // 320*C for 150 ms
  }
 
  ReturnCode Application::ConfigureSensor()
  {
    
    /* configure BME68x */
    if (!this->bme68x.begin()) {
      return ReturnCode::kBme68xNotFound;
    }
    SetupBme68x();
  
    return ReturnCode::kOk;
  }
  
  ReturnCode Application::GetSensorData( SensorData& data, Sensor sensor_selection )
  {    
    if( !this->enable_peripheral )
    {
      return ReturnCode::kPeripheralOff;
    }
   
    /* Read BME68x sensor */
    if ( !this->bme68x.performReading()) {
      return ReturnCode::kBme68xReadFail;
    }
    data.temperature      = bme68x.temperature;
    data.pressure         = bme68x.pressure;
    data.humidity         = bme68x.humidity;
    data.gas_resistance   = bme68x.gas_resistance;
    
    return ReturnCode::kOk;
  }
  
  ReturnCode Application::ProcessGnssStream(float hdop, uint32_t sat, unsigned long ms)
  {
    unsigned long start = millis();
    do 
    {
      while (Serial1.available()) this->l86.encode(Serial1.read());
      if( l86.hdop.hdop() != 0 && l86.hdop.hdop() <= hdop && l86.hdop.isValid() &&
          l86.satellites.value() != 0 && l86.satellites.value() >= sat && l86.satellites.isValid() )
      {
        return ReturnCode::kOk; 
      }
    } while (millis() - start < ms);
    return ReturnCode::kTimeout;
  }

  TinyGPSPlus& Application::GetGnssData()
  {
    return this->l86; 
  }
  
} // namespace teapot

/* lora payload implementation */
namespace teapot{
namespace payload {
  /* environmental payload */
  EnvironmentalSensorTypeB::EnvironmentalSensorTypeB( uint16_t temperature,
                                                      uint16_t pressure,
                                                      uint16_t humidity )
  {
    // set data
    this->data.header.version = kVersion;
    this->data.header.type = static_cast<uint8_t>(this->type);
    this->data.temperature = temperature;
    this->data.pressure = pressure;
    this->data.humidity = humidity;
  }
  
  size_t EnvironmentalSensorTypeB::GetAsBytes(uint8_t* data, size_t size)
  {
    if( data == nullptr || size < sizeof(this->data) )
    {
      return 0;
    }
    
    memcpy( data, &(this->data), sizeof(this->data) );
    return( sizeof(this->data) );
  }
} // namespace payload 
} // namespace teapot
