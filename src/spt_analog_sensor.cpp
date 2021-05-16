///////////////////////////////////////////////////////////////////////////////
// File spt_analog_sensor.cpp
// Creation date: 2017/09/08
///////////////////////////////////////////////////////////////////////////////

#include "spt_analog_sensor.h"

///////////////////////////////////////////////////////////////////////////////
// Class CAnalogSensor
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Public Constructor
//-----------------------------------------------------------------------------
CAnalogSensor::CAnalogSensor() : CSensor()
{
  Reset();
  Type=CSENSOR_ANALOG;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Reset function
//-----------------------------------------------------------------------------
void CAnalogSensor::Reset()
{
  CSensor::Reset();
  //SensorId=-1;
  Value=-999.9;
  AnalogInputPin=A0;
  //wifiPtr=NULL;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Reset function
//-----------------------------------------------------------------------------
void CAnalogSensor::Init(int sensorid, int analoginputpin/*, PubSubClient *mqttclient*/)
{
  CSensor::Init(sensorid/*, mqttclient*/);
  //SensorId=sensorid;
  AnalogInputPin=analoginputpin;
  pinMode(AnalogInputPin, INPUT);
  //wifiPtr=wifiptr;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public ReadData function
//-----------------------------------------------------------------------------
float CAnalogSensor::ReadData(bool senddata)
{
  Value=(float)analogRead(AnalogInputPin);
  //Value=(1024.0-Value)/1024.0;
  Value=ConvertData(Value);
  if (senddata) MQTTPublishData();
  return Value;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public ConvertData function
//-----------------------------------------------------------------------------
float CAnalogSensor::ConvertData(float data)
{
  return data;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetXMLString function
//-----------------------------------------------------------------------------
/*String CAnalogSensor::GetXMLString()
{
  String str;
  str=CSensor::GetXMLString();
  str=_addXMLString(str);
  return str;
}
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Protected _addJSONString function
//-----------------------------------------------------------------------------
String CAnalogSensor::_addJSONString(String str)
{
  str += CSensor::_addJSONString(str);
  str += F(",\"v\":");
  str += String(Value);
  return str;
}
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class CSoilMoistureSensor
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Public Constructor
//-----------------------------------------------------------------------------
CSoilMoistureSensor::CSoilMoistureSensor() : CAnalogSensor()
{
  Reset();
  Type=CSENSOR_ANALOG_SOILMOISTURE;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public ConvertData function
//-----------------------------------------------------------------------------
float CSoilMoistureSensor::ConvertData(float data)
{
  return ((1024.0-data)/1024.0);
}
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class CLightSensor
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Public Constructor
//-----------------------------------------------------------------------------
CLightSensor::CLightSensor() : CAnalogSensor()
{
  Reset();
  Type=CSENSOR_ANALOG_LIGHT;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public ConvertData function
//-----------------------------------------------------------------------------
float CLightSensor::ConvertData(float data)
{
  return ((data-1024.0)/1024.0);
}
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////