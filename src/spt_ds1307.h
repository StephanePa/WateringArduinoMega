#ifndef SPT_DS1307_H
#define SPT_DS1307_H

/* Dépendancy */
#include "Wire.h"

/** Structure contenant les informations de date et heure en provenance ou à destination du module RTC */
struct DateTime_t
{
  uint8_t seconds; /**!< Secondes 00 - 59 */
  uint8_t minutes; /**!< Minutes 00 - 59 */
  uint8_t hours;  /**!< Heures 00 - 23 (format 24h), 01 - 12 (format 12h) */
  uint8_t is_pm; /**!< Vaut 1 si l'heure est en format 12h et qu'il est l'aprés midi, sinon 0 */
  uint8_t day_of_week;  /**!< Jour de la semaine 01 - 07, 1 = lundi, 2 = mardi, etc.  */
  uint8_t days; /**!< Jours 01 - 31 */
  uint8_t months;  /**!< Mois 01 - 12 */
  uint8_t year;  /**!< Année au format yy (exemple : 16 = 2016) de 2000 à 2099 */
  void fromString(String str);
  String toString();
};


/** Mode de fonctionnement pour la broche SQW */
typedef enum {
  SQW_1_HZ = 0, /**!< Signal à 1Hz sur la broche SQW */
  SQW_4096_HZ,  /**!< Signal à 4096Hz sur la broche SQW */
  SQW_8192_HZ,  /**!< Signal à 8192Hz sur la broche SQW */
  SQW_32768_HZ, /**!< Signal à 32768Hz sur la broche SQW */
  SQW_DC /**!< Broche SQW toujours à LOW ou HIGH */
} DS1307_Mode_t;

class spt_ds1307
{
  public:
    spt_ds1307();
    void SetWirePtr(TwoWire *wire);
    void SetCurrentDateTime(DateTime_t *datetime); 
    uint8_t GetCurrentDateTime(DateTime_t *datetime);
    String GetCurrentDateTimeString();
    // SQW pin mode configuration
    //   SetSQWPinMode(SQW_DC, LOW);
    //   SetSQWPinMode(SQW_DC, HIGH);
    //   SetSQWPinMode(SQW_1_HZ, 0);
    //   SetSQWPinMode(SQW_4096_HZ, 0);
    //   SetSQWPinMode(SQW_8192_HZ, 0);
    //   SetSQWPinMode(SQW_32768_HZ, 0);
    void SetSQWPinMode(DS1307_Mode_t mode, uint8_t polarity);
    // Memory management functions
    // Memory from 0x08 to 0x3F (physical address)
    // address (functional address) from 0x00 to 0x37
    int ReadMemory(uint8_t address);
    void WriteMemory(uint8_t address, uint8_t data);
  protected:
    TwoWire *WirePtr;
    uint8_t bcd_to_decimal(uint8_t bcd);
    uint8_t decimal_to_bcd(uint8_t decimal);
    /** Adresse I2C du module RTC DS1307 */
    uint8_t DS1307_ADDRESS;
    /** Adresse du registre de contrôle du module RTC DS1307 */
    uint8_t DS1307_CTRL_REGISTER;
    /** Adresse et taille de la NVRAM du module RTC DS1307 */
    uint8_t DS1307_NVRAM_BASE;
    uint8_t DS1307_NVRAM_SIZE;
};

#endif // SPT_DS1307_H
