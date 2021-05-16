///////////////////////////////////////////////////////////////////////////////
// File spt_relais.h
// Creation date: 2017/09/08
///////////////////////////////////////////////////////////////////////////////

#ifndef SPT_RELAIS_H
#define SPT_RELAIS_H
#include "spt_definition.h"
#include <arduino.h>
//#include "spt_tcpserver.h"
//#include <PubSubClient.h>

///////////////////////////////////////////////////////////////////////////////
// Power on/off definition
///////////////////////////////////////////////////////////////////////////////
#define PowerOn LOW
#define PowerOff HIGH
///////////////////////////////////////////////////////////////////////////////

struct CPowerSupply_DataConfig
{
  int Id;
  int Pin;
};
///////////////////////////////////////////////////////////////////////////////
// Class CPowerSupply
///////////////////////////////////////////////////////////////////////////////
class CPowerSupply
{
  public:
    // Constructor
      CPowerSupply();
    // Reset class function
      void Reset();
    // Init class function
	  void Init(CPowerSupply_DataConfig dataconig, int OnOff = PowerOff);
    void Init(int id, int outputPin, int OnOff = PowerOff);
    // On & Off function
      void On(bool senddata=true);
      void Off(bool senddata=true);
  protected:
    // Format and send on/off feedback function to TCP/IP client(s)
      void SendDataToNetwork();
    // pointer to the arduino TCP/IP server
      //spt_tcpserver *wifiPtr;
	  //PubSubClient *MQTT_Client;
	  // Arduino output pin
      int OutputPin;
    // Power Supply State (PowerOn or PowerOff state)
      int State;
    // PowerSupply Id
      int Id;
      static String str_payload,str_topic;
};
///////////////////////////////////////////////////////////////////////////////

#endif // SPT_RELAIS_H
