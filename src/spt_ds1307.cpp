#include "spt_ds1307.h"
#include "arduino.h"

spt_ds1307::spt_ds1307()
{
  /** Adresse I2C du module RTC DS1307 */
  DS1307_ADDRESS = 0x68;

  /** Adresse du registre de contrôle du module RTC DS1307 */
  DS1307_CTRL_REGISTER = 0x07;

  /** Adresse et taille de la NVRAM du module RTC DS1307 */
  DS1307_NVRAM_BASE = 0x08;
  DS1307_NVRAM_SIZE = 56; // 0x38 -> from 0x08 to 0x3F
  WirePtr=NULL;
}

void spt_ds1307::SetWirePtr(TwoWire *wire)
{
  WirePtr=wire;
}

/** Fonction de conversion BCD -> decimal */
uint8_t spt_ds1307::bcd_to_decimal(uint8_t bcd) {
  return (bcd / 16 * 10) + (bcd % 16);
}

/** Fonction de conversion decimal -> BCD */
uint8_t spt_ds1307::decimal_to_bcd(uint8_t decimal) {
  return (decimal / 10 * 16) + (decimal % 10);
}


/**
 * Fonction récupérant l'heure et la date courante à partir du module RTC.
 * Place les valeurs lues dans la structure passée en argument (par pointeur).
 * N.B. Retourne 1 si le module RTC est arrêté (plus de batterie, horloge arrêtée manuellement, etc.), 0 le reste du temps.
 */
uint8_t spt_ds1307::GetCurrentDateTime(DateTime_t *datetime)
{
  /* Début de la transaction I2C */
  WirePtr->beginTransmission(DS1307_ADDRESS);
  WirePtr->write((uint8_t) 0); // Lecture mémoire à l'adresse 0x00
  WirePtr->endTransmission(); // Fin de la transaction I2C

  /* Lit 7 octets depuis la mémoire du module RTC */
  WirePtr->requestFrom(DS1307_ADDRESS, (uint8_t) 7);
  uint8_t raw_seconds = WirePtr->read();
  datetime->seconds = bcd_to_decimal(raw_seconds);
  datetime->minutes = bcd_to_decimal(WirePtr->read());
  uint8_t raw_hours = WirePtr->read();
  if (raw_hours & 64) { // Format 12h
    datetime->hours = bcd_to_decimal(raw_hours & 31);
    datetime->is_pm = raw_hours & 32;
  } else { // Format 24h
    datetime->hours = bcd_to_decimal(raw_hours & 63);
    datetime->is_pm = 0;
  }
  datetime->day_of_week = bcd_to_decimal(WirePtr->read());
  datetime->days = bcd_to_decimal(WirePtr->read());
  datetime->months = bcd_to_decimal(WirePtr->read());
  datetime->year = bcd_to_decimal(WirePtr->read());

  /* Si le bit 7 des secondes == 1 : le module RTC est arrêté */
  return raw_seconds & 128;
}


/**
 * Fonction ajustant l'heure et la date courante du module RTC à partir des informations fournies.
 * N.B. Redémarre l'horloge du module RTC si nécessaire.
 */
void spt_ds1307::SetCurrentDateTime(DateTime_t *datetime) {

  /* Début de la transaction I2C */
  WirePtr->beginTransmission(DS1307_ADDRESS);
  WirePtr->write((uint8_t) 0); // Ecriture mémoire à l'adresse 0x00
  WirePtr->write(decimal_to_bcd(datetime->seconds) & 127); // CH = 0
  WirePtr->write(decimal_to_bcd(datetime->minutes));
  WirePtr->write(decimal_to_bcd(datetime->hours) & 63); // Mode 24h
  WirePtr->write(decimal_to_bcd(datetime->day_of_week));
  WirePtr->write(decimal_to_bcd(datetime->days));
  WirePtr->write(decimal_to_bcd(datetime->months));
  WirePtr->write(decimal_to_bcd(datetime->year));
  WirePtr->endTransmission(); // Fin de transaction I2C
}
/**
 * Fonction de sélection du mode de fonctionnement et de la polarité (HIGH ou LOW) de la broche SQW.
 */
