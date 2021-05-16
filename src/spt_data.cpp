#include "spt_data.h"
#include "spt_utils.h"
#include <string.h>

File_DataConfig::File_DataConfig()
{
  // default value

  // DHTSensor[0] - AirTemperatureRelativeHumidity Sensor Box
  DHT_Sensors[0].Id=AirTemperatureRelativeHumiditySensor_1_Id;
  DHT_Sensors[0].Pin=DTH11_internal_DigitalInputPin;
  DHT_Sensors[0].Type=DHT11SensorType;
  DHT_Sensors[0].enable=0;
  // DHTSensor[0] - AirTemperatureRelativeHumidity Sensor Box
  DHT_Sensors[0].Id=AirTemperatureRelativeHumiditySensor_2_Id;
  DHT_Sensors[0].Pin=DTH22_1_external_DigitalInputPin;
  DHT_Sensors[0].Type=DHT22SensorType;
  DHT_Sensors[0].enable=0;
  // DHTSensor[0] - AirTemperatureRelativeHumidity Sensor Box
  DHT_Sensors[0].Id=AirTemperatureRelativeHumiditySensor_3_Id;
  DHT_Sensors[0].Pin=DTH22_2_external_DigitalInputPin;
  DHT_Sensors[0].Type=DHT22SensorType;
  DHT_Sensors[0].enable=0;
  // WaterPump1
  WaterPump1_PowerSupply.Id=WaterPump_1_Id;
  WaterPump1_PowerSupply.Pin=WaterPump_1_PowerSupplyOutputPin;
  // PS12V_PowerSupply
  PS12V_PowerSupply.Id=3001;
  PS12V_PowerSupply.Pin=PS12V_PowerSupplyOutputPin;
  // Sensor_PowerSupply
  Sensor_PowerSupply.Id=SensorPowerSupply_Id;
  Sensor_PowerSupply.Pin=Sensor_PowerSupplyOutputPin;
  // SolenoidValve_PowerSupply
  SolenoidValve[0].Id=SolenoidValve_1_Id;
  SolenoidValve[0].Pin=SolenoidValve1_PowerSupplyOutputPin;
  SolenoidValve[1].Id=SolenoidValve_2_Id;
  SolenoidValve[1].Pin=SolenoidValve2_PowerSupplyOutputPin;
  SolenoidValve[2].Id=SolenoidValve_3_Id;
  SolenoidValve[2].Pin=SolenoidValve3_PowerSupplyOutputPin;
  SolenoidValve[3].Id=SolenoidValve_4_Id;
  SolenoidValve[3].Pin=SolenoidValve4_PowerSupplyOutputPin;
  SolenoidValve[4].Id=SolenoidValve_5_Id;
  SolenoidValve[4].Pin=SolenoidValve5_PowerSupplyOutputPin;

  // Push Buttons
  WateringCyclePushButton.Pin=WateringCyclePushButtonPin;
  WateringCyclePushButton.enable=1;
  ManualPumpPushButton.Pin=ManualPumpPushButtonPin;
  ManualPumpPushButton.enable=1;
  ManualPumpPushButton.timer=10;
  WateringFlowerPotPushButton[0].Pin=WateringFlowerPot1PushButtonPin;
  WateringFlowerPotPushButton[0].enable=1;
  WateringFlowerPotPushButton[0].timer=11;
  WateringFlowerPotPushButton[1].Pin=WateringFlowerPot2PushButtonPin;
  WateringFlowerPotPushButton[1].enable=1;
  WateringFlowerPotPushButton[1].timer=11;
  WateringFlowerPotPushButton[2].Pin=WateringFlowerPot3PushButtonPin;
  WateringFlowerPotPushButton[2].enable=1;
  WateringFlowerPotPushButton[2].timer=11;
  WateringFlowerPotPushButton[3].Pin=WateringFlowerPot4PushButtonPin;
  WateringFlowerPotPushButton[3].enable=1;
  WateringFlowerPotPushButton[3].timer=11;
  WateringFlowerPotPushButton[4].Pin=WateringFlowerPot5PushButtonPin;
  WateringFlowerPotPushButton[4].enable=1;
  WateringFlowerPotPushButton[4].timer=11;

  // TinyRTC Module (Time module)
  TinyRTC.PinWire_SCL=PIN_WIRE_SCL;
  TinyRTC.PinWire_SDA=PIN_WIRE_SDA;
  
  // Busy Led Status
  BusyLed.Pin=BusyLedPin;

  // OneWire configuration
  One_Wire.Pin=OneWire_DigitalInputPin;

  // DS18S20 one wire sensor
  DS18S20[0].Id=SoilTemperatureSensor_1_Id;
  DS18S20[0].Addr[0]=0x28; DS18S20[0].Addr[1]=0x81; DS18S20[0].Addr[2]=0x11; DS18S20[0].Addr[3]=0x04; 
  DS18S20[0].Addr[4]=0x00; DS18S20[0].Addr[5]=0x00; DS18S20[0].Addr[6]=0x80; DS18S20[0].Addr[7]=0xF0;
  DS18S20[0].enable=0;
  DS18S20[1].Id=SoilTemperatureSensor_2_Id;
  DS18S20[1].Addr[0]=0x28; DS18S20[1].Addr[1]=0x47; DS18S20[1].Addr[2]=0x1B; DS18S20[1].Addr[3]=0x27; 
  DS18S20[1].Addr[4]=0x00; DS18S20[1].Addr[5]=0x00; DS18S20[1].Addr[6]=0x80; DS18S20[1].Addr[7]=0x98;
  DS18S20[1].enable=0;
  DS18S20[2].Id=SoilTemperatureSensor_3_Id;
  DS18S20[2].Addr[0]=0x28; DS18S20[2].Addr[1]=0xF9; DS18S20[2].Addr[2]=0x1B; DS18S20[2].Addr[3]=0x27; 
  DS18S20[2].Addr[4]=0x00; DS18S20[2].Addr[5]=0x00; DS18S20[2].Addr[6]=0x80; DS18S20[2].Addr[7]=0x8C;
  DS18S20[2].enable=0;
  DS18S20[3].Id=SoilTemperatureSensor_4_Id;
  DS18S20[3].Addr[0]=0x28; DS18S20[3].Addr[1]=0xBB; DS18S20[3].Addr[2]=0xC2; DS18S20[3].Addr[3]=0x26; 
  DS18S20[3].Addr[4]=0x00; DS18S20[3].Addr[5]=0x00; DS18S20[3].Addr[6]=0x80; DS18S20[3].Addr[7]=0xB5;
  DS18S20[3].enable=0;
  DS18S20[4].Id=SoilTemperatureSensor_5_Id;
  DS18S20[4].Addr[0]=0x28; DS18S20[4].Addr[1]=0x5D; DS18S20[4].Addr[2]=0xA6; DS18S20[4].Addr[3]=0x26; 
  DS18S20[4].Addr[4]=0x00; DS18S20[4].Addr[5]=0x00; DS18S20[4].Addr[6]=0x80; DS18S20[4].Addr[7]=0x20;
  DS18S20[4].enable=0;

  // SensorTimerValue
  SensorTimerValue=60;
  // SoilSensorTimerValue
  SoilSensorTimerValue=120;
}

