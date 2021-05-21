#ifndef SPT_APPLICATION2_H
#define SPT_APPLICATION2_H

/////////////////////////////////////////////////////////////////
// Autor: Stephane PARIZET
// Version: 0.1(.01) / date: 2020/05/09
//
// ProgramState_WaitingForRemoteCommand program state added (disable sensor measurement)
// SetSensorMeasurementEnable added (Function Id 18)
// Function Id 19: GetSensorMeasurementEnable added (Function Id 19)
// Function Id 20: SetRemoteControlState added (Function Id 20)
// Sensor measurement management (logic changed)
//
// Version: 0.1(.01) / date: 2020/05/09
// Creation Date
/////////////////////////////////////////////////////////////////

#include "spt_definition.h"
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "spt_data.h"

// Application State ------------------------------------------------
#define ProgramState_Unknown -1
#define ProgramState_Setup 0
#define ProgramState_WaitingForCommand 1   // sensor measurement enabled
#define ProgramState_WateringCycle 2       // sensor measurement enabled
#define ProgramState_ManualPump 3          // sensor measurement enabled
#define ProgramState_AutomaticWatering 4   // sensor measurement enabled
#define ProgramState_WateringFlowerPot 10  // sensor measurement enabled
#define ProgramState_WateringFlowerPot1 11 // sensor measurement enabled
#define ProgramState_WateringFlowerPot2 12 // sensor measurement enabled
#define ProgramState_WateringFlowerPot3 13 // sensor measurement enabled
#define ProgramState_WateringFlowerPot4 14 // sensor measurement enabled
#define ProgramState_WateringFlowerPot5 15 // sensor measurement enabled
#define ProgramState_WaitingForRemoteCommand 16 // sensor measurement disabled // TO BE CHANGED TO 5 ?

#define CommandFunction_CommandOK 1
#define CommandFunction_CommandKO 0
#define CommandFunction_NotCommand -1

// Command
//   <G>: Command (Greenhouse command)
//
// Fonctions
//   <F>: Function id (int)
//
// Function parameters
//   <C>: command count (int)
//   <D>: Date Time (string format: "20yy-MM-ddThh:mm:ss")
//   <Id>: Id (Sensor, powersupply, ...)
//   <E>: Enable (0 or 1)
//   <Ti>: Timer Value in second (float)
//   <P>: FlowerPot number (int)
//   <L>: light level (float)
//   <NS>: Network Status
//
// Events:
//   <AS>: Analog Sensor Event
//   <PS>: Power Supply Event
//   <PR>: Program Event
//
// Event parameters
//   <D>: Event Date Time
//   <Id>: Id (Sensor, powersupply, ...)
//   <Te>: temperature in degC (float)
//   <Hu>: humidity rate in % (float)
//   <L>: light level (float)
//   <S>: Program State
//   <ME>: Sensor measurement enable
//   <ST>: Sensor Type
//   <SST>: Sensor Sub Type
//   <V>: Sensor Value

// List of functions
//   Function Id 1: LaunchWateringCycle
//   Function Id 2: GetWateringTimer
//   Function Id 3: SetWateringTimer
//   Function Id 4: LaunchWateringFlowerPot
//   Function Id 5: GetFlowerPotWateringEnable
//   Function Id 6: SetFlowerPotWateringEnable
//   Function Id 7: LaunchManualPump
//   Function Id 8: GetManualPumpTimer
//   Function Id 9: SetManualPumpTimer
//   Function Id 10: GetSoilSensorTimer
//   Function Id 11: SetSoilSensorTimer
//   Function Id 12: GetSensorEnabled
//   Function Id 13: SetSensorEnabled
//   Function Id 14: GetNetworkStatus
//   Function Id 15: GetProgramState
//   Function Id 16: GetDateTime
//   Function Id 17: SetDateTime
//   Function Id 18: SetSensorMeasurementEnable
//   Function Id 19: GetSensorMeasurementEnable
//   Function Id 20: SetRemoteControlState
//   Function Id 21: SetAutomaticWateringState // TO BE DEVELOPPED

typedef int (*CommandFunctionPtr)();

#define MAX_COMMAND_FUNCTION 20

