#include "spt_application2.h"

//-----------------------------------------------------------------------------
// Public Constructor
//-----------------------------------------------------------------------------
spt_application::spt_application()
{
  NFunction=0;

  // Function Id 1
  CommandNames[NFunction]="LaunchWateringCycle";
  CommandFunctions[NFunction++]=&LaunchWateringCycle_Command;

  // Function Id 2
  CommandNames[NFunction]="GetWateringTimer";
  CommandFunctions[NFunction++]=&GetWateringTimer_Command;

  // Function Id 3
  CommandNames[NFunction]="SetWateringTimer";
  CommandFunctions[NFunction++]=&SetWateringTimer_Command;

  // Function Id 4
  CommandNames[NFunction]="LaunchWateringFlowerPot";
  CommandFunctions[NFunction++]=&LaunchWateringFlowerPot_Command;

  // Function Id 5
  CommandNames[NFunction]="GetFlowerPotWateringEnable";
  CommandFunctions[NFunction++]=&GetFlowerPotWateringEnable_Command;

  // Function Id 6
  CommandNames[NFunction]="SetFlowerPotWateringEnable";
  CommandFunctions[NFunction++]=&SetFlowerPotWateringEnable_Command;

  // Function Id 7
  CommandNames[NFunction]="LaunchManualPump";
  CommandFunctions[NFunction++]=&LaunchManualPump_Command;

  // Function Id 8
  CommandNames[NFunction]="GetManualPumpTimer";
  CommandFunctions[NFunction++]=&GetManualPumpTimer_Command;

  // Function Id 9
  CommandNames[NFunction]="SetManualPumpTimer";
  CommandFunctions[NFunction++]=&SetManualPumpTimer_Command;

  // Function Id 10
  CommandNames[NFunction]="GetSoilSensorTimer";
  CommandFunctions[NFunction++]=&GetSoilSensorTimer_Command;

  // Function Id 11
  CommandNames[NFunction]="SetSoilSensorTimer";
  CommandFunctions[NFunction++]=&SetSoilSensorTimer_Command;

  // Function Id 12
  CommandNames[NFunction]="GetSensorEnabled";
  CommandFunctions[NFunction++]=&GetSensorEnabled_Command;

  // Function Id 13
  CommandNames[NFunction]="SetSensorEnabled";
  CommandFunctions[NFunction++]=&SetSensorEnabled_Command;

  // Function Id 14
  CommandNames[NFunction]="GetNetworkStatus";
  CommandFunctions[NFunction++]=&GetNetworkStatus_Command;

  // Function Id 15
  CommandNames[NFunction]="GetProgramState";
  CommandFunctions[NFunction++]=&GetProgramState_Command;

  // Function Id 16
  CommandNames[NFunction]="GetDateTime";
  CommandFunctions[NFunction++]=&GetDateTime_Command;

  // Function Id 17
  CommandNames[NFunction]="SetDateTime";
  CommandFunctions[NFunction++]=&SetDateTime_Command;

  // Function Id 18
  CommandNames[NFunction]="SetSensorMeasurementEnable";
  CommandFunctions[NFunction++]=&SetSensorMeasurementEnable_Command;

  // Function Id 19
  CommandNames[NFunction]="GetSensorMeasurementEnable";
  CommandFunctions[NFunction++]=&GetSensorMeasurementEnable_Command;

  // Function Id 20
  CommandNames[NFunction]="SetRemoteControlState";
  CommandFunctions[NFunction++]=&SetRemoteControlState_Command;

  //CommandNames[NFunction]="GetInternalMuxId";
  //CommandFunctions[NFunction++]=&GetInternalMuxId_Command;

  //CommandNames[NFunction]="SetInternalMuxId";
  //CommandFunctions[NFunction++]=&SetInternalMuxId_Command;

  // NFunction is equal to 20
  Reset();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Reset function
//-----------------------------------------------------------------------------
void spt_application::Reset()
{
  //MQTT_Client=NULL;
  dataPtr=NULL;
  State=ProgramState_Unknown;
  SensorMeasurementEnabled=true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetState function
//-----------------------------------------------------------------------------
int spt_application::GetState()
{
  return State;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public GetState function
//-----------------------------------------------------------------------------
void spt_application::Init(spt_data *dataptr/*,PubSubClient *mqttclient*/)
{
  dataPtr=dataptr;
  //MQTT_Client=mqttclient;
}
//-----------------------------------------------------------------------------

String spt_application::GetStateString(int state)
{
  switch (state)
  {
    case ProgramState_Unknown : return String(F("ProgramState_Unknown"));
    case ProgramState_Setup : return String(F("ProgramState_Setup"));
    case ProgramState_WateringCycle : return String(F("ProgramState_WateringCycle"));
    case ProgramState_ManualPump : return String(F("ProgramState_ManualPump"));
    case ProgramState_WateringFlowerPot : return String(F("ProgramState_WateringFlowerPot"));
    case ProgramState_WateringFlowerPot1 : return String(F("ProgramState_WateringFlowerPot1"));
    case ProgramState_WateringFlowerPot2 : return String(F("ProgramState_WateringFlowerPot2"));
    case ProgramState_WateringFlowerPot3 : return String(F("ProgramState_WateringFlowerPot3"));
    case ProgramState_WateringFlowerPot4 : return String(F("ProgramState_WateringFlowerPot4"));
    case ProgramState_WateringFlowerPot5 : return String(F("ProgramState_WateringFlowerPot5"));
    case ProgramState_WaitingForRemoteCommand : return String(F("ProgramState_WaitingForRemoteCommand"));
    case ProgramState_WaitingForCommand : return String(F("ProgramState_WaitingForCommand"));
    case ProgramState_AutomaticWatering : return String(F("ProgramState_AutomaticWatering"));
  }
  return String(F("ProgramState_Unknownd"));
}

//-----------------------------------------------------------------------------
// Public SetState function
//-----------------------------------------------------------------------------
void spt_application::SetState(int state, bool senddata)
{
  String str_topic;
  str_topic=String("state");
#ifdef _SERIAL_VERSION_
  Serial.println(F("spt_application::SetState----------------"));
  Serial.print(F("current state="));
  Serial.print(State);
  Serial.print(F(" - "));
  Serial.println(GetStateString(State));
  //Serial.println(State);
  Serial.print(F("new state="));
  Serial.print(state);
  Serial.print(F(" - "));
  Serial.println(GetStateString(state));
  //Serial.println(State);
#endif
  String str;
  if (State!=state)
  {
    if (State==ProgramState_Setup)
    {
      PreviousState=ProgramState_WaitingForCommand;
      State=ProgramState_WaitingForCommand;
    }
    else
    {
      PreviousState=State;
      State=state;
      switch (State)
      {
        case ProgramState_Unknown :
        case ProgramState_Setup :
        case ProgramState_WateringCycle :
        case ProgramState_ManualPump :
        case ProgramState_WateringFlowerPot :
        case ProgramState_WateringFlowerPot1 :
        case ProgramState_WateringFlowerPot2 :
        case ProgramState_WateringFlowerPot3 :
        case ProgramState_WateringFlowerPot4 :
        case ProgramState_WateringFlowerPot5 :
        case ProgramState_WaitingForRemoteCommand :
          digitalWrite(BusyLedPin, HIGH);
          SensorMeasurementEnabled=false;
          break;
        case ProgramState_WaitingForCommand :
          SensorMeasurementEnabled=true;
          digitalWrite(BusyLedPin, LOW);
          break;
        case ProgramState_AutomaticWatering :
          SensorMeasurementEnabled=true;
          digitalWrite(BusyLedPin, HIGH);
          break;
      }
    }
    if (senddata)
    {
      //str=BuildXMLString("S",State);
      //wifiPtr->SendData("PR",str);
      str = "{\"s\":";
      str += String(State);
      str += ",\"ps\":";
      str += String(PreviousState);
      str += "}";
      MQTTSerial.println("[" + str_topic + "]" + str);
      /*
      if (MQTT_Client != NULL)
      {
        str="{\"s\":";
        str+=String(State);
        str+=",\"ps\":";
        str+=String(PreviousState);
        str+="}";
        MQTT_Client->publish(str_topic.c_str(),str.c_str());
      }
      */
    }
  }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public Command function
//-----------------------------------------------------------------------------
boolean spt_application::Command(String str_command)
{
  String str;
  bool ok;
  ok=false;
  //int functionID
  // Deserialize the JSON document
  #ifdef JSONVERSION5 
    JsonCmd = JsonCmdObject.parseObject(str_command);
  #endif

  #ifdef JSONVERSION6
    DeserializationError error = deserializeJson(JsonCmd, str_command.c_str());
  #endif

  // Test if parsing succeeds.
  #ifdef JSONVERSION5 
    if (JsonCmd.success())
  #endif
  #ifdef JSONVERSION6
  if (error)
  #endif
  {
#ifdef _SERIAL_VERSION_
Serial.println(F("spt_application::Command: json parse error"));
//Serial.println(error.c_str());
#endif
    return false;
  }
  else
  {
    FunctionID = JsonCmd["f"];

    if ((FunctionID<1)||(FunctionID>NFunction)) return false;

    if ((*CommandFunctions[FunctionID-1])()==CommandFunction_CommandKO)
    {
      str="{\"f\":";
      str+=String(FunctionID);
      str+=",\"a\":";
      str+=String(CommandFunction_CommandKO);
      str+="}";
      //MQTT_Client->publish(MQTT_PublishTopic,str.c_str());
      MQTTSerial.println("[ack]"+str);
#ifdef _SERIAL_VERSION_
Serial.println(F("spt_application::Command: CommandFunction_CommandKO"));
#endif
    }
    else
    {
      str="{\"f\":";
      str+=String(FunctionID);
      str+=",\"a\":";
      str+=String(CommandFunction_CommandOK);
      str+="}";
      //MQTT_Client->publish(MQTT_PublishTopic,str.c_str());
      MQTTSerial.println("[ack]" + str);
      ok=true;
#ifdef _SERIAL_VERSION_
Serial.println(F("spt_application::Command: CommandFunction_CommandOK"));
#endif
    }
  }
  return ok;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//   Function Id 4: LaunchWateringFlowerPot
// Public LaunchWateringFlowerPot_Command function
//-----------------------------------------------------------------------------
int spt_application::LaunchWateringFlowerPot_Command()
{
  bool enable;
  int pot;
  
#ifdef _SERIAL_VERSION_
Serial.println(F("spt_application::LaunchWateringFlowerPot_Command()"));
#endif

  CommandStatus=CommandFunction_CommandOK;
  if (FunctionID!=4) return (CommandStatus=CommandFunction_CommandKO);
  pot = JsonCmd["p"];
  if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return (CommandStatus=CommandFunction_CommandKO);
  if ( (State!=ProgramState_WaitingForCommand) && (State!=(ProgramState_WateringFlowerPot+pot)) ) return (CommandStatus=CommandFunction_CommandKO);
  enable = JsonCmd["e"];
#ifdef _SERIAL_VERSION_
Serial.print(F("  LaunchWateringFlowerPot_Command-> pot="));
Serial.println(pot);
#endif
  if ( enable && (State==ProgramState_WaitingForCommand) )
  {
#ifdef _SERIAL_VERSION_
Serial.println(F("  LaunchWateringFlowerPot_Command-> StartWateringFlowerPot"));
#endif
    StartWateringFlowerPot(pot);
  }
  else
  { 
    if ( !enable && (State==(ProgramState_WateringFlowerPot+pot)) )
    {
#ifdef _SERIAL_VERSION_
Serial.println(F("  LaunchWateringFlowerPot_Command-> StopWateringFlowerPot"));
#endif
      StopWateringFlowerPot();
    }
    else
    {
      return (CommandStatus=CommandFunction_CommandKO);
    }
  }
  return CommandStatus;
  /*CommandStatus=CommandFunction_CommandOK;
  SetState(ProgramState_WateringFlowerPot);
  delay(1000);
  SetState(ProgramState_WaitingForCommand);
  return CommandStatus;*/
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 7: LaunchManualPump
// Public LaunchManualPump_Command function
//-----------------------------------------------------------------------------
int spt_application::LaunchManualPump_Command()
{
  //bool enable;
  CommandStatus=CommandFunction_CommandOK;
  if ( (State!=ProgramState_WaitingForCommand) && (State!=ProgramState_ManualPump) ) return (CommandStatus=CommandFunction_CommandKO);
  if (FunctionID!=7) return (CommandStatus=CommandFunction_CommandKO);
  //enable = JsonCmd["e"];
  if (JsonCmd["e"])
  {
    StartManualPump();
  }
  else
  {
    StopManualPump();
  }
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 8: GetManualPumpTimer
// Public GetManualPumpTimer_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::GetManualPumpTimer_Command()
{
  String str_topic;
  String str;
  CommandStatus=CommandFunction_CommandOK;
  if (FunctionID!=8) return (CommandStatus=CommandFunction_CommandKO);
  str_topic = String("f8");
  str = String(dataPtr->ManualPumpTimer.GetTimerValue());
  MQTTSerial.println("[" + str_topic + "]" + str);
  /*
  if (MQTT_Client!=NULL)
  {
    str_topic=String(MQTT_PublishTopic)+String("/f8");
    str = String(dataPtr->ManualPumpTimer.GetTimerValue());
    MQTT_Client->publish(str_topic.c_str(),str.c_str());
  }
  */
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 9: SetManualPumpTimer
// Public SetManualPumpTimer_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::SetManualPumpTimer_Command()
{
  unsigned int TimerValue;
  //unsigned long timerValue;
  String str_topic;
  String str;
  CommandStatus=CommandFunction_CommandOK;
  TimerValue=JsonCmd["v"];
  if (TimerValue==0) return (CommandStatus=CommandFunction_CommandKO);
  dataPtr->ManualPumpTimerValue = TimerValue;
  dataPtr->ManualPumpTimer.SetTimerValue(TimerValue);
  dataPtr->SaveConfiguration();
  str_topic = String("f8");
  str = String(dataPtr->ManualPumpTimer.GetTimerValue());
  MQTTSerial.println("[" + str_topic + "]" + str);
  /*if (MQTT_Client != NULL)
  {
    str_topic=String(MQTT_PublishTopic)+String("/f8");
    str = String(dataPtr->ManualPumpTimer.GetTimerValue());
    MQTT_Client->publish(str_topic.c_str(),str.c_str());
  }*/
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 1: LaunchWateringCycle
// Public LaunchWateringCycle_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::LaunchWateringCycle_Command()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_application::LaunchWateringCycle_Command()");
#endif
  bool enable;
  CommandStatus = CommandFunction_CommandKO;
  enable=JsonCmd["e"];
#ifdef _SERIAL_VERSION_
Serial.print("  > FunctionID=");
Serial.println(FunctionID);
Serial.print("  > enable=");
Serial.println(enable);
Serial.print("  > state=");
Serial.println(State);
//Serial.println(GetStateString(State));
#endif
  if (FunctionID != 1) return (CommandStatus = CommandFunction_CommandKO);
  if ( (State==ProgramState_WaitingForCommand) && (enable) )
  {
    StartWateringCycle();
    delay(1000);
    return (CommandStatus = CommandFunction_CommandOK);
  }

  if ( (State==ProgramState_WateringCycle) && (!enable) )
  {
    StopWateringCycle();
    delay(1000);
    return (CommandStatus = CommandFunction_CommandOK);
  }
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 3: SetWateringTimer
// Public SetWateringTimer_Command function
//-----------------------------------------------------------------------------
int spt_application::SetWateringTimer_Command()
{
	unsigned int TimerValue;
	int pot;
	String str, str_topic;

	CommandStatus = CommandFunction_CommandOK;

	if (State != ProgramState_WaitingForCommand) return (CommandStatus = CommandFunction_CommandKO);

	if (FunctionID != 3) return (CommandStatus = CommandFunction_CommandKO);

	pot = JsonCmd["p"];
	if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return (CommandStatus = CommandFunction_CommandKO);

	TimerValue = JsonCmd["v"];
	if (TimerValue == 0) return (CommandStatus = CommandFunction_CommandKO);
	dataPtr->FlowerPotWateringTimerValue[pot-1] = TimerValue;
  dataPtr->FlowerPotWateringTimer[pot - 1].SetTimerValue(TimerValue);
  dataPtr->SaveConfiguration();
  str_topic = String("f2p") + String(pot);
  str = String(dataPtr->FlowerPotWateringTimer[pot - 1].GetTimerValue());
  MQTTSerial.println("[" + str_topic + "]" + str);
  /*if (MQTT_Client != NULL)
	{
		str_topic = String(MQTT_PublishTopic) + String("/f2p") + String(pot);
        str = String(dataPtr->FlowerPotWateringTimer[pot - 1].GetTimerValue());
		MQTT_Client->publish(str_topic.c_str(), str.c_str());
	}*/
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 2: GetWateringTimer
// Public GetWateringTimer_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::GetWateringTimer_Command()
{
  int pot;
  String str, str_topic;

  CommandStatus = CommandFunction_CommandOK;

  if (State != ProgramState_WaitingForCommand) return (CommandStatus = CommandFunction_CommandKO);

  if (FunctionID != 2) return (CommandStatus = CommandFunction_CommandKO);

  pot = JsonCmd["p"];

  if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return (CommandStatus = CommandFunction_CommandKO);

  str_topic = String("f2p") + String(pot);
  str = String(dataPtr->FlowerPotWateringTimer[pot - 1].GetTimerValue());
  MQTTSerial.println("[" + str_topic + "]" + str);
  /*if (MQTT_Client != NULL)
  {
    str_topic = String(MQTT_PublishTopic) + String("/f2p")+String(pot);
    str = String(dataPtr->FlowerPotWateringTimer[pot-1].GetTimerValue()); 
    MQTT_Client->publish(str_topic.c_str(), str.c_str());
  }*/
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 6: SetFlowerPotWateringEnable
// Public SetFlowerPotWateringEnable_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::SetFlowerPotWateringEnable_Command()
{
  int enable;
  int pot;
  String str, str_topic;

  CommandStatus = CommandFunction_CommandOK;

  if (State != ProgramState_WaitingForCommand) return (CommandStatus = CommandFunction_CommandKO);

  if (FunctionID != 6) return (CommandStatus = CommandFunction_CommandKO);

  pot = JsonCmd["p"];

  if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return (CommandStatus = CommandFunction_CommandKO);

  enable = JsonCmd["e"];
  
  if (enable==0) dataPtr->FlowerPotWateringEnable[pot - 1] = false; else dataPtr->FlowerPotWateringEnable[pot - 1] = true; 
  dataPtr->SaveConfiguration();

  str_topic = String("f5p") + String(pot);
  str = String(dataPtr->FlowerPotWateringEnable[pot - 1]);
  MQTTSerial.println("[" + str_topic + "]" + str);

  /*if (MQTT_Client != NULL)
  {
      str_topic = String(MQTT_PublishTopic) + String("/f5p") + String(pot);
      str = String(dataPtr->FlowerPotWateringEnable[pot - 1]);
      MQTT_Client->publish(str_topic.c_str(), str.c_str());
  }*/

  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 5: GetFlowerPotWateringEnable
// Public GetFlowerPotWateringEnable_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::GetFlowerPotWateringEnable_Command()
{
  int pot;
  String str, str_topic;

    CommandStatus = CommandFunction_CommandOK;

    if (State != ProgramState_WaitingForCommand) return (CommandStatus = CommandFunction_CommandKO);

    if (FunctionID != 5) return (CommandStatus = CommandFunction_CommandKO);

    pot = JsonCmd["p"];

    if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return (CommandStatus = CommandFunction_CommandKO);

    str_topic = String("f5p") + String(pot);
    str = String(dataPtr->FlowerPotWateringEnable[pot - 1]);
    MQTTSerial.println("[" + str_topic + "]" + str);
    /*if (MQTT_Client != NULL)
    {
        str_topic = String(MQTT_PublishTopic) + String("/f5p") + String(pot);
        str = String(dataPtr->FlowerPotWateringEnable[pot - 1]);
        MQTT_Client->publish(str_topic.c_str(), str.c_str());
    }*/

    return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 11: SetSoilSensorTimer
// Public SetSoilSensorTimer_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::SetSoilSensorTimer_Command()
{
  unsigned int TimerValue;
  String str, str_topic;

  CommandStatus = CommandFunction_CommandOK;

  if (State != ProgramState_WaitingForCommand) return (CommandStatus = CommandFunction_CommandKO);

  if (FunctionID != 11) return (CommandStatus = CommandFunction_CommandKO);

  TimerValue = JsonCmd["v"];
  if (TimerValue == 0) return (CommandStatus = CommandFunction_CommandKO);
  dataPtr->SoilSensorTimerValue = TimerValue;
  dataPtr->SoilSensorTimer.SetTimerValue(TimerValue);
  dataPtr->SaveConfiguration();


  str_topic = String("f10");
  str = String(dataPtr->SoilSensorTimer.GetTimerValue());
  MQTTSerial.println("[" + str_topic + "]" + str);

  /*if (MQTT_Client != NULL)
  {
    str_topic = String(MQTT_PublishTopic) + String("/f10");
    str = String(dataPtr->SoilSensorTimer.GetTimerValue());
    MQTT_Client->publish(str_topic.c_str(), str.c_str());
  }*/
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 10: GetSoilSensorTimer
// Public GetSoilSensorTimer_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::GetSoilSensorTimer_Command()
{
  String str_topic;
  String str;
  CommandStatus=CommandFunction_CommandOK;
  if (FunctionID!=10) return (CommandStatus=CommandFunction_CommandKO);
  str_topic = String("f10");
  str = String(dataPtr->SoilSensorTimer.GetTimerValue());
  MQTTSerial.println("[" + str_topic + "]" + str);
  /*if (MQTT_Client != NULL)
  {
    str_topic=String(MQTT_PublishTopic)+String("/f10");
    str = String(dataPtr->SoilSensorTimer.GetTimerValue());
    MQTT_Client->publish(str_topic.c_str(),str.c_str());
  }*/
  return CommandStatus;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
//   Function Id 12: GetSensorEnabled
// Public GetSensorEnabled_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::GetSensorEnabled_Command()
{
  int sensor_id;
  CSensor *sensor;
  String str, str_topic;

    CommandStatus = CommandFunction_CommandOK;

    if (FunctionID != 12) return (CommandStatus = CommandFunction_CommandKO);

    sensor_id = JsonCmd["s"];

    sensor=dataPtr->FindSensorById(sensor_id);

    if (sensor==NULL) return (CommandStatus = CommandFunction_CommandKO);

    str_topic = String("f12s") + String(sensor_id);
    str = String(sensor->IsEnabled());
    MQTTSerial.println("[" + str_topic + "]" + str);
    /*if (MQTT_Client != NULL)
    {
        str_topic = String(MQTT_PublishTopic) + String("/f5p") + String(pot);
        str = String(dataPtr->FlowerPotWateringEnable[pot - 1]);
        MQTT_Client->publish(str_topic.c_str(), str.c_str());
    }*/

    return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 13: SetSensorEnabled
// Public SetSensorEnabled_Command function
// Creation Date: 2017/09/03
//-----------------------------------------------------------------------------
int spt_application::SetSensorEnabled_Command()
{
  int sensor_id;
  bool enable;
  CSensor *sensor;
  String str, str_topic;

    CommandStatus = CommandFunction_CommandOK;

    if (FunctionID != 13) return (CommandStatus = CommandFunction_CommandKO);

    sensor_id = JsonCmd["s"];

    sensor=dataPtr->FindSensorById(sensor_id);

    if (sensor==NULL) return (CommandStatus = CommandFunction_CommandKO);

    enable = JsonCmd["e"];

    if (enable) sensor->Enable(); else sensor->Disable();

    str_topic = String("f12s") + String(sensor_id);
    str = String(sensor->IsEnabled());
    MQTTSerial.println("[" + str_topic + "]" + str);
    /*if (MQTT_Client != NULL)
    {
        str_topic = String(MQTT_PublishTopic) + String("/f5p") + String(pot);
        str = String(dataPtr->FlowerPotWateringEnable[pot - 1]);
        MQTT_Client->publish(str_topic.c_str(), str.c_str());
    }*/

    return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 14: GetNetworkStatus
// Public GetNetworkStatus_Command function
//-----------------------------------------------------------------------------
int spt_application::GetNetworkStatus_Command()
{
  CommandStatus=CommandFunction_CommandOK;
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 15: GetProgramState
// Public GetProgramState_Command function
//-----------------------------------------------------------------------------
int spt_application::GetProgramState_Command()
{
  String str, str_topic;

  CommandStatus = CommandFunction_CommandOK;

  if (FunctionID != 13) return (CommandStatus = CommandFunction_CommandKO);

  str_topic = String("f15");
  str = String(State);
  MQTTSerial.println("[" + str_topic + "]" + str);

  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 16: GetDateTime
// Public GetProgramDateTime_Command function
//-----------------------------------------------------------------------------
int spt_application::GetDateTime_Command()
{
  CommandStatus=CommandFunction_CommandOK;
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 17: SetDateTime
// Public SetProgramDateTime_Command function
//-----------------------------------------------------------------------------
int spt_application::SetDateTime_Command()
{
  CommandStatus=CommandFunction_CommandOK;
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 18: SetSensorMeasurementEnable
// Public SetSensorMeasurementEnable_Command function
//-----------------------------------------------------------------------------
int spt_application::SetSensorMeasurementEnable_Command()
{
  CommandStatus=CommandFunction_CommandOK;
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 19: GetSensorMeasurementEnable
// Public GetSensorMeasurementEnable_Command function
//-----------------------------------------------------------------------------
int spt_application::GetSensorMeasurementEnable_Command()
{
  CommandStatus=CommandFunction_CommandOK;
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//   Function Id 20: SetRemoteControlState
// Public SetRemoteControlState_Command function
//-----------------------------------------------------------------------------
int spt_application::SetRemoteControlState_Command()
{
  CommandStatus=CommandFunction_CommandOK;
  return CommandStatus;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public StartManualPump function
//-----------------------------------------------------------------------------
boolean spt_application::StartManualPump()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_application::StartManualPump()");
#endif
  String str_topic;
  // check if Program State is coherent
    if (State!=ProgramState_WaitingForCommand)
    {
#ifdef _SERIAL_VERSION_
Serial.println("  > function not allowed: State!=ProgramState_WaitingForCommand");
#endif
      return false;
    }
  // Change Program State
    SetState(ProgramState_ManualPump);
    dataPtr->ManualPumpTimer.Reset();
    dataPtr->Pump_PowerSupply.On();

    str_topic = String("f7");
    MQTTSerial.println("[" + str_topic + "]on");

    /*if (MQTT_Client!=NULL)
    {
      str_topic=String(MQTT_PublishTopic)+String("/f7");
      MQTT_Client->publish(str_topic.c_str(),"on");
#ifdef _SERIAL_VERSION_
Serial.println("  > send MQTT message : Manual Pump ON");
#endif
    }*/
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public StopManualPump function
//-----------------------------------------------------------------------------
boolean spt_application::StopManualPump()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_application::StopManualPump()");
#endif
  String str_topic;
  // check if Program State is coherent
    if (State!=ProgramState_ManualPump)
    {
#ifdef _SERIAL_VERSION_
Serial.println("  > function not allowed: State!=ProgramState_ManualPump");
#endif
      return false;
    }
  // Change Program State
    dataPtr->Pump_PowerSupply.Off();
  // temporary (to be integrated to PowerSupply class ?
    str_topic = String("f7");
    MQTTSerial.println("[" + str_topic + "]off");
    /*if (MQTT_Client != NULL)
    {
      str_topic=String(MQTT_PublishTopic)+String("/f7");
      MQTT_Client->publish(str_topic.c_str(),"off");
#ifdef _SERIAL_VERSION_
Serial.println("  > send MQTT message : Manual Pump OFF");
#endif
    }*/
    SetState(ProgramState_WaitingForCommand);

  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public CheckManualPumpTimeout function
//-----------------------------------------------------------------------------
boolean spt_application::CheckManualPumpTimeout()
{
#ifdef _SERIAL_VERSION_
//Serial.println("spt_application::CheckManualPumpTimeout()");
#endif
  // check if Program State is coherent
    if (State!=ProgramState_ManualPump) 
    {
#ifdef _SERIAL_VERSION_
Serial.println("  > function not allowed: State!=ProgramState_ManualPump");
#endif
      return false;
    }
  // check Manual pump timer
    if (dataPtr->ManualPumpTimer.IsDone()) 
    {
#ifdef _SERIAL_VERSION_
Serial.print("  > dataPtr->ManualPumpTimer GetCurrentValue: ");
Serial.println(dataPtr->ManualPumpTimer.GetCurrentValue());
Serial.println("  > dataPtr->ManualPumpTimer is done");
#endif
      StopManualPump();
    }
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public StartWateringCycle function
//-----------------------------------------------------------------------------
boolean spt_application::StartWateringCycle()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_application::StartWateringCycle()");
#endif
  // check if Program State is coherent
    if (State!=ProgramState_WaitingForCommand) return false;
  // Change Program State
    SetState(ProgramState_WateringCycle);
    //MQTTSerial.println("[f1]on");
    str_topic = String("PS") + String(2000);
    str_payload = "on";
    MQTTSerial.print("[" + str_topic + "]" + str_payload);

    str_topic = String("f1");
    str_payload = "on";
    MQTTSerial.println("[" + str_topic + "]" + str_payload);
    //MQTTSerial.println("[PS2000]on");
    Step=0;
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public StopWateringCycle function
//-----------------------------------------------------------------------------
boolean spt_application::StopWateringCycle()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_application::StopWateringCycle()");
#endif
  //int i;
  // check if Program State is coherent
    if (State!=ProgramState_WateringCycle) return false;
  // Change Program State
    dataPtr->Pump_PowerSupply.Off();
    //for (i=0;i<5;i++) dataPtr->SolenoidValve_PowerSupply[i].Off();
    if (Step>=1 && Step<=5) dataPtr->SolenoidValve_PowerSupply[Step-1].Off();
    //MQTTSerial.println("[f1]off");
    //MQTTSerial.println("[PS2000]off");
    str_topic = String("f1");
    str_payload = "off";
    MQTTSerial.println("[" + str_topic + "]" + str_payload);

    str_topic = String("PS") + String(2000);
    str_payload = "off";
    MQTTSerial.print("[" + str_topic + "]" + str_payload);
    SetState(ProgramState_WaitingForCommand);
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public NextWateringCycleStep function
//-----------------------------------------------------------------------------
boolean spt_application::NextWateringCycleStep()
{
#ifdef _SERIAL_VERSION_
Serial.println("spt_application::NextWateringCycleStep()");
#endif
  boolean IncrementStep;
  IncrementStep=false;
#ifdef _SERIAL_VERSION_
Serial.println("spt_application::NextWateringCycleStep----------------");
Serial.print("current step=");
Serial.println(Step);
Serial.print("ProgramState=");
Serial.println(State);
#endif

  if ((Step<0) || (Step>5)) return false;
  if (Step==0)
  {
#ifdef _SERIAL_VERSION_
Serial.println("case step 0");
#endif
    // Start of the watering cycle: water flower pot 1
    if (dataPtr->FlowerPotWateringEnable[0])
    {
#ifdef _SERIAL_VERSION_
Serial.println("FlowerPotWatering=enabled");
#endif
      // power on solenoidValve 1
      dataPtr->SolenoidValve_PowerSupply[0].On();
      // pump power on
      dataPtr->Pump_PowerSupply.On();
      // reset timer for the flower pot 1
      dataPtr->FlowerPotWateringTimer[0].Reset();
    }
    // step incrementation
#ifdef _SERIAL_VERSION_
Serial.println("IncrementStep=true");
#endif
    IncrementStep=true;
  }
  if ((Step>=1)&&(Step<=4))
  {
    // Check flower pot 1 timer
    if (dataPtr->FlowerPotWateringEnable[Step-1])
    {
      if (dataPtr->FlowerPotWateringTimer[Step-1].IsDone())
      { // end of the flower pot 1 watering
        // pump power off
        dataPtr->Pump_PowerSupply.Off();
        // power off solenoidValve 1
        dataPtr->SolenoidValve_PowerSupply[Step-1].Off();
        if (dataPtr->FlowerPotWateringEnable[Step])
        {
          // power on solenoidValve 2
          dataPtr->SolenoidValve_PowerSupply[Step].On();
          // pump power on
          dataPtr->Pump_PowerSupply.On();
          // reset timer for the flower pot 2
          dataPtr->FlowerPotWateringTimer[Step].Reset();
        }
        // step incrementation
        IncrementStep=true;
      }
    }
    else
    {
      if (dataPtr->FlowerPotWateringEnable[Step])
      {
        // power on solenoidValve 2
        dataPtr->SolenoidValve_PowerSupply[Step].On();
        // pump power on
        dataPtr->Pump_PowerSupply.On();
        // reset timer for the flower pot 2
        dataPtr->FlowerPotWateringTimer[Step].Reset();
        // step incrementation
      }
      IncrementStep=true;
    }
  }
  if (Step==5)
  {
    if (dataPtr->FlowerPotWateringEnable[4])
    {
      // Check flower pot 5 timer
      if (dataPtr->FlowerPotWateringTimer[4].IsDone())
      { // end of the flower pot 5 watering
        // pump power off
        dataPtr->Pump_PowerSupply.Off();
        // power off solenoidValve 5
        dataPtr->SolenoidValve_PowerSupply[4].Off();
        // Change Program State
        SetState(ProgramState_WaitingForCommand);
        // step incrementation
        IncrementStep=true;
      }
    }
    else
    {
      // Change Program State
      //MQTTSerial.println("[f1]off");
      //MQTTSerial.println("[PS2000]off");
      //MQTTSerial.println("[f1]off");
      str_topic = String("f1");
      str_payload = "off";
      MQTTSerial.println("[" + str_topic + "]" + str_payload);

      str_topic = String("PS") + String(2000);
      str_payload = "off";
      MQTTSerial.print("[" + str_topic + "]" + str_payload);
      SetState(ProgramState_WaitingForCommand);
    }
  }
  if (IncrementStep) Step++;
#ifdef _SERIAL_VERSION_
Serial.print("final step=");
Serial.println(Step);
#endif
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public StartWateringFlowerPot function
//-----------------------------------------------------------------------------
boolean spt_application::StartWateringFlowerPot(int pot)
{
#ifdef _SERIAL_VERSION_
Serial.print(F("spt_application::StartWateringFlowerPot("));
Serial.print(pot);
Serial.println(F(")"));
#endif
  String str_topic;
  // check input flower pot number : pot
    if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return false;
  // check if Program State is coherent
    //if (State!=(ProgramState_WateringPlanterBox+pot)) return false;
    if (State!=ProgramState_WaitingForCommand) return false;
    if (!dataPtr->FlowerPotWateringEnable[pot-1]) return false;
  // Change program state
    SetState(ProgramState_WateringFlowerPot+pot,true);
  // Reset Timer
    dataPtr->FlowerPotWateringTimer[pot-1].Reset();
#ifdef _SERIAL_VERSION_
Serial.print(F("-> Timer="));
Serial.println(dataPtr->FlowerPotWateringTimer[pot-1].GetTimerValue());
#endif

  // power on Solenoid Valve
    dataPtr->SolenoidValve_PowerSupply[pot-1].On();

    str_topic = String("f4p") + String(pot);
    MQTTSerial.println("[" + str_topic + "]on");

    /*if (MQTT_Client != NULL)
    {
      str_topic=String(MQTT_PublishTopic)+String("/f4p")+String(pot);
      MQTT_Client->publish(str_topic.c_str(),"on");
    }*/
  // power on pump
    dataPtr->Pump_PowerSupply.On();
    str_topic = String("f7");
    MQTTSerial.println("[" + str_topic + "]on");
    /*if (MQTT_Client != NULL)
    {
      str_topic=String(MQTT_PublishTopic)+String("/f7");
      MQTT_Client->publish(str_topic.c_str(),"on");
    }*/
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public CheckWateringFlowerPotTimeout function
//-----------------------------------------------------------------------------
boolean spt_application::CheckWateringFlowerPotTimeout()
{
#ifdef _SERIAL_VERSION_
Serial.println(F("spt_application::CheckWateringFlowerPotTimeout()"));
#endif
  int pot;
  // check if Program State is coherent
  pot=State-ProgramState_WateringFlowerPot;
#ifdef _SERIAL_VERSION_
Serial.print(F("  CheckWateringFlowerPotTimeout -> pot="));
Serial.println(pot);
Serial.print(F("  CheckWateringFlowerPotTimeout -> FlowerPotWateringTimer.IsDone="));
Serial.println(dataPtr->FlowerPotWateringTimer[pot-1].IsDone());
#endif
  if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return false;
  // check Manual pump timer
    if (dataPtr->FlowerPotWateringTimer[pot-1].IsDone()) StopWateringFlowerPot();
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public StopWateringFlowerPot function
//-----------------------------------------------------------------------------
boolean spt_application::StopWateringFlowerPot()
{
  String str_topic;
  int pot=State-ProgramState_WateringFlowerPot;
  if ((pot<POT_NUMBER_MIN) || (pot>POT_NUMBER_MAX)) return false;
  dataPtr->Pump_PowerSupply.Off();
  str_topic = String("f7");
  MQTTSerial.println("[" + str_topic + "]off");
  /*if (MQTT_Client != NULL)
    {
      str_topic=String(MQTT_PublishTopic)+String("/f7");
      MQTT_Client->publish(str_topic.c_str(),"off");
    }*/
  dataPtr->SolenoidValve_PowerSupply[pot-1].Off();
  str_topic = String("f4p") + String(pot);
  MQTTSerial.println("[" + str_topic + "]on");
  /*if (MQTT_Client != NULL)
    {
      str_topic=String(MQTT_PublishTopic)+String("/f4p")+String(pot);
      MQTT_Client->publish(str_topic.c_str(),"off");
    }*/
  SetState(PreviousState);
  // temporary (to be integrated to PowerSupply class ?
  return true;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public OtherSensorMeasurement function
//-----------------------------------------------------------------------------
void spt_application::OtherSensorMeasurement()
{
#ifdef _SERIAL_VERSION_
Serial.println(F("spt_application::OtherSensorMeasurement()"));
#endif
  float temperature, relative_humidity;
  //float Light;
  int i;
  digitalWrite(BusyLedPin, HIGH);

  for (i=0;i<3;i++)
  {
    // Measurement electrical box temperature and relative humidity
    if (dataPtr->DHTSensors[i].IsEnabled())
    {
      dataPtr->DHTSensors[i].ReadData(&temperature,&relative_humidity);
    }
    else
    {
        temperature=-999.9;
        relative_humidity=-999.9;
    }
  }
  /*if (dataPtr->LightSensor.IsEnabled())
  {
    Light=dataPtr->LightSensor.ReadData(true);
  }
  else
  {
    Light=-999.9;
  }*/
  dataPtr->SensorTimer.Reset();
  digitalWrite(BusyLedPin, LOW);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public IsSensorMeasurementEnabled function
//-----------------------------------------------------------------------------
bool spt_application::IsSensorMeasurementEnabled()
{
  return SensorMeasurementEnabled;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public SoilSensorMeasurement function
//-----------------------------------------------------------------------------
void spt_application::SoilSensorMeasurement()
{
#ifdef _SERIAL_VERSION_
Serial.println(F("spt_application::OtherSensorMeasurement()"));
#endif
  digitalWrite(BusyLedPin, HIGH);
  float temperature, relative_humidity;
  int i;
  // switch on sensor power supply
    dataPtr->Sensor_PowerSupply.On();
  // wait for sensor stabilisation
    delay(5000);
  // Measurement flower pot 1 to 5
    for (i=0;i<5;i++)
    {
      if (dataPtr->DS18S20_Sensors[i].IsEnabled())
      {
        dataPtr->DS18S20_Sensors[i].startTemperatureMeasure();
        temperature=dataPtr->DS18S20_Sensors[i].Read(true);
      }
      else
      {
        temperature=-999.9;
      }
      if (dataPtr->RelativeHumidityRate[i].IsEnabled())
      {
        relative_humidity=dataPtr->RelativeHumidityRate[i].ReadData(true);
      }
      else
      {
        relative_humidity=-999.9;
      }
    }
  // switch off sensor power supply
    dataPtr->Sensor_PowerSupply.Off();
  // reset soil sensor timer
    dataPtr->SoilSensorTimer.Reset();
  digitalWrite(BusyLedPin, LOW);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Public IsSensorMeasurementEnabled function
//-----------------------------------------------------------------------------
bool spt_application::IsSoilSensorMeasurementEnabled()
{
  return true;
}
//-----------------------------------------------------------------------------