void File_DataConfig::_loadConfigFile(File& OrigFile)
{
  int i,j;
  unsigned int val;
  int line_counter;
  char * pEnd;
  String str;

#ifdef _SERIAL_VERSION_
Serial.println("File_DataConfig::_loadConfigFile()");
#endif 

  line_counter=0;

  while(OrigFile.available() > 0 )
  {
    // Get a line
    i = 0;
    while((buffer[i++] = OrigFile.read()) != '\n') 
    {
      /* Si la ligne dépasse la taille du buffer */
      if(i == 200) 
      {
         /* On finit de lire la ligne mais sans stocker les données */
        while(OrigFile.read() != '\n');
        break; // Et on arrête la lecture de cette ligne
      }  
    }
    /* Finalise la chaine de caractéres ASCIIZ en supprimant le \n au passage */
    buffer[--i] = '\0';
 
    /* Incrémente le compteur de lignes */
    ++line_counter;
 
    /* Ignore les lignes vides ou les lignes de commentaires */
    if(buffer[0] == '\0' || buffer[0] == '#') continue;  
    buf=strstr(buffer,"="); buf++;
    int n=strlen(buffer)-strlen(buf)-1;
    strncpy(key,buffer,n);
    key[n]='\0';
    str=String(key);
/*
#ifdef _SERIAL_VERSION_
Serial.print("File_DataConfig::_loadConfigFile -> ");
Serial.println(buffer);
Serial.print("  >buf=");
Serial.println(key);
Serial.print("  >val=");
Serial.println(buf);
#endif 
*/
    // DHTSensor[0] - AirTemperatureRelativeHumidity Sensor Box
    if (str == String(F("DHTSensor[0].Id"))) DHT_Sensors[0].Id=String(buf).toInt();
    if (str == String(F("DHTSensor[0].Pin"))) DHT_Sensors[0].Pin=String(buf).toInt();
    if (str == String(F("DHTSensor[0].Type")))
    {
      buf[strlen(buf)-1]=0x00;
#ifdef _SERIAL_VERSION_
Serial.print("  >> DHTSensor[0].Type -> buffer=");
Serial.println(buffer);
Serial.print("  >> DHTSensor[0].Type -> Key=");
Serial.println(key);
Serial.print("  >> DHTSensor[0].Type -> Buf=");
Serial.println(buf);
Serial.print("  >> ");
if (strcmp(buf,"DHT11SensorType")==0) Serial.print("DHT11; "); else Serial.print("no_DHT11; "); 
if (strcmp(buf,"DHT22SensorType")==0) Serial.print("DHT22; "); else Serial.print("no_DHT22; "); 
Serial.println("  <<");
Serial.print("  >> length : ");
Serial.print(strlen(buf));
Serial.print("  >> length : ");
Serial.println(strlen("DHT11SensorType"));
#endif 
      DHT_Sensors[0] .Type=DHT22SensorType;
      if (strcmp(buf,"DHT11SensorType")==0) DHT_Sensors[0].Type=DHT11SensorType;
      if (strcmp(buf,"DHT22SensorType")==0) DHT_Sensors[0].Type=DHT22SensorType;
    }
    if (str == String(F("DHTSensor[0].enabled"))) DHT_Sensors[0].enable=String(buf).toInt();

    // DHTSensor[1] - AirTemperatureRelativeHumidity Sensor Greenhouse
    if (str == String(F("DHTSensor[1].Id"))) DHT_Sensors[1].Id=String(buf).toInt();
    if (str == String(F("DHTSensor[1].Pin"))) DHT_Sensors[1].Pin=String(buf).toInt();
    if (str == String(F("DHTSensor[1].Type")))
    {
      buf[strlen(buf)-1]=0x00;
#ifdef _SERIAL_VERSION_
Serial.print("  >> DHTSensor[1].Type -> buffer=");
Serial.println(buffer);
Serial.print("  >> DHTSensor[1].Type -> Key=");
Serial.println(key);
Serial.print("  >> DHTSensor[1].Type -> Buf=");
Serial.println(buf);
Serial.print("  >> ");
if (strcmp(buf,"DHT11SensorType")==0) Serial.print("DHT11; "); else Serial.print("no_DHT11; "); 
if (strcmp(buf,"DHT22SensorType")==0) Serial.print("DHT22; "); else Serial.print("no_DHT22; "); 
Serial.println("  <<");
Serial.print("  >> length : ");
Serial.print(strlen(buf));
Serial.print("  >> length : ");
Serial.println(strlen("DHT11SensorType"));
#endif 
      DHT_Sensors[1].Type=DHT22SensorType;
      if (strcmp(buf,"DHT11SensorType")==0) DHT_Sensors[1].Type=DHT11SensorType;
      if (strcmp(buf,"DHT22SensorType")==0) DHT_Sensors[1].Type=DHT22SensorType;
    }
    if (str == String(F("DHTSensor[1].enabled"))) DHT_Sensors[1].enable=String(buf).toInt();

    // DHTSensor[2] - AirTemperatureRelativeHumidity Sensor OutDoor
    if (str == String(F("DHTSensor[2].Id"))) DHT_Sensors[2].Id=String(buf).toInt();
    if (str == String(F("DHTSensor[2].Pin"))) DHT_Sensors[2].Pin=String(buf).toInt();
    if (str == String(F("DHTSensor[2].Type")))
    {
      buf[strlen(buf)-1]=0x00;
#ifdef _SERIAL_VERSION_
Serial.print("  >> DHTSensor[2].Type -> buffer=");
Serial.println(buffer);
Serial.print("  >> DHTSensor[2].Type -> Key=");
Serial.println(key);
Serial.print("  >> DHTSensor[2].Type -> Buf=");
Serial.println(buf);
Serial.print("  >> ");
if (strcmp(buf,"DHT11SensorType")==0) Serial.print("DHT11; "); else Serial.print("no_DHT11; "); 
if (strcmp(buf,"DHT22SensorType")==0) Serial.print("DHT22; "); else Serial.print("no_DHT22; "); 
Serial.println("  <<");
Serial.print("  >> length : ");
Serial.print(strlen(buf));
Serial.print("  >> length : ");
Serial.println(strlen("DHT11SensorType"));
#endif 
      DHT_Sensors[2].Type=DHT22SensorType;
      if (strcmp(buf,"DHT11SensorType")==0) DHT_Sensors[2].Type=DHT11SensorType;
      if (strcmp(buf,"DHT22SensorType")==0) DHT_Sensors[2].Type=DHT22SensorType;
    }
    if (str == String(F("DHTSensor[2].enabled"))) DHT_Sensors[2].enable=String(buf).toInt();

    // WaterPump1
    if (str == String(F("WaterPump1.Id"))) WaterPump1_PowerSupply.Id=String(buf).toInt();
    if (str == String(F("WaterPump1.Pin"))) WaterPump1_PowerSupply.Pin=String(buf).toInt();

    // PS12V_PowerSupply
    if (str == String(F("PS12V.Id"))) PS12V_PowerSupply.Id=String(buf).toInt();
    if (str == String(F("PS12V.Pin"))) PS12V_PowerSupply.Pin=String(buf).toInt();

    // Sensor_PowerSupply
    if (str == String(F("PSSensor.Id"))) Sensor_PowerSupply.Id=String(buf).toInt();
    if (str == String(F("PSSensor.Pin"))) Sensor_PowerSupply.Pin=String(buf).toInt();

    // SolenoidValve_PowerSupply
    if (str == String(F("PSSolenoidValve[0].Id"))) SolenoidValve[0].Id=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[0].Pin"))) SolenoidValve[0].Pin=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[1].Id"))) SolenoidValve[1].Id=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[1].Pin"))) SolenoidValve[1].Pin=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[2].Id"))) SolenoidValve[2].Id=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[2].Pin"))) SolenoidValve[2].Pin=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[3].Id"))) SolenoidValve[3].Id=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[3].Pin"))) SolenoidValve[3].Pin=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[4].Id"))) SolenoidValve[4].Id=String(buf).toInt();
    if (str == String(F("PSSolenoidValve[4].Pin"))) SolenoidValve[4].Pin=String(buf).toInt();

    // Push Buttons
    if (str == String(F("PBWateringCycle.Pin"))) WateringCyclePushButton.Pin=String(buf).toInt();
    if (str == String(F("PBWateringCycle.enable"))) WateringCyclePushButton.enable=String(buf).toInt();
    if (str == String(F("PBManualPump.Pin"))) ManualPumpPushButton.Pin=String(buf).toInt();
    if (str == String(F("PBManualPump.enable"))) ManualPumpPushButton.enable=String(buf).toInt();
    if (str == String(F("PBManualPump.Timer"))) ManualPumpPushButton.timer=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[0].Pin"))) WateringFlowerPotPushButton[0].Pin=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[0].enable"))) WateringFlowerPotPushButton[0].enable=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[0].Timer"))) WateringFlowerPotPushButton[0].timer=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[1].Pin"))) WateringFlowerPotPushButton[1].Pin=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[1].enable"))) WateringFlowerPotPushButton[1].enable=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[1].Timer"))) WateringFlowerPotPushButton[1].timer=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[2].Pin"))) WateringFlowerPotPushButton[2].Pin=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[2].enable"))) WateringFlowerPotPushButton[2].enable=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[2].Timer"))) WateringFlowerPotPushButton[2].timer=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[3].Pin"))) WateringFlowerPotPushButton[3].Pin=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[3].enable"))) WateringFlowerPotPushButton[3].enable=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[3].Timer"))) WateringFlowerPotPushButton[3].timer=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[4].Pin"))) WateringFlowerPotPushButton[4].Pin=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[4].enable"))) WateringFlowerPotPushButton[4].enable=String(buf).toInt();
    if (str == String(F("PBWateringFlowerPot[4].Timer"))) WateringFlowerPotPushButton[4].timer=String(buf).toInt();
    

    // TinyRTC Module (Time module)
    if (str == String(F("RTC.SCL"))) TinyRTC.PinWire_SCL=String(buf).toInt();
    if (str == String(F("RTC.SDA"))) TinyRTC.PinWire_SDA=String(buf).toInt();
  
    // Busy Led Status
    if (str == String(F("LedStatus.Pin"))) BusyLed.Pin=String(buf).toInt();

    // OneWire configuration
    if (str == String(F("OneWire.Pin"))) One_Wire.Pin=String(buf).toInt();

    // DS18S20 one wire sensor
    // sensor 1
    if (str == String(F("DS18S20_Sensors[0].Id"))) DS18S20[0].Id=String(buf).toInt();
    if (str == String(F("DS18S20_Sensors[0].Addr"))) 
    {
      for (j=0;j<8;j++) DS18S20[0].Addr[j]=(convertCharToHex(buf[2*j])<<4) + convertCharToHex(buf[2*j+1]);
    }
    if (str == String(F("DS18S20_Sensors[0].enabled"))) DS18S20[0].enable=String(buf).toInt();
    // sensor 2
    if (str == String(F("DS18S20_Sensors[1].Id"))) DS18S20[1].Id=String(buf).toInt();
    if (str == String(F("DS18S20_Sensors[1].Addr"))) 
    {
      for (j=0;j<8;j++) DS18S20[1].Addr[j]=(convertCharToHex(buf[2*j])<<4) + convertCharToHex(buf[2*j+1]);
    }
    if (str == String(F("DS18S20_Sensors[1].enabled"))) DS18S20[1].enable=String(buf).toInt();
    // sensor 3
    if (str == String(F("DS18S20_Sensors[2].Id"))) DS18S20[2].Id=String(buf).toInt();
    if (str == String(F("DS18S20_Sensors[2].Addr"))) 
    {
      for (j=0;j<8;j++) 
      {
        DS18S20[2].Addr[j]=(convertCharToHex(buf[2*j])<<4) + convertCharToHex(buf[2*j+1]);
#ifdef _SERIAL_VERSION_
Serial.print("  >> DS18S20[2].Addr -> j=");
Serial.print(j);
Serial.print("; 2j->");
Serial.print(buf[2*j]);
Serial.print(" <> ");
Serial.print(convertCharToHex(buf[2*j]));
Serial.print("; 2j+1->");
Serial.print(buf[2*j+1]);
Serial.print("; 2j+1->");
Serial.print(buf[2*j+1]);
Serial.print(" <> ");
Serial.print(convertCharToHex(buf[2*j+1]));
Serial.print("; ");
Serial.println(String(DS18S20[2].Addr[j],HEX));
#endif 

      }
    }
    if (str == String(F("DS18S20_Sensors[2].enabled"))) DS18S20[2].enable=String(buf).toInt();
    // sensor 4
    if (str == String(F("DS18S20_Sensors[3].Id"))) DS18S20[3].Id=String(buf).toInt();
    if (str == String(F("DS18S20_Sensors[3].Addr"))) 
    {
      for (j=0;j<8;j++) DS18S20[3].Addr[j]=(convertCharToHex(buf[2*j])<<4) + convertCharToHex(buf[2*j+1]);
    }
    if (str == String(F("DS18S20_Sensors[3].enabled"))) DS18S20[3].enable=String(buf).toInt();
    // sensor 5
    if (str == String(F("DS18S20_Sensors[4].Id"))) DS18S20[4].Id=String(buf).toInt();
    if (str == String(F("DS18S20_Sensors[4].Addr"))) 
    {
      for (j=0;j<8;j++) DS18S20[4].Addr[j]=(convertCharToHex(buf[2*j])<<4) + convertCharToHex(buf[2*j+1]);
    }
    if (str == String(F("DS18S20_Sensors[4].enabled"))) DS18S20[4].enable=String(buf).toInt();

    // SensorTimerValue
    if (str == String(F("SensorTimerValue"))) SensorTimerValue=String(buf).toInt();

    // SoilSensorTimerValue
    if (str == String(F("SoilSensorTimerValue"))) SoilSensorTimerValue=String(buf).toInt();
  }
