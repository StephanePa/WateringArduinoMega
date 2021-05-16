#ifndef SPT_DEFINITION_H
#define SPT_DEFINITION_H
#include <SPI.h>

/////////////////////////////////////////////////////////////////////////////////
// Released version
//  ->_SERIAL_Version=false
// Debug version (connected to a computer by using Serial via USB)
//  ->_SERIAL_Version=true
//-------------------------------------------------------------------------------
#define _SERIAL_VERSION_
//#define _SERIAL_Version_ true
//#define _SERIAL_Version_ false

/////////////////////////////////////////////////////////////////////////////////
/// JSON Version
/////////////////////////////////////////////////////////////////////////////////
#define JSONVERSION6

/////////////////////////////////////////////////////////////////////////////////
/// Debug functions
/////////////////////////////////////////////////////////////////////////////////
//void Serial_print(String a) { if (_SERIAL_Version) Serial.print(a); }
//void Serial_println(String a) { if (_SERIAL_Version) Serial.println(a); }
//void Serial_print(int a) { if (_SERIAL_Version) Serial.print(a); }
//void Serial_println(int a) { if (_SERIAL_Version) Serial.println(a); }
/////////////////////////////////////////////////////////////////////////////////

// When using Qt compiler:
//#define __AVR_ATmega2560__
//#define ARDUINO 100
//#define F_CPU 16000000L
/////////////////////////////////////////////////////////////////////////////////

#define VERSION_HIGH 1
#define VERSION_LOW 1

#define MQTTSerial Serial2

// Wifi parameters
#define SSID        "InternalNetwork1"
#define PASSWORD    "Gollum628and314"
// MQTT parameters
#define MQTT_a1 192
#define MQTT_a2 168
#define MQTT_a3 0
#define MQTT_a4 5
#define MQTT_SubscribeTopic "cmdA1"
#define MQTT_PublishTopic "teleA1"

// Parameter filename
#define ParameterFilename1 "A1Param001.prn"

// watering Pot number
#define POT_NUMBER_MIN 1
#define POT_NUMBER_MAX 5

// Soil humidity sensors
#define SoilHumiditySensor_1_AnalogInputPin A0
#define SoilHumiditySensor_2_AnalogInputPin A1
#define SoilHumiditySensor_3_AnalogInputPin A2
#define SoilHumiditySensor_4_AnalogInputPin A3
#define SoilHumiditySensor_5_AnalogInputPin A4
#define SoilHumiditySensor_1_Id 101
#define SoilHumiditySensor_2_Id 102
#define SoilHumiditySensor_3_Id 103
#define SoilHumiditySensor_4_Id 104
#define SoilHumiditySensor_5_Id 105
// light sensor
#define LightSensor_1_AnalogInputPin A5
#define LightSensor_1_Id 321
// OneWire temperature sensor pin
//#define OneWire_DigitalInputPin 50
#define OneWire_DigitalInputPin 35
#define SoilTemperatureSensor_1_Id 201
#define SoilTemperatureSensor_2_Id 202
#define SoilTemperatureSensor_3_Id 203
#define SoilTemperatureSensor_4_Id 204
#define SoilTemperatureSensor_5_Id 205
// DTH sensors (Temperature and relative humidity)
//#define DTH11_internal_DigitalInputPin 53 // inside the electrical box
#define DTH11_internal_DigitalInputPin 38
//#define DTH22_1_external_DigitalInputPin 52 // inside the greenhouse
#define DTH22_1_external_DigitalInputPin 37
//#define DTH22_2_external_DigitalInputPin 51 // outside the greenhouse
#define DTH22_2_external_DigitalInputPin 36
#define AirTemperatureRelativeHumiditySensor_1_Id 111
#define AirTemperatureRelativeHumiditySensor_2_Id 112
#define AirTemperatureRelativeHumiditySensor_3_Id 113
// Sensor power supply (Soil temperature and relative humidity)
#define Sensor_PowerSupplyOutputPin 47
#define SensorPowerSupply_Id 3101
// Relais commands
#define WaterPump_1_PowerSupplyOutputPin 46 // Pompe 1
#define WaterPump_1_Id 1011
#define SolenoidValve1_PowerSupplyOutputPin 45
#define SolenoidValve2_PowerSupplyOutputPin 44
#define SolenoidValve3_PowerSupplyOutputPin 43
#define SolenoidValve4_PowerSupplyOutputPin 42
#define SolenoidValve5_PowerSupplyOutputPin 41
#define SolenoidValve_1_Id 2001
#define SolenoidValve_2_Id 2002
#define SolenoidValve_3_Id 2003
#define SolenoidValve_4_Id 2004
#define SolenoidValve_5_Id 2005
// Spare
#define PS12V_PowerSupplyOutputPin 40
#define PS12V_Id 3001
// pushbutton
#define WateringCyclePushButtonPin 26
#define ManualPumpPushButtonPin 27
#define WateringFlowerPot1PushButtonPin 29
#define WateringFlowerPot2PushButtonPin 30
#define WateringFlowerPot3PushButtonPin 31
#define WateringFlowerPot4PushButtonPin 32
#define WateringFlowerPot5PushButtonPin 33
#define BusyLedPin 28
// SD Card UNO
//#define SD_MOSI_Pin 11
//#define SD_MISO_Pin 12
//#define SD_CLK_Pin 13
//#define SD_SS_CS_Pin 4
// SD Card MEGA
#define SD_MOSI_Pin 51
#define SD_MISO_Pin 50
#define SD_CLK_Pin 52
#define SD_SS_CS_Pin 53

