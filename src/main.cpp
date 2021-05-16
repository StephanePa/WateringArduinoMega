//#include <WiFiEsp.h>
//#include <WiFiEspClient.h>
//#include <WiFiEspUdp.h>
//#include <PubSubClient.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "spt_definition.h"
#include "spt_application2.h"
#include <SD.h>


/////////////////////////////////////////////////////////////////////////////////
/// Debug functions
/////////////////////////////////////////////////////////////////////////////////
//void Serial_print(String a) { if (_SERIAL_Version) Serial.print(a); }
//void Serial_println(String a) { if (_SERIAL_Version) Serial.println(a); }
//void Serial_print(int a) { if (_SERIAL_Version) Serial.print(a); }
//void Serial_println(int a) { if (_SERIAL_Version) Serial.println(a); }
/////////////////////////////////////////////////////////////////////////////////

// Init MQTT address
//IPAddress server(MQTT_a1,MQTT_a2,MQTT_a3,MQTT_a4); //RPi address

// Init Wifi Status
//int status = WL_IDLE_STATUS; // the Wifi radio's status

// Initialize the Ethernet client object
//WiFiEspClient espClient;

// MQTT instance
//PubSubClient client(espClient);

// data
spt_data Data;

// Application instance
spt_application Application;
int spt_application::FunctionID;
int spt_application::CommandStatus;
int spt_application::State;
int spt_application::PreviousState;
bool spt_application::SensorMeasurementEnabled;
//PubSubClient* spt_application::MQTT_Client;
char spt_application::str_temp[255];
spt_data* spt_application::dataPtr;
String spt_application::str_payload;
String spt_application::str_topic;

// JSON Document
  // Json 5
  #ifdef JSONVERSION5
  StaticJsonBuffer<512> spt_application::JsonCmdObject;
  JsonObject& spt_application::JsonCmd = 0;
  #endif
  // Json 6
  #ifdef JSONVERSION6
  StaticJsonDocument<255> spt_application::JsonCmd;
  #endif
  
int spt_application::Step;

String CPowerSupply::str_payload;
String CPowerSupply::str_topic;

String CSensor::str_topic;
String CSensor::str_payload;
      
void setup() 
{
  // initialize serial for debugging
  pinMode(BusyLedPin,OUTPUT);
  digitalWrite(BusyLedPin, HIGH);
  
  Serial.begin(115200);
  // initialize serial for ESP module
  Serial2.begin(115200);
  // initialize ESP module
  //WiFi.init(&Serial2);

  // Initialisation SD Card
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(SD_SS_CS_Pin, OUTPUT);
  if (SD.begin(SD_SS_CS_Pin))
  {
#ifdef _SERIAL_VERSION_
Serial.println("SD Begin -> OK");
#endif
    Data.LoadConfiguration();
  }
  else
  {
#ifdef _SERIAL_VERSION_
Serial.println("SD Begin -> ERROR !");
#endif
  }
  // Init Application
  Data.Init(/*&client*/);
  Application.Init(&Data/*,&client*/);
 

  // check for the presence of the shield
  /*if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }*/

  // attempt to connect to WiFi network
  /*
  while ( status != WL_CONNECTED) 
  {
    Serial.print("Attempting to connect to WPA SSID: ");
    //Serial.println(ssid);
    Serial.println(SSID);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(SSID, PASSWORD);
   }

   // you're connected now, so print out the data
   Serial.println("You're connected to the network");

   //connect to MQTT server
   client.setServer(server, 1883);
   client.setCallback(callback);
   */
   Application.SetState(ProgramState_WaitingForCommand);
   digitalWrite(BusyLedPin, LOW);
}

//print any message received for subscribed topic


void loop() {
bool bool_debug;
// put your main code here, to run repeatedly:
/*
if (!client.connected()) {
reconnect();
}
*/
//client.loop();
delay(200);

if (Serial2.available())
{
    String str;
    str = Serial2.readString();
Serial.print("---> string received (");
Serial.print(str.length());
Serial.print("):");
Serial.println(str);

for (int ii=0;ii<str.length();ii++)
{
  Serial.print("..(");
  Serial.print(ii);
  Serial.print(") : ");
  Serial.println((int)str.c_str()[ii]);
}
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, str.c_str());
    // Test if parsing succeeds.
        if (error)
        {
            Serial.println(F("   > Json parse error"));
            return;
        }
        else
        {
            /*int function = doc["f"];
            strncpy(buff, (char*)payload, length);
            buff[length] = 0x00;
            String str2(buff);
            // Print values.
            Serial.print("   > function n°"); Serial.println(function);
            Serial.print("   > code : "); Serial.println(value);
            Serial.print("> launch code Application.Command(str) str="); Serial.println(str2);*/
            Application.Command(str); // return boolean !!!
        }
    /*char receivedChar = (char)payload[i];
    Serial.print(receivedChar);
    if (receivedChar == '0') Serial.println("Off");
    if (receivedChar == '1') Serial.println("On");
    */
    //}
    Serial.println();
    //client.publish(MQTT_PublishTopic, "{\"ack\":\"ok\",\"func\":0}");
    Serial2.println("[ack]ok");
}