#ifdef _SERIAL_VERSION_
Serial.println("end of .................................. File_DataConfig::_loadConfigFile()");
#endif 
};

void File_DataConfig::_saveConfigFile(File& DestFile)
{
  int j;
  String hex_str;

  DestFile.println(F("#------------------------------"));
  DestFile.println(F("# ARDUINO GREENHGOUSE v0.1"));
  DestFile.println(F("# Configuration file"));
  DestFile.println(F("#------------------------------"));
  
  DestFile.println(F("#"));
  DestFile.println(F("# AirTemperatureRelativeHumidity Sensor Box"));
  DestFile.print(F("DHTSensor[0].Id="));
  DestFile.println(DHT_Sensors[0].Id);
  DestFile.print(F("DHTSensor[0].Pin="));
  DestFile.println(DHT_Sensors[0].Pin);
  DestFile.print(F("DHTSensor[0].Type="));
  if (DHT_Sensors[0].Type==DHT11SensorType) DestFile.println("DHT11SensorType");
  if (DHT_Sensors[0].Type==DHT22SensorType) DestFile.println("DHT22SensorType");
  DestFile.print(F("DHTSensor[0].enabled="));
  DestFile.println(DHT_Sensors[0].enable);

  DestFile.println(F("#"));
  DestFile.println(F("# AirTemperatureRelativeHumidity Sensor Greenhouse"));
  DestFile.print(F("DHTSensor[1].Id="));
  DestFile.println(DHT_Sensors[1].Id);
  DestFile.print(F("DHTSensor[1].Pin="));
  DestFile.println(DHT_Sensors[1].Pin);
  DestFile.print(F("DHTSensor[1].Type="));
  if (DHT_Sensors[1].Type==DHT11SensorType) DestFile.println("DHT11SensorType");
  if (DHT_Sensors[1].Type==DHT22SensorType) DestFile.println("DHT22SensorType");
  DestFile.print(F("DHTSensor[1].enabled="));
  DestFile.println(DHT_Sensors[1].enable);

  DestFile.println(F("#"));
  DestFile.println(F("# AirTemperatureRelativeHumidity Sensor OutDoor"));
  DestFile.print(F("DHTSensor[2].Id="));
  DestFile.println(DHT_Sensors[2].Id);
  DestFile.print(F("DHTSensor[2].Pin="));
  DestFile.println(DHT_Sensors[2].Pin);
  DestFile.print(F("DHTSensor[2].Type="));
  if (DHT_Sensors[2].Type==DHT11SensorType) DestFile.println("DHT11SensorType");
  if (DHT_Sensors[2].Type==DHT22SensorType) DestFile.println("DHT22SensorType");
  DestFile.print(F("DHTSensor[2].enabled="));
  DestFile.println(DHT_Sensors[2].enable);

  DestFile.println(F("#"));
  DestFile.println(F("# Water Pump 1"));
  DestFile.print(F("WaterPump1.Id="));
  DestFile.println(WaterPump1_PowerSupply.Id);
  DestFile.print(F("WaterPump1.Pin="));
  DestFile.println(WaterPump1_PowerSupply.Pin);

  DestFile.println(F("#"));
  DestFile.println(F("# PS12V_PowerSupply"));
  DestFile.print(F("PS12V.Id="));
  DestFile.println(PS12V_PowerSupply.Id);
  DestFile.print(F("PS12V.Pin="));
  DestFile.println(PS12V_PowerSupply.Pin);

  DestFile.println(F("#"));
  DestFile.println(F("# PSSolenoidValve_PowerSupply"));
  DestFile.print(F("PSSolenoidValve[0].Id="));
  DestFile.println(SolenoidValve[0].Id);
  DestFile.print(F("PSSolenoidValve[0].Pin="));
  DestFile.println(SolenoidValve[0].Pin);
  DestFile.print(F("PSSolenoidValve[1].Id="));
  DestFile.println(SolenoidValve[1].Id);
  DestFile.print(F("PSSolenoidValve[1].Pin="));
  DestFile.println(SolenoidValve[1].Pin);
  DestFile.print(F("PSSolenoidValve[2].Id="));
  DestFile.println(SolenoidValve[2].Id);
  DestFile.print(F("PSSolenoidValve[2].Pin="));
  DestFile.println(SolenoidValve[2].Pin);
  DestFile.print(F("PSSolenoidValve[3].Id="));
  DestFile.println(SolenoidValve[3].Id);
  DestFile.print(F("PSSolenoidValve[3].Pin="));
  DestFile.println(SolenoidValve[3].Pin);
  DestFile.print(F("PSSolenoidValve[4].Id="));
  DestFile.println(SolenoidValve[4].Id);
  DestFile.print(F("PSSolenoidValve[4].Pin="));
  DestFile.println(SolenoidValve[4].Pin);

  DestFile.println(F("#"));
  DestFile.println(F("# Push Buttons"));
  DestFile.print(F("PBWateringCycle.Pin="));
  DestFile.println(WateringCyclePushButton.Pin);
  DestFile.print(F("PBWateringCycle.enable="));
  DestFile.println(WateringCyclePushButton.enable);
  DestFile.print(F("PBManualPump.Pin="));
  DestFile.println(ManualPumpPushButton.Pin);
  DestFile.print(F("PBManualPump.enable="));
  DestFile.println(ManualPumpPushButton.enable);
  DestFile.print(F("PBManualPump.Timer="));
  DestFile.println(ManualPumpPushButton.timer);
  DestFile.print(F("PBWateringFlowerPot[0].Pin="));
  DestFile.println(WateringFlowerPotPushButton[0].Pin);
  DestFile.print(F("PBWateringFlowerPot[0].enable="));
  DestFile.println(WateringFlowerPotPushButton[0].enable);
  DestFile.print(F("PBWateringFlowerPot[0].Timer="));
  DestFile.println(WateringFlowerPotPushButton[0].timer);
  DestFile.print(F("PBWateringFlowerPot[1].Pin="));
  DestFile.println(WateringFlowerPotPushButton[1].Pin);
  DestFile.print(F("PBWateringFlowerPot[1].enable="));
  DestFile.println(WateringFlowerPotPushButton[1].enable);
  DestFile.print(F("PBWateringFlowerPot[1].Timer="));
  DestFile.println(WateringFlowerPotPushButton[1].timer);
  DestFile.print(F("PBWateringFlowerPot[2].Pin="));
  DestFile.println(WateringFlowerPotPushButton[2].Pin);
  DestFile.print(F("PBWateringFlowerPot[2].enable="));
  DestFile.println(WateringFlowerPotPushButton[2].enable);
  DestFile.print(F("PBWateringFlowerPot[2].Timer="));
  DestFile.println(WateringFlowerPotPushButton[2].timer);
  DestFile.print(F("PBWateringFlowerPot[3].Pin="));
  DestFile.println(WateringFlowerPotPushButton[3].Pin);
  DestFile.print(F("PBWateringFlowerPot[3].enable="));
  DestFile.println(WateringFlowerPotPushButton[3].enable);
  DestFile.print(F("PBWateringFlowerPot[3].Timer="));
  DestFile.println(WateringFlowerPotPushButton[3].timer);
  DestFile.print(F("PBWateringFlowerPot[4].Pin="));
  DestFile.println(WateringFlowerPotPushButton[4].Pin);
  DestFile.print(F("PBWateringFlowerPot[4].enable="));
  DestFile.println(WateringFlowerPotPushButton[4].enable);
  DestFile.print(F("PBWateringFlowerPot[4].Timer="));
  DestFile.println(WateringFlowerPotPushButton[4].timer);

  DestFile.println(F("#"));
  DestFile.println(F("# TinyRTC Time module"));
  DestFile.print(F("RTC.SCL="));
  DestFile.println(TinyRTC.PinWire_SCL);
  DestFile.print(F("RTC.SDA="));
  DestFile.println(TinyRTC.PinWire_SDA);

  DestFile.println(F("#"));
  DestFile.println(F("# Led Status"));
  DestFile.print(F("LedStatus.Pin="));
  DestFile.println(BusyLed.Pin);

  DestFile.println(F("#"));
  DestFile.println(F("# One Wire Pin (for DS18S20 sensors)"));
  DestFile.print(F("OneWire.Pin="));
  DestFile.println(One_Wire.Pin);

  DestFile.println(F("#"));
  DestFile.println(F("# DS18S20 sensors"));
  DestFile.println(F("#"));
  DestFile.println(F("# DS18B20 Temperature sensor (soil measurement 1)"));
  DestFile.print(F("DS18S20_Sensors[0].Id="));
  DestFile.println(DS18S20[0].Id);
  DestFile.print(F("DS18S20_Sensors[0].Addr="));
  hex_str="";
  for (j=0;j<8;j++)
  {
    if(DS18S20[0].Addr[j] < 0x10) hex_str += '0';
    hex_str += String(DS18S20[0].Addr[j], HEX);
  }
  DestFile.println(hex_str);
  DestFile.print(F("DS18S20_Sensors[0].enabled="));
  DestFile.println(DS18S20[0].enable);
  DestFile.println(F("#"));
  DestFile.println(F("# DS18B20 Temperature sensor (soil measurement 2)"));
  DestFile.print(F("DS18S20_Sensors[1].Id="));
  DestFile.println(DS18S20[1].Id);
  DestFile.print(F("DS18S20_Sensors[1].Addr="));
  hex_str="";
  for (j=0;j<8;j++)
  {
    if(DS18S20[1].Addr[j] < 0x10) hex_str += '0';
    hex_str += String(DS18S20[1].Addr[j], HEX);
  }
  DestFile.println(hex_str);
  DestFile.print(F("DS18S20_Sensors[1].enabled="));
  DestFile.println(DS18S20[1].enable);
  DestFile.println(F("#"));
  DestFile.println(F("# DS18B20 Temperature sensor (soil measurement 3)"));
  DestFile.print(F("DS18S20_Sensors[2].Id="));
  DestFile.println(DS18S20[2].Id);
  DestFile.print(F("DS18S20_Sensors[2].Addr="));
  hex_str="";
  for (j=0;j<8;j++)
  {
    if(DS18S20[2].Addr[j] < 0x10) hex_str += '0';
    hex_str += String(DS18S20[2].Addr[j], HEX);
  }
  DestFile.println(hex_str);
  DestFile.print(F("DS18S20_Sensors[2].enabled="));
  DestFile.println(DS18S20[2].enable);
  DestFile.println(F("#"));
  DestFile.println(F("# DS18B20 Temperature sensor (soil measurement 4)"));
  DestFile.print(F("DS18S20_Sensors[3].Id="));
  DestFile.println(DS18S20[3].Id);
  DestFile.print(F("DS18S20_Sensors[3].Addr="));
  hex_str="";
  for (j=0;j<8;j++)
  {
    if(DS18S20[3].Addr[j] < 0x10) hex_str += '0';
    hex_str += String(DS18S20[3].Addr[j], HEX);
  }
  DestFile.println(hex_str);
  DestFile.print(F("DS18S20_Sensors[3].enabled="));
  DestFile.println(DS18S20[3].enable);
  DestFile.println(F("#"));
  DestFile.println(F("# DS18B20 Temperature sensor (soil measurement 5)"));
  DestFile.print(F("DS18S20_Sensors[4].Id="));
  DestFile.println(DS18S20[4].Id);
  DestFile.print(F("DS18S20_Sensors[4].Addr="));
  hex_str="";
  for (j=0;j<8;j++)
  {
    if(DS18S20[4].Addr[j] < 0x10) hex_str += '0';
    hex_str += String(DS18S20[4].Addr[j], HEX);
  }
  DestFile.println(hex_str);
  DestFile.print(F("DS18S20_Sensors[4].enabled="));
  DestFile.println(DS18S20[4].enable);

  DestFile.println(F("#"));
  DestFile.println(F("# Sensor measurement timer in seconds"));
  DestFile.print(F("SensorTimerValue="));
  DestFile.println(SensorTimerValue);

  DestFile.println(F("#"));
  DestFile.println(F("# Soil Sensor measurement timer in seconds"));
  DestFile.print(F("SoilSensorTimerValue="));
  DestFile.println(SoilSensorTimerValue);
}

