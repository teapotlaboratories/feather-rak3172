#ifndef TEAPOT_APPLICATION_H
#define TEAPOT_APPLICATION_H

#include "Arduino.h"
#include "Adafruit_BME680.h"
#include "TinyGPSPlus.h"

// configuration for teapot bwlr3d application
#include "Configuration.h"

/* pin definition */
#define BLUE_LED      PA8
//#define GPS_ENABLE            nullptr
//#define GPS_RESET            nullptr
#define BATT_MEASURE  PA15
#define GPS_TXD       PB7
#define GPS_RXD       PB6
#define I2C_SDA       PA11
#define I2C_SCL       PA12

#ifndef ADC_TO_BATTERY
  #error "ADC_TO_BATTERY not set"
#endif

/* application definition */
namespace teapot{
  enum class ReturnCode {
    kOk = 0,
    kError,
    kBme68xNotFound,
    kBme68xReadFail,
    kPeripheralOff,
    kTimeout,
  };
  
  enum class Sensor {
    kNone     = 0b0,
    kAll      = 0b1111,
    kBme68x   = 0b1,
  };
 
  struct SensorData {
    // Temperature (Celsius)
    float temperature;
    // Pressure (hPascals)
    uint32_t pressure;
    // Humidity (RH %)
    float humidity;
    // Gas resistor (ohms)
    uint32_t gas_resistance;
  };

  class Application {
    private:
      Adafruit_BME680   bme68x;
      TinyGPSPlus       l86;
      bool              enable_peripheral;
      
      void  SetupBme68x();
    public:
      Application();
      void          Initialize();
      ReturnCode    ConfigureSensor();
      void          EnablePeripheral( bool enable );
      ReturnCode    EnableLed( bool enable );
      ReturnCode    EnableGnss( bool enable );
      int           ReadBatteryAdc();
      float         ReadBatteryVoltage();
      ReturnCode    GetSensorData( SensorData& data, Sensor sensor_selection = Sensor::kAll );
      void          ResetGnssData();
      ReturnCode    ProcessGnssStream(float hdop, uint32_t sat, unsigned long ms);
      TinyGPSPlus&  GetGnssData();
  };
  
} // namespace teapot


/* lora payload definition */
namespace teapot{
namespace payload {
  /* Payload Component Definition */
  const uint32_t kVersion = 0x01;
  enum class Type {
    kEnvironmentalSensorTypeB = 0x05
  };
  
  struct Header {
    uint8_t version;
    uint8_t type;
  } __attribute__((packed));

  /* Payload Definition */  
  /* environmental payload */
  class EnvironmentalSensorTypeB {
    struct Frame {
      Header header;
      uint16_t temperature;  // Celsius
      uint16_t humidity; // RH %
      uint16_t pressure;  // Pascals
    } __attribute__((packed));
    
    const Type type = teapot::payload::Type::kEnvironmentalSensorTypeB;
    Frame data;
    public:
      EnvironmentalSensorTypeB( 
        uint16_t temperature,
        uint16_t humidity,
        uint16_t pressure
      );
      size_t GetAsBytes(uint8_t* data, size_t size);
  };

} // namespace payload 
} // namespace teapot

#endif // TEAPOT_APPLICATION_H
