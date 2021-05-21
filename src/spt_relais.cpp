///////////////////////////////////////////////////////////////////////////////
// File spt_relais.cpp
// Creation date: 2017/09/08
///////////////////////////////////////////////////////////////////////////////

#include "spt_relais.h"

///////////////////////////////////////////////////////////////////////////////
// Class CPowerSupply
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------
// Public Constructor
//-----------------------------------------------------------------------------
CPowerSupply::CPowerSupply()
{
  Reset();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Reset function
//-----------------------------------------------------------------------------
void CPowerSupply::Reset()
{
  // set default arduino pin number
    OutputPin=PS12V_PowerSupplyOutputPin;
  // set default State to Off
    State=PowerOff;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Init function
//-----------------------------------------------------------------------------
void CPowerSupply::Init(CPowerSupply_DataConfig dataconfig, int OnOff = PowerOff)
{
  Id=dataconfig.Id;
  OutputPin=dataconfig.Pin;
  pinMode(OutputPin,OUTPUT);
  digitalWrite(OutputPin, OnOff);
  State=OnOff;
}
void CPowerSupply::Init(int id, int outputPin, int OnOff/*, PubSubClient *mqttclient/*, spt_tcpserver *wifiptr*/)
{
  Id=id;
  OutputPin=outputPin;
  pinMode(OutputPin,OUTPUT);
  digitalWrite(OutputPin, OnOff);
  State=OnOff;
  //wifiPtr=wifiptr;
  //MQTT_Client = mqttclient;

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public On function
//-----------------------------------------------------------------------------
void CPowerSupply::On(bool senddata)
{
  String str;
  if (State!=PowerOn)
  {
    digitalWrite(OutputPin, PowerOn);
    State=PowerOn;
    if (senddata) SendDataToNetwork();
  }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Off function
//-----------------------------------------------------------------------------
void CPowerSupply::Off(bool senddata)
{
  String str;
  if (State!=PowerOff)
  {
    digitalWrite(OutputPin, PowerOff);
    State=PowerOff;
    if (senddata) SendDataToNetwork();
  }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public SendDataToNetwork function
//-----------------------------------------------------------------------------
void CPowerSupply::SendDataToNetwork()
{
  // send to TCP clients
  str_topic = String("PS") + String(Id);
  if (State == PowerOn) str_payload = "on"; else str_payload = "off";
  MQTTSerial.print("[" + str_topic + "]" + str_payload);
    /*
  if (MQTT_Client != NULL)
  {
    str_topic = String(MQTT_PublishTopic) + String("/PS") + String(Id);
    if (State == PowerOn) str_payload = "on"; else str_payload = "off";
	  MQTT_Client->publish(str_topic.c_str(), str_payload.c_str());
  }
  */
}
//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