spt_data::spt_data()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::spt_data()");
#endif
  ds=new OneWire(OneWire_DigitalInputPin);
  Reset();
}
spt_data::~spt_data()
{
  delete ds;
}
void spt_data::Reset()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::Reset()");
#endif
  //wifiPtr=NULL;
  //MQTT_Client=NULL;
  memset(ConfigFilename,30,1);
  memset(ConfigBackupFilename,30,1);
  strcpy(ConfigFilename,"A1CONFIG.CFG");
  strcpy(ConfigBackupFilename,"A1CONFIG.BKG");
}
void spt_data::Init()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::Init()");
#endif
  int i;
  //wifiPtr=wifiptr;
  //MQTT_Client=mqttclient;
  // Sensors
    // array of OneWire_DS18S20_Sensor sensor - OneWire_DS18S20_Sensor DS18S20_Sensors[5]
      DS18S20_Sensors[0].Init(Config.DS18S20[0].Addr,Config.DS18S20[0].Id,ds/*,wifiPtr*/);
      DS18S20_Sensors[0].SetEnabled(Config.DS18S20[0].enable);
      DS18S20_Sensors[1].Init(Config.DS18S20[1].Addr,Config.DS18S20[1].Id,ds/*,wifiPtr*/);
      DS18S20_Sensors[1].SetEnabled(Config.DS18S20[1].enable);
      DS18S20_Sensors[2].Init(Config.DS18S20[2].Addr,Config.DS18S20[2].Id,ds/*,wifiPtr*/);
      DS18S20_Sensors[2].SetEnabled(Config.DS18S20[2].enable);
      DS18S20_Sensors[3].Init(Config.DS18S20[3].Addr,Config.DS18S20[3].Id,ds/*,wifiPtr*/);
      DS18S20_Sensors[3].SetEnabled(Config.DS18S20[3].enable);
      DS18S20_Sensors[4].Init(Config.DS18S20[4].Addr,Config.DS18S20[4].Id,ds/*,wifiPtr*/);
      DS18S20_Sensors[4].SetEnabled(Config.DS18S20[4].enable);
      
      // array of analog humidity rate sensor - CAnalogSensor RelativeHumidityRate[5]
      RelativeHumidityRate[0].Init(SoilHumiditySensor_1_Id, SoilHumiditySensor_1_AnalogInputPin);// , MQTT_Client);
      RelativeHumidityRate[0].Enable();
      RelativeHumidityRate[1].Init(SoilHumiditySensor_2_Id, SoilHumiditySensor_2_AnalogInputPin);//, MQTT_Client);
      RelativeHumidityRate[1].Enable();
      RelativeHumidityRate[2].Init(SoilHumiditySensor_3_Id, SoilHumiditySensor_3_AnalogInputPin);//, MQTT_Client);
      RelativeHumidityRate[2].Enable();
      RelativeHumidityRate[3].Init(SoilHumiditySensor_4_Id, SoilHumiditySensor_4_AnalogInputPin);//, MQTT_Client);
      RelativeHumidityRate[3].Enable();
      RelativeHumidityRate[4].Init(SoilHumiditySensor_5_Id, SoilHumiditySensor_5_AnalogInputPin);//, MQTT_Client);
      RelativeHumidityRate[4].Enable();
      // Soil Sensor measurement timer
      SoilSensorTimerValue=Config.SoilSensorTimerValue;
