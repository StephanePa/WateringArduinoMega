#ifndef SPT_SENSOR_H
#define SPT_SENSOR_H
#include "spt_definition.h"
#include "arduino.h"
//#include "spt_tcpserver.h"
//#include "spt_xml.h"
//#include <PubSubClient.h>




///////////////////////////////////////////////////////////////////////////////
// CSensor type
///////////////////////////////////////////////////////////////////////////////
#define CSENSOR_UNKNOWN 0
#define CSENSOR_DHT 1
#define CSENSOR_DS18S20 2
#define CSENSOR_ANALOG 3
#define CSENSOR_ANALOG_SOILMOISTURE 4
#define CSENSOR_ANALOG_LIGHT 5

///////////////////////////////////////////////////////////////////////////////
// CAlarm type
///////////////////////////////////////////////////////////////////////////////
#define CALARM_ALARM_MAX 2
#define CALARM_WARNING_MAX 1
#define CALARM_NO_ALARM 0
#define CALARM_WARNING_MIN -1
#define CALARM_ALARM_MIN -2

///////////////////////////////////////////////////////////////////////////////
// Class CSensor
///////////////////////////////////////////////////////////////////////////////
class CSensor
{
  public:
    // Constructor
    CSensor();
	// enable / disable set functions
    void Enable();
    void Disable();
    void SetEnabled(boolean enable);
	// get state function
    boolean IsEnabled();
    int GetType();
    int GetId();
    // get data in JSON formatted format
    virtual String GetJSONString();
    // Publish Data (MQTT broker)
    void MQTTPublishData();
  protected:
    // class Reset function
    virtual void Reset();
    // initialisation function (set parameters)
    void Init(int sensorid/*, PubSubClient *mqttclient=NULL*/);
	// get data in JSON formatted format (internal function)
	virtual String _addJSONString(String str);
    // Id of the Sensor
    int Id;
    // Sensor Type
    int Type;
    // pointer to the wifi module for data transmission to the connected TCP/IP clients
    // MQTT Broquer pointer
    //PubSubClient *MQTT_Client;
    // Sensor enable or disable
    boolean Enabled;
	// temporary String
    static String str_topic,str_payload;
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Class CSensor
///////////////////////////////////////////////////////////////////////////////
class CAlarm
{
  public:
    // Constructor
    CAlarm();
    void Reset();
    void Init(float alarm_min,float warning_min,float warning_max,float alarm_max);
    int CheckValue(float value);
  protected:
    // Warning and Alarm thresholds
    // value>=AlarmMaxValue
      float AlarmMinValue;
      float WarningMinValue;
      float WarningMaxValue;
      float AlarmMaxValue;
};
///////////////////////////////////////////////////////////////////////////////
#endif // SPT_SENSOR_H
