///////////////////////////////////////////////////////////////////////////////
// File spt_sensor.cpp
// Creation date: 2017/09/08
///////////////////////////////////////////////////////////////////////////////

#include "spt_sensor.h"

///////////////////////////////////////////////////////////////////////////////
// Class CSensor
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Public Constructor
//-----------------------------------------------------------------------------
CSensor::CSensor()
{
  Type=CSENSOR_UNKNOWN;
  Reset();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Reset function
//-----------------------------------------------------------------------------
void CSensor::Reset()
{
  Id=-1;
  //MQTT_Client=NULL;
  Enabled=false;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Init function
//-----------------------------------------------------------------------------
void CSensor::Init(int sensorid/*, PubSubClient *mqttclient/*spt_tcpserver *wifiptr*/)
{
  Id=sensorid;
  //MQTT_Client=mqttclient;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Enable function
//-----------------------------------------------------------------------------
void CSensor::Enable()
{
  Enabled=true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Disable function
//-----------------------------------------------------------------------------
void CSensor::Disable()
{
  Enabled=false;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public SetEnabled function
//-----------------------------------------------------------------------------
void CSensor::SetEnabled(boolean enable)
{
  Enabled=enable;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public IsEnabled function
//-----------------------------------------------------------------------------
boolean CSensor::IsEnabled()
{
  return Enabled;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetType function
//-----------------------------------------------------------------------------
int CSensor::GetType()
{
  return Type;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetId function
//-----------------------------------------------------------------------------
int CSensor::GetId()
{
  return Id;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetJSONString function
//-----------------------------------------------------------------------------
String CSensor::GetJSONString()
{
  String str;
  String str1,str2,str3;
  str1="{";
  str2=_addJSONString(str);
  str3="}";
  str=str1+str2+str3;
  return str;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Protected _addJSONString function
//-----------------------------------------------------------------------------
String CSensor::_addJSONString(String str)
{
  //str+=BuildXMLString("Id",Id);
  //str+=BuildXMLString("ST",Type);
  //str+="\"i\":";
  //str+=String(Id);
  //str+=",\"st\":";
  str+="\"st\":";
  str+=String(Type);
  return str;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public MQTTPublishData function
//-----------------------------------------------------------------------------
void CSensor::MQTTPublishData()
{
  str_payload=GetJSONString();
  str_topic = String("C") + String(Id);
  Serial2.println("[" + str_topic + "]" + str_payload);
  /*str_topic=String(MQTT_PublishTopic)+String("/C")+String(Id);
  if (MQTT_Client!=NULL)
  {
    MQTT_Client->publish(str_topic.c_str(),str_payload.c_str());
  }
  */
}
//-----------------------------------------------------------------------------

CAlarm::CAlarm()
{
  Reset();
}

void CAlarm::Reset()
{
  AlarmMinValue=5.0;
  WarningMinValue=25.0;
  WarningMaxValue=50.0;
  AlarmMaxValue=95.0;
}

void CAlarm::Init(float alarm_min, float warning_min, float warning_max, float alarm_max)
{
  AlarmMinValue=alarm_min;
  WarningMinValue=warning_min;
  WarningMaxValue=warning_max;
  AlarmMaxValue=alarm_max;
}

int CAlarm::CheckValue(float value)
{
  if (value<=AlarmMinValue) return CALARM_ALARM_MIN;
  if (value<=WarningMinValue) return CALARM_WARNING_MIN;
  if (value>=AlarmMaxValue) return CALARM_ALARM_MAX;
  if (value<=WarningMaxValue) return CALARM_WARNING_MAX;
  return CALARM_NO_ALARM;
}