void spt_ds1307::SetSQWPinMode(DS1307_Mode_t mode, uint8_t polarity) {

  /* Calcul la valeur du registre de contrôle */
  uint8_t ctrl_register = !!polarity << 7; // OUT = polarity
  if (mode != SQW_DC) {
    ctrl_register |= 1 << 4; // SQWE = 1
    ctrl_register |= mode & 3; // RSx = mode
  }

  /* Début de la transaction I2C */
  WirePtr->beginTransmission(DS1307_ADDRESS);
  WirePtr->write(DS1307_CTRL_REGISTER); // Ecriture mémoire à l'adresse 0x07
  WirePtr->write(ctrl_register);
  WirePtr->endTransmission(); // Fin de transaction I2C
}
/** Fonction de lecture de la mémoire non volatile du module RTC (56 octets maximum) */
int spt_ds1307::ReadMemory(uint8_t address)
{
  /* Ne lit pas en dehors de la NVRAM */
  if (address > DS1307_NVRAM_SIZE)
    return -1;
  /* Début de la transaction I2C */
  WirePtr->beginTransmission(DS1307_ADDRESS);
  WirePtr->write(DS1307_NVRAM_BASE + address); // Lecture mémoire NVRAM
  WirePtr->endTransmission(); // Fin de la transaction I2C
  /* Lit un octet depuis la mémoire du module RTC */
  WirePtr->requestFrom(DS1307_ADDRESS, (uint8_t) 1);
  return WirePtr->read();
}
/** Fonction d'écriture de la mémoire non volatile du module RTC (56 octets maximum) */
void spt_ds1307::WriteMemory(uint8_t address, uint8_t data)
{
  /* N'écrit pas en dehors de la NVRAM */
  if (address > DS1307_NVRAM_SIZE)
    return;
  /* Début de la transaction I2C */
  WirePtr->beginTransmission(DS1307_ADDRESS);
  WirePtr->write(DS1307_NVRAM_BASE + address); // Ecriture mémoire NVRAM
  WirePtr->write(data);
  WirePtr->endTransmission(); // Fin de transaction I2C
}

String spt_ds1307::GetCurrentDateTimeString()
{
  String str;
  DateTime_t datetime;
  uint8_t iResult;
  iResult=GetCurrentDateTime(&datetime);
  if (iResult==0)
  {
    str=datetime.toString();
  }
  else
  {
    str="0000-00-00T00:00:00";
  }
  return str;
}

void DateTime_t::fromString(String str)
{ // 0000-00-00T00:00:00
  // 0  0  0  0  -  0  0  -  0  0  T  0  0  :  0  0  :  0  0
  // 00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18
  // uint8_t year;  /**!< Année au format yy (exemple : 16 = 2016) de 2000 à 2099 */
Serial.println("DEBUG ************* "+str);
  year=str.substring(2,4).toInt();
  // uint8_t months;  /**!< Mois 01 - 12 */
  months=str.substring(5,7).toInt();
  // uint8_t days; /**!< Jours 01 - 31 */
  days=str.substring(8,10).toInt();
  // uint8_t hours;  /**!< Heures 00 - 23 (format 24h), 01 - 12 (format 12h) */
  hours=str.substring(11,13).toInt();
  // uint8_t minutes; /**!< Minutes 00 - 59 */
  minutes=str.substring(14,16).toInt();
  // uint8_t seconds; /**!< Secondes 00 - 59 */
  seconds=str.substring(17,19).toInt();
  // uint8_t is_pm; /**!< Vaut 1 si l'heure est en format 12h et qu'il est l'aprés midi, sinon 0 */
  is_pm=0;
  // uint8_t day_of_week;  /**!< Jour de la semaine 01 - 07, 1 = lundi, 2 = mardi, etc.  */
  day_of_week=0;
}

String DateTime_t::toString()
{
  String str;
  //str="0000-00-00T00:00:00";
  str="20";
  if (year<10) str+="0"+String(year); else str+=String(year);
  str+="-";
  if (months<10) str+="0"+String(months); else str+=String(months);
  str+="-";
  if (days<10) str+="0"+String(days); else str+=String(days);
  str+="T";
  if (hours<10) str+="0"+String(hours); else str+=String(hours);
  str+=":";
  if (minutes<10) str+="0"+String(minutes); else str+=String(minutes);
  str+=":";
  if (seconds<10) str+="0"+String(seconds); else str+=String(seconds);
  return str;
}
