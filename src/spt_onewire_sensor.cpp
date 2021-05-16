#include "spt_onewire_sensor.h"
#include "spt_utils.h"

OneWire_DS18S20_Sensor::OneWire_DS18S20_Sensor() : CSensor()
{
  Reset();
  Type=CSENSOR_DS18S20;
}
void OneWire_DS18S20_Sensor::Reset()
{
  int i;
  for(i=0;i<8;i++) Address[i]=0x00;
  CSensor::Reset();
}
void OneWire_DS18S20_Sensor::Init(byte addr[8], int sensorid, OneWire *onewireptr/*, spt_tcpserver *wifiptr*/)
{
  CSensor::Init(sensorid/*,wifiptr*/);
  Address[0]=addr[0];
  Address[1]=addr[1];
  Address[2]=addr[2];
  Address[3]=addr[3];
  Address[4]=addr[4];
  Address[5]=addr[5];
  Address[6]=addr[6];
  Address[7]=addr[7];
  //SensorId=sensorid;
  //wifiPtr=wifiptr;
  OneWirePtr=onewireptr;
}

void OneWire_DS18S20_Sensor::startTemperatureMeasure()
{
  // addr[] : Adresse du module 1-Wire détecté
  /* Reset le bus 1-Wire et sélectionne le capteur */
  OneWirePtr->reset();
  OneWirePtr->select(Address);

  /* Lance une prise de mesure de température et attend la fin de la mesure */
  OneWirePtr->write(0x44, 1);
  delay(1000);
}
float OneWire_DS18S20_Sensor::Read(bool senddata)
{
  Value=readTemperatureMeasure();
  if (senddata) MQTTPublishData()/*SendDataToNetwork()*/;
  return Value;
}
float OneWire_DS18S20_Sensor::readTemperatureMeasure()
{
  byte data[9];
  // data[] : Données lues depuis le scratchpad
  // addr[] : Adresse du module 1-Wire détecté

  /* Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad */
  OneWirePtr->reset();
  OneWirePtr->select(Address);
  OneWirePtr->write(0xBE);

  /* Lecture du scratchpad */
  for (byte i = 0; i < 9; i++)
  {
    data[i] = OneWirePtr->read();
  }
  /* Calcul de la température en degré Celsius */
  return ((data[1] << 8) | data[0]) * 0.0625;
}
String OneWire_DS18S20_Sensor::_addJSONString(String str)
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_dhtsensor::_addJSONString()");
Serial.println(" > str(avant) : "+str);
#endif
  str+=CSensor::_addJSONString(str);
  str+=",\"t\":";
  str+=String(Value);
#ifdef _SERIAL_VERSION_
Serial.println(" > str(apres) : "+str);
#endif
  return str;
}

//-----------------------------------------------------------------------------
// Public GetXMLString function
//-----------------------------------------------------------------------------
/*String OneWire_DS18S20_Sensor::GetXMLString()
{
  String str;
  str=CSensor::GetXMLString();
  str=_addXMLString(str);
  return str;
}
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Protected _addXMLString function
//-----------------------------------------------------------------------------
/*String OneWire_DS18S20_Sensor::_addXMLString(String str)
{
  str+=CSensor::_addXMLString(str);
  str+=BuildXMLString("V",Value);
  return str;
}*/
//-----------------------------------------------------------------------------