#ifdef _SERIAL_VERSION_
Serial.print("spt_data::Init -> SoilSensorTimerValue= { ");
Serial.print(SoilSensorTimer.GetTimerValue());
Serial.print(" ; ");
Serial.print(SoilSensorTimerValue);
#endif 
      SoilSensorTimer.SetTimerValue(SoilSensorTimerValue);
#ifdef _SERIAL_VERSION_
Serial.print(" ; ");
Serial.print(SoilSensorTimer.GetTimerValue());
Serial.println(" }");
#endif 
      SoilSensorTimer.Reset();
      // Sensor measurement timer
      SensorTimerValue=Config.SensorTimerValue;
      SensorTimer.SetTimerValue(SensorTimerValue);
      SensorTimer.Reset();

      
    // Lightness analog sensor
      LightSensor.Init(LightSensor_1_Id, LightSensor_1_AnalogInputPin);//, MQTT_Client);
      LightSensor.Disable();
      
    // array of dhtsensor
      DHTSensors[0].Init(Config.DHT_Sensors[0].Id, Config.DHT_Sensors[0].Pin,Config.DHT_Sensors[0].Type);
      DHTSensors[0].SetEnabled(Config.DHT_Sensors[0].enable);
      DHTSensors[1].Init(Config.DHT_Sensors[1].Id, Config.DHT_Sensors[1].Pin,Config.DHT_Sensors[1].Type);
      DHTSensors[1].SetEnabled(Config.DHT_Sensors[1].enable);
      DHTSensors[2].Init(Config.DHT_Sensors[2].Id, Config.DHT_Sensors[2].Pin,Config.DHT_Sensors[2].Type);
      DHTSensors[2].SetEnabled(Config.DHT_Sensors[2].enable);
      /*
    // Alarm regarding the soil relative humidity rate
      Alarm_RelativeHumidityRate[0].Init(0.25,0.4,0.6,0.75);
      Alarm_RelativeHumidityRate[1].Init(0.25,0.4,0.6,0.75);
      Alarm_RelativeHumidityRate[2].Init(0.25,0.4,0.6,0.75);
      Alarm_RelativeHumidityRate[3].Init(0.25,0.4,0.6,0.75);
      Alarm_RelativeHumidityRate[4].Init(0.25,0.4,0.6,0.75);*/

      Pump_PowerSupply.Init(Config.WaterPump1_PowerSupply.Id,Config.WaterPump1_PowerSupply.Pin, PowerOff);
      SolenoidValve_PowerSupply[0].Init(Config.SolenoidValve[0].Id,Config.SolenoidValve[0].Pin, PowerOff);    
      SolenoidValve_PowerSupply[1].Init(Config.SolenoidValve[1].Id,Config.SolenoidValve[1].Pin, PowerOff);    
      SolenoidValve_PowerSupply[2].Init(Config.SolenoidValve[2].Id,Config.SolenoidValve[2].Pin, PowerOff);    
      SolenoidValve_PowerSupply[3].Init(Config.SolenoidValve[3].Id,Config.SolenoidValve[3].Pin, PowerOff);    
      SolenoidValve_PowerSupply[4].Init(Config.SolenoidValve[4].Id,Config.SolenoidValve[4].Pin, PowerOff);    
      Sensor_PowerSupply.Init(Config.Sensor_PowerSupply.Id,Config.Sensor_PowerSupply.Pin, PowerOff);


  // bouton lancement d'un cycle d'arrosage
  pinMode(Config.WateringCyclePushButton.Pin,INPUT);
  pinMode(Config.ManualPumpPushButton.Pin,INPUT);
  pinMode(Config.WateringFlowerPotPushButton[0].Pin,INPUT);
  pinMode(Config.WateringFlowerPotPushButton[1].Pin,INPUT);
  pinMode(Config.WateringFlowerPotPushButton[2].Pin,INPUT);
  pinMode(Config.WateringFlowerPotPushButton[3].Pin,INPUT);
  pinMode(Config.WateringFlowerPotPushButton[4].Pin,INPUT);

  // ManualPumpTimer
  ManualPumpTimerValue=Config.ManualPumpPushButton.timer;
  ManualPumpTimer.SetTimerValue(ManualPumpTimerValue);
  ManualPumpTimer.Reset();

  for (i=0;i<5;i++)
  {
    FlowerPotWateringTimerValue[i]=Config.WateringFlowerPotPushButton[i].timer;
    FlowerPotWateringTimer[i].SetTimerValue(FlowerPotWateringTimerValue[i]);
    FlowerPotWateringTimer[i].Reset();
    FlowerPotWateringEnable[i] = Config.WateringFlowerPotPushButton[i].enable;
  }

  int j;
  j=0;
  for (i=0;i<5;i++) Sensors[j++]=(CSensor*)&(DS18S20_Sensors[i]);
  for (i=0;i<5;i++) Sensors[j++]=(CSensor*)&(RelativeHumidityRate[i]);
  for (i=0;i<3;i++) Sensors[j++]=(CSensor*)&(DHTSensors[i]);
  Sensors[j++]=(CSensor*)&LightSensor;

  // Alarm and Warning definition
  /*
    SoilRelativeHumidityAlarm.Init(25.0,35.0,65.0,75.0);
    SoilTemperatureAlarm.Init(0.0,5.0,35.0,45.0);
    GreenHouseRelativeHumidityAlarm.Init(25.0,35.0,65.0,75.0);
    GreenHouseTemperatureAlarm.Init(0.0,5.0,35.0,45.0);
    ElectricityBoxRelativeHumidityAlarm.Init(25.0,35.0,65.0,75.0);
    ElectricityBoxTemperatureAlarm.Init(5.0,10.0,45.0,55.0);
    */
}