class spt_application
{
  public:
    // Constructor
    spt_application();
    // Reset function
    void Reset();
    // Class initialisation function
    void Init(spt_data *data/*,PubSubClient *mqttclient*/);
    // Command function (command received from MQTT Subscription
    //boolean Command(String str_command, uint8_t mux_id);
    boolean Command(String str_command);
    static String GetStateString(int state);

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Launch Soil Sensor Measurment
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static void SoilSensorMeasurement();
    bool IsSoilSensorMeasurementEnabled();
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Launch Other Sensor Measurement
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static void OtherSensorMeasurement();
    bool IsSensorMeasurementEnabled();
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Program state management function
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static int GetState();
    static void SetState(int state, bool senddata=true);
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Command function table
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    CommandFunctionPtr CommandFunctions[MAX_COMMAND_FUNCTION];
    String CommandNames[MAX_COMMAND_FUNCTION];
    int NFunction;
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Manual pump functions
    //  -> StartManualPump
    //  -> StopManualPump
    //  -> CheckManualPumpTimeout
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Manual pump function
    static boolean StartManualPump();
    static boolean StopManualPump();
    static boolean CheckManualPumpTimeout();
    //---------------------------------------------------------------

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Watering functions
    //  -> StartWateringCycle
    //  -> StopWateringCycle
    //  -> NextWateringCycleStep
    //  -> StartWateringFlowerPot
    //  -> StopWateringFlowerPot
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Watering Cycle function
    static boolean StartWateringCycle();
    static boolean StopWateringCycle();
    static boolean NextWateringCycleStep();
    // Watering Flower Pot function
    static boolean StartWateringFlowerPot(int pot);
    static boolean StopWateringFlowerPot();
    static boolean CheckWateringFlowerPotTimeout();
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Watering Command functions
    //  -> LaunchWateringCycle
    //  -> LaunchWateringFlowerPot
    //  -> SetWateringTimer
    //  -> GetWateringTimer
    //  -> SetFlowerPotWateringEnable
    //  -> GetFlowerPotWateringEnable
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static int LaunchWateringCycle_Command();
    //---------------------------------------------------------------
    static int LaunchWateringFlowerPot_Command();
    //---------------------------------------------------------------
    static int SetWateringTimer_Command();
    //---------------------------------------------------------------
	  static int GetWateringTimer_Command();
    //---------------------------------------------------------------
    static int SetFlowerPotWateringEnable_Command();
    //---------------------------------------------------------------
    static int GetFlowerPotWateringEnable_Command();
    //---------------------------------------------------------------

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Manual pump Command functions
    //  -> LaunchManualPump: power on/off the pump
    //  -> GetManualPumpTimer: Get the timer value of the manual pump mode
    //  -> SetManualPumpTimer: Set the timer value of the manual pump mode
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static int LaunchManualPump_Command();
    //---------------------------------------------------------------
    static int GetManualPumpTimer_Command();
    //---------------------------------------------------------------
    static int SetManualPumpTimer_Command();
    //---------------------------------------------------------------

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Soil Sensor Command functions
    //  -> SetSoilSensorTimer: set time between two measurements
    //  -> GetSoilSensorTimer: get time between two measurements
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static int SetSoilSensorTimer_Command();
    //---------------------------------------------------------------
    static int GetSoilSensorTimer_Command();
    //---------------------------------------------------------------

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // Sensor Enable Command functions
    //  -> SetSoilSensorTimer: set time between two measurements
    //  -> GetSoilSensorTimer: get time between two measurements
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static int SetSensorEnabled_Command();
    //---------------------------------------------------------------
    static int GetSensorEnabled_Command();
    //---------------------------------------------------------------

    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // General Command functions
    //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    static int GetNetworkStatus_Command();
    //---------------------------------------------------------------
    static int GetProgramState_Command();
    //---------------------------------------------------------------
    static int GetDateTime_Command();
    //---------------------------------------------------------------
    static int SetDateTime_Command();
    //---------------------------------------------------------------
    static int SetSensorMeasurementEnable_Command();
    //---------------------------------------------------------------
    static int GetSensorMeasurementEnable_Command();
    //---------------------------------------------------------------
    static int SetRemoteControlState_Command();
    //---------------------------------------------------------------
    //static int GetInternalMuxId_Command();
    //---------------------------------------------------------------
    //static int SetInternalMuxId_Command();
    //---------------------------------------------------------------

  protected:
    // pointer to MQTT
      //static PubSubClient *MQTT_Client;
    // Program State
      static int State;
      static int PreviousState;
      static bool SensorMeasurementEnabled;
      static int CommandStatus;
    // temporary char buffer
      static char str_temp[255];
    // JSON Document
      // Json 5
      #ifdef JSONVERSION5
        static StaticJsonBuffer<512> JsonCmdObject;
        static JsonObject& JsonCmd;
      #endif
      // Json 6
      #ifdef JSONVERSION6
        static StaticJsonDocument<255> JsonCmd;
      #endif

    static int FunctionID;
    static spt_data *dataPtr;
    // Step used during watering cycle
      static int Step;
      static String str_topic,str_payload;
    
};


#endif // SPT_APPLICATION2_H