/*
ID Allocation

101 SoilHumiditySensor_1_Id 101
102 SoilHumiditySensor_2_Id 102
103 SoilHumiditySensor_3_Id 103
104 SoilHumiditySensor_4_Id 104
105 SoilHumiditySensor_5_Id 105

111 AirTemperatureRelativeHumiditySensor_1_Id 111
112 AirTemperatureRelativeHumiditySensor_2_Id 112
113 AirTemperatureRelativeHumiditySensor_3_Id 113

201 SoilTemperatureSensor_1_Id 201
202 SoilTemperatureSensor_2_Id 202
203 SoilTemperatureSensor_3_Id 203
204 SoilTemperatureSensor_4_Id 204
205 SoilTemperatureSensor_5_Id 205

321 LightSensor_1_Id 321

1011 WaterPump_1_Id 1011

2001 SolenoidValve_1_Id 2001
2002 SolenoidValve_2_Id 2002
2003 SolenoidValve_3_Id 2003
2004 SolenoidValve_4_Id 2004
2005 SolenoidValve_5_Id 2005

3001 PS12V_Id 3001

3101 SensorPowerSupply_Id 3101

// Pin allocation

A0 SoilHumiditySensor_1_AnalogInputPin A0
A1 SoilHumiditySensor_2_AnalogInputPin A1
A2 SoilHumiditySensor_3_AnalogInputPin A2
A3 SoilHumiditySensor_4_AnalogInputPin A3
A4 SoilHumiditySensor_5_AnalogInputPin A4
A5 LightSensor_1_AnalogInputPin A5

20 PIN_WIRE_SDA use with Tiny RTC module
21 PIN_WIRE_SCL use with Tiny RTC module


26 WateringCyclePushButtonPin 26
27 ManualPumpPushButtonPin 27
28 BusyLedPin 28
29 WateringFlowerPot1PushButtonPin 29

30 WateringFlowerPot2PushButtonPin 30
31 WateringFlowerPot3PushButtonPin 31
32 WateringFlowerPot4PushButtonPin 32
33 WateringFlowerPot5PushButtonPin 33

35 OneWire_DigitalInputPin 50
36 DTH22_2_external_DigitalInputPin 51
37 DTH22_1_external_DigitalInputPin 52
38 DTH11_internal_DigitalInputPin 53

40 PS12V_PowerSupplyOutputPin 40
41 SolenoidValve5_PowerSupplyOutputPin 41
42 SolenoidValve4_PowerSupplyOutputPin 42
43 SolenoidValve3_PowerSupplyOutputPin 43
44 SolenoidValve2_PowerSupplyOutputPin 44
45 SolenoidValve1_PowerSupplyOutputPin 45
46 Pompe1_PowerSupplyOutputPin 46 // Pompe 1
47 Sensor_PowerSupplyOutputPin 47

50 SD_MISO_Pin 50
51 SD_MOSI_Pin 51
52 SD_CLK_Pin 52
53 SD_SS_CS_Pin 53
*/
#endif // SPT_DEFINITION_H
