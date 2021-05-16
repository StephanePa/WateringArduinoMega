#ifndef SPT_DATA_H
#define SPT_DATA_H
// Class spt_data
#include "spt_definition.h"
#include <arduino.h>
#include "spt_analog_sensor.h"
#include "spt_onewire_sensor.h"
#include "spt_relais.h"
#include "spt_timer.h"
//#include "spt_tcpserver.h"
#include "spt_dhtsensor.h"
#include <spt_OneWire.h>
#include <SD.h>

struct PushButton_DataConfig
{
  int Pin;
  int enable;
  int timer; // in second
};

struct Led_DataConfig
{
  int Pin;
};

struct OneWire_DataConfig
{
  int Pin;
};

struct TinyRTC_Module_DataConfig
{
  int PinWire_SDA;
  int PinWire_SCL;
};

struct File_DataConfig
{
  File_DataConfig();
  CPowerSupply_DataConfig WaterPump1_PowerSupply;
  CPowerSupply_DataConfig PS12V_PowerSupply;
  CPowerSupply_DataConfig Sensor_PowerSupply;
  CPowerSupply_DataConfig SolenoidValve[5];
  TinyRTC_Module_DataConfig TinyRTC;
  PushButton_DataConfig WateringCyclePushButton;
  PushButton_DataConfig ManualPumpPushButton;
  Led_DataConfig BusyLed;
  PushButton_DataConfig WateringFlowerPotPushButton[5];
  OneWire_DataConfig One_Wire;
  spt_dhtsensor_dataconfig DHT_Sensors[3];
  OneWire_DS18S20_Sensor_DataConfig DS18S20[5];
  int SensorTimerValue;
  int SoilSensorTimerValue;
  void _loadConfigFile(File& OrigFile);
  void _saveConfigFile(File& DestFile);
  void _copyConfigFile();
  char buffer[200];
  char *buf;
  char key[100];
};

class spt_data
{
  public:
    spt_data();
    ~spt_data();
    void Reset();
    void Init();
    CSensor* FindSensorById(int id);
    //OneWire  ds(OneWire_DigitalInputPin);  // a 4.7K resistor is necessary between +5V and the pin
    OneWire *ds;
// pointer to all sensor
    CSensor* Sensors[14]; // 5+5+3+1
// Power supply (digital output)
  // Pump power supply (12VDC)
    CPowerSupply Pump_PowerSupply;
  // array of solenoid valve powerSupply (12VDC)
    CPowerSupply SolenoidValve_PowerSupply[5];
  // Soil Sensor power supply (5VDC)
    CPowerSupply Sensor_PowerSupply;
	void LoadConfiguration();
	void SaveConfiguration();

// Soil Sensors
  // array of OneWire DS18S20 sensor (soil sensor)
    OneWire_DS18S20_Sensor DS18S20_Sensors[5];
  // array of analog humidity rate sensor (soil sensor)
    CSoilMoistureSensor RelativeHumidityRate[5];
  // Alarm regarding the soil relative humidity rate
    //CAlarm Alarm_RelativeHumidityRate[5];
    spt_timer SoilSensorTimer; // accessible from external TCP Client
    unsigned int SoilSensorTimerValue; // in second

// Light Sensors
  // analog lightness sensor
    CLightSensor LightSensor;

  //---------------------------------------------------------------------------
  // DHT Sensors
    // array of DHT Sensor
      spt_dhtsensor DHTSensors[3];
    // Sensor measurement timer
      spt_timer SensorTimer;
      unsigned int SensorTimerValue; // in second ### dupplication data ### already exits inside SensorTimer
	  //CAlarm GreenHouseRelativeHumidityAlarm;
	  //CAlarm GreenHouseTemperatureAlarm;
	  //CAlarm ElectricityBoxRelativeHumidityAlarm;
	  //CAlarm ElectricityBoxTemperatureAlarm;
  //---------------------------------------------------------------------------
  // Flower pot watering data
	// timers
      spt_timer FlowerPotWateringTimer[5];
	// enabling status
      boolean FlowerPotWateringEnable[5];
	// Timer values
      unsigned int FlowerPotWateringTimerValue[5]; // in second ### dupplication data ### already exits inside spt_timer FlowerPotWateringTimer
  //---------------------------------------------------------------------------
  // Manual pump timer
    // timer
	  spt_timer ManualPumpTimer; // accessible from external TCP Client
	// timer value
	  unsigned int ManualPumpTimerValue; // in second
  // Alarm and Warning definition
    //CAlarm SoilRelativeHumidityAlarm;
    //CAlarm SoilTemperatureAlarm;
  // Date Time module
    //spt_ds1307 DateTimeMod;
  protected:
    //spt_tcpserver *wifiPtr;
    //PubSubClient *MQTT_Client;
    char ConfigFilename[30];
    char ConfigBackupFilename[30];
    void _loadConfigFile();
    void _saveConfigFile();
    void _copyConfigFile();
    File_DataConfig Config;
  char buffer[200];
  char *buf;
  char key[100];
};
#endif // SPT_DATA_H
