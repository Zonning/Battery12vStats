/* 
 *  12v Lead acid battery
 */

#ifndef Battery12vStats_H_
#define Battery12vStats_H_


//#define USE_ADS1115  //Use external ADS1115 to get ADC Readings.
//#define USE_INTERNAL_ADC //Use internal ADC pin to get ADC Readings.

//Internal ADC
#include <Arduino.h>

//Define battery type for better charge status accuracy, LEAD_ACID is default.
// 1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM

#define DEFAULT_PIN 36
#define DEFAULT_READS 20
class BatteryStatsInternal {
 public:
  BatteryStatsInternal();
  ~BatteryStatsInternal();
  BatteryStatsInternal(int adcPin);
  BatteryStatsInternal(int adcPin, int reads);

  void set_conversionFactor(double convFactor = 4.855);
  void set_battType(int battType = 1);
  double get_conversionFactor();
  int get_battType();

  int getBatteryChargeLevel(bool useConversionTable = true);
  double getBatteryVolts();

 private:
  double CONVFACTOR = 4.855;
  int BATTTYPE = 1;
  int _adcPin;
  int _reads;
  double _conversionFactor;
  double *_conversionTable = nullptr;

  void _initConversionTable();
  int _getChargeLevelFromConversionTable(double volts);
  int _calculateChargeLevel(double volts);
  int _avgAnalogRead(int pinNumber, int reads);
  double _analogReadToVolts(int readValue);
};


//ADS1115

//Define battery type for better charge status accuracy, LEAD_ACID is default.
// 1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM

#define DEFAULT_READS 20
class BatteryStatsADS1115 {
 public:
  BatteryStatsADS1115();
  ~BatteryStatsADS1115();

  void set_conversionFactor(double convFactor = 1.05);
  void set_battType(int battType = 1);
  void send_adcValue(double adcValue = 0);
  double get_adcValue();
  double get_conversionFactor();
  int get_battType();

  int getBatteryChargeLevel(bool useConversionTable = true);
  double getBatteryVolts();

 private:
  double CONVFACTOR = 4.855;
  int BATTTYPE = 1;
  double _adcValue;
  double _conversionFactor;
  double *_conversionTable = nullptr;

  void _initConversionTable();
  int _getChargeLevelFromConversionTable(double volts);
  int _calculateChargeLevel(double volts);
  double _analogReadToVolts(int readValue);
};

#endif