CSensor* spt_data::FindSensorById(int id)
{
  int i;
  CSensor* sensor;
  sensor=NULL;
  i=0;
  while ((i<14)&&(sensor==NULL))
  {
    if (Sensors[i]->GetId()==id) sensor=Sensors[i];
    i++;
  }
  return sensor;
}


//-----------------------------------------------------------------------------
void spt_data::LoadConfiguration()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::LoadConfiguration()");
#endif
  _loadConfigFile();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void spt_data::SaveConfiguration()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::SaveConfiguration()");
#endif
  if (SD.exists(ConfigFilename)) _copyConfigFile();
  _saveConfigFile();
}  
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void spt_data::_loadConfigFile()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::_loadConfigFile()");
#endif
  File OrigFile;
  //int i;
  //unsigned int val;
  //int line_counter;
  //char * pEnd;
  //String str;
  
  //line_counter=0;
   //if (!SD.exists(ConfigFilename)) _saveConfigFile();
  OrigFile=SD.open(ConfigFilename);
#ifdef _SERIAL_VERSION_
Serial.println("  >> Config._loadConfigFile(OrigFile);");
#endif  
  Config._loadConfigFile(OrigFile);
#ifdef _SERIAL_VERSION_
Serial.println("  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");
#endif  
  OrigFile.close();
