#ifndef SPT_DHTSENSOR_H
#define SPT_DHTSENSOR_H
// Class CAnalogSensor
#include "spt_sensor.h"
#include "spt_DHT.h"

#define DHT11SensorType 11
#define DHT22SensorType 22

/* Error code for read functions */
const byte DHT_SUCCESS = 0;        // Pas d'erreur
const byte DHT_TIMEOUT_ERROR = 1;  // Temps d'attente dépassé
const byte DHT_CHECKSUM_ERROR = 2; // Données reçues erronées
const byte DHT_TYPE_ERROR = 3; // Erreur de type

struct spt_dhtsensor_dataconfig
{
  int Id;
  int Pin;
  int Type;
  boolean enable;
};

class spt_dhtsensor : public CSensor
{
  public:
    spt_dhtsensor();
    ~spt_dhtsensor();
    void Reset();
    void Init(spt_dhtsensor_dataconfig dataconfig);
    void Init(int sensorid, int digitalinputpin, int sensortype/*, PubSubClient *mqttclient=NULL*/);
    boolean ReadData(float *temperature, float *humidity, bool senddata=true);
    // get data in xml formatted format
    //virtual String GetXMLString();
  protected:
    // get data in xml formatted format
    //virtual String _addXMLString(String str);
    virtual String _addJSONString(String str);
    //int SensorId;
    float TemperatureValue;
    float RelativeHumidityValue;
    int SensorInputPin;
    int SensorType;
    //spt_tcpserver *wifiPtr;
    //PubSubClient *MQTT_Client;
    DHT *dht_sensor;

};
#endif // SPT_DHTSENSOR_H
