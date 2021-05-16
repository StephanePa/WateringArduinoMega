#ifndef SPT_ONEWIRE_SENSOR_H
#define SPT_ONEWIRE_SENSOR_H
// Class CAnalogSensor
#include "spt_sensor.h"
#include "spt_OneWire.h"
// OneWire DS18S20 Temperature Sensors
//
struct OneWire_DS18S20_Sensor_DataConfig
{
  int Id;
  byte Addr[8];
  boolean enable;
};

class OneWire_DS18S20_Sensor : public CSensor
{
  public:
    OneWire_DS18S20_Sensor();
    void Reset();
    //void Init(char str_addr[16], int sensorid, OneWire *onewireptr/*, spt_tcpserver *wifiptr*/);
    void Init(byte addr[8], int sensorid, OneWire *onewireptr/*, spt_tcpserver *wifiptr=NULL*/);
    //void SetAddress(byte addr[8], int sensorid, OneWire *onewireptr, spt_tcpserver *wifiptr=NULL);
    void startTemperatureMeasure();
    float Read(bool senddata=false);
    // get data in xml formatted format
    //virtual String GetXMLString();
  protected:
    // get data in xml formatted format
    //virtual String _addXMLString(String str);
    // Sensor address
    byte Address[8];
    //int SensorId;
    float Value;
    //spt_tcpserver *wifiPtr;
    OneWire *OneWirePtr;
    float readTemperatureMeasure();
    virtual String _addJSONString(String str);
};
#endif // SPT_ONEWIRE_SENSOR_H