#ifdef _SERIAL_VERSION_
Serial.println(".............................. end of spt_data::_loadConfigFile()");
#endif
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void spt_data::_saveConfigFile()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::_saveConfigFile()");
#endif
  File DestFile;
  //unsigned long l_val;
  //unsigned int i_val;
  if (SD.exists(ConfigFilename)) SD.remove(ConfigFilename);

  DestFile=SD.open(ConfigFilename,FILE_WRITE);
  Config._saveConfigFile(DestFile);
  DestFile.close();
#ifdef _SERIAL_VERSION_
Serial.println(".............................. end of spt_data::_saveConfigFile()");
#endif
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void spt_data::_copyConfigFile()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_data::_copyConfigFile()");
#endif
  File OrigFile;
  File DestFile;
  char strbuf[512];
  int i;
  if (SD.exists(ConfigBackupFilename)) SD.remove(ConfigBackupFilename);
  
  OrigFile=SD.open(ConfigFilename);
  DestFile=SD.open(ConfigBackupFilename,FILE_WRITE);
  
  while ((i=OrigFile.available()))
  {
    if (i>512) i=512;
    OrigFile.read(strbuf,i);
    DestFile.write(strbuf,i);
  }
  
  DestFile.close();
  OrigFile.close();
}
//-----------------------------------------------------------------------------
