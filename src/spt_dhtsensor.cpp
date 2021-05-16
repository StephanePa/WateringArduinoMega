// Class spt_dhtsensor
#include "spt_dhtsensor.h"
//#include "spt_xml.h"

spt_dhtsensor::spt_dhtsensor() : CSensor()
{
  Reset();
  Type=CSENSOR_DHT;
}
spt_dhtsensor::~spt_dhtsensor()
{
  if (dht_sensor!=NULL) delete dht_sensor;
}
void spt_dhtsensor::Reset()
{
  CSensor::Reset();
  TemperatureValue=-999.9;
  RelativeHumidityValue=-999.9;
  SensorInputPin=53;
  SensorType=DHT11SensorType;
  dht_sensor=NULL;
}
void spt_dhtsensor::Init(spt_dhtsensor_dataconfig dataconfig)
{
  CSensor::Init(dataconfig.Id);
  SensorInputPin=dataconfig.Pin;
  SensorType=dataconfig.Type;
  if (dht_sensor!=NULL) delete dht_sensor;
  dht_sensor=new DHT(SensorInputPin,SensorType);
}
void spt_dhtsensor::Init(int sensorid, int digitalinputpin, int sensortype/*, PubSubClient *mqttclient*/)
{
  CSensor::Init(sensorid/*,mqttclient*/);
  SensorInputPin=digitalinputpin;
  SensorType=sensortype;
  if (dht_sensor!=NULL) delete dht_sensor;
  dht_sensor=new DHT(SensorInputPin,sensortype);
}

boolean spt_dhtsensor::ReadData(float *temperature, float *humidity, bool senddata)
{
  boolean ok;
  ok=false;
  if (dht_sensor!=NULL)
  {
    ok=dht_sensor->Read(temperature,humidity);
    if (ok)
    {
      TemperatureValue=*temperature;
      RelativeHumidityValue=*humidity;
    }
    else
    {
      TemperatureValue=-999.9;
      RelativeHumidityValue=-999.9;
    }
    if (senddata) MQTTPublishData()/*SendDataToNetwork()*/;
    return (ok);
  }
  return false;
}

//-----------------------------------------------------------------------------
// Public GetXMLString function
//-----------------------------------------------------------------------------
/*
String spt_dhtsensor::GetXMLString()
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
String spt_dhtsensor::_addJSONString(String str)
{
#ifdef _SERIAL_VERSION_
//Serial.println("spt_dhtsensor::_addJSONString()");
//Serial.println(" > str(avant) : "+str);
#endif
  //str+=CSensor::_addXMLString(str);
  str+=CSensor::_addJSONString(str);
  //str+=BuildXMLString("SST",SensorType);
  //str+=BuildXMLString("Te",TemperatureValue);
  //str+=BuildXMLString("Hu",RelativeHumidityValue);
  str+=",\"sst\":";
  str+=String(SensorType);
  str+=",\"t\":";
  str+=String(TemperatureValue);
  str+=",\"h\":";
  str+=String(RelativeHumidityValue);
#ifdef _SERIAL_VERSION_
//Serial.println(" > str(apres) : "+str);
#endif
  return str;
}
//-----------------------------------------------------------------------------