//#ifdef _SERIAL_VERSION_
//Serial.print(F("LOOP Application State = "));
//Serial.println(Application.GetState());
//#endif
  // ----------------------------------------------------------------------------
  // Soil temperature and relative humidity measurement
  // ----------------------------------------------------------------------------
/*
#ifdef _SERIAL_VERSION_
Serial.print("> Data.SoilSensorTimer.IsDone() ->");
if (Data.SoilSensorTimer.IsDone()) Serial.print("true"); else Serial.print("false");
Serial.print("; ");
Serial.print(Data.SoilSensorTimer.GetTimerValue());
Serial.print("; ");
Serial.println(Data.SoilSensorTimer.GetCurrentValue());
Serial.print("> Application.IsSensorMeasurementEnabled() ->");
if (Application.IsSensorMeasurementEnabled()) Serial.println("true"); else Serial.println("false");
#endif
*/
    if (Data.SoilSensorTimer.IsDone()&&Application.IsSensorMeasurementEnabled()) Application.SoilSensorMeasurement();
  // ----------------------------------------------------------------------------

  // ----------------------------------------------------------------------------
  // Check if Program State is ProgramState_WaitingForCommand
  // ----------------------------------------------------------------------------
  if (Application.GetState()==ProgramState_WaitingForCommand)
  {
    if (digitalRead(ManualPumpPushButtonPin)==HIGH)
    { // Start WateringCycle
      Application.StartManualPump();
      delay(1000);
    }
    if (digitalRead(WateringCyclePushButtonPin)==HIGH)
    { // Start WateringCycle
      Application.StartWateringCycle();
      delay(1000);
    }
    // ----------------------------------------------------------------------------
    // Other sensor measurement
    // ----------------------------------------------------------------------------
      if (Data.SensorTimer.IsDone()&&Application.IsSensorMeasurementEnabled()) Application.OtherSensorMeasurement();
    // ----------------------------------------------------------------------------
    /*
    if (digitalRead(WateringFlowerPot1PushButtonPin)==HIGH)
    { // Start WateringCycle
      App.StartWateringFlowerPot(1);
      delay(1000);
    }
    if (digitalRead(WateringFlowerPot2PushButtonPin)==HIGH)
    { // Start WateringCycle
      App.StartWateringFlowerPot(2);
      delay(1000);
    }
    if (digitalRead(WateringFlowerPot3PushButtonPin)==HIGH)
    { // Start WateringCycle
      App.StartWateringFlowerPot(3);
      delay(1000);
    }
    if (digitalRead(WateringFlowerPot4PushButtonPin)==HIGH)
    { // Start WateringCycle
      App.StartWateringFlowerPot(4);
      delay(1000);
    }
    if (digitalRead(WateringFlowerPot5PushButtonPin)==HIGH)
    { // Start WateringCycle
      App.StartWateringFlowerPot(5);
      delay(1000);
    }
    */
  }
  // ----------------------------------------------------------------------------

  // ----------------------------------------------------------------------------
  // Check if Program State is ProgramState_WateringCycle
  // ----------------------------------------------------------------------------
  if (Application.GetState()==ProgramState_WateringCycle)
  {
    if (digitalRead(WateringCyclePushButtonPin)==HIGH)
    { // Stop WateringCycle
      Application.StopWateringCycle();
      delay(1000);
    }
    else
    {
      Application.NextWateringCycleStep();
    }
  }
  // ----------------------------------------------------------------------------

  // ----------------------------------------------------------------------------
  // Check if Program State is ProgramState_WateringFlowerPot(n)
  // ----------------------------------------------------------------------------
  int state=Application.GetState()-ProgramState_WateringFlowerPot;
  int pin;
  if ((state>=1)&&(state<=5))
  {
    switch (state)
    {
      case 1:
        pin=WateringFlowerPot1PushButtonPin;
        break;
      case 2:
        pin=WateringFlowerPot2PushButtonPin;
        break;
      case 3:
        pin=WateringFlowerPot3PushButtonPin;
        break;
      case 4:
        pin=WateringFlowerPot4PushButtonPin;
        break;
      case 5:
        pin=WateringFlowerPot5PushButtonPin;
        break;
    }
    // pin not connected then force pin=LOW
    bool_debug=false;
    if ((digitalRead(pin)==HIGH) && bool_debug)
    {
      Application.StopWateringFlowerPot();
      delay(1000);
    }
    else
    {
      Application.CheckWateringFlowerPotTimeout();
    }
  }
  // ----------------------------------------------------------------------------

  // ----------------------------------------------------------------------------
  // Check if Program State is ProgramState_ManualPump
  // ----------------------------------------------------------------------------
  if (Application.GetState()==ProgramState_ManualPump)
  {
    // pin not connected then force pin=LOW
    bool_debug=true;
    if ((digitalRead(ManualPumpPushButtonPin)==HIGH) && bool_debug)
    //if (digitalRead(ManualPumpPushButtonPin)==HIGH)
    {
      Application.StopManualPump();
      delay(1000);
    }
    else
    {
      Application.CheckManualPumpTimeout();
    }
  }
  // ----------------------------------------------------------------------------

}
