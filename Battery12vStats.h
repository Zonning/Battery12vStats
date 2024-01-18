/* 
 *  12v Lead acid battery
 */

#ifndef Battery12vStats_H_
#define Battery12vStats_H_

#include <Arduino.h>

//Define battery type for better charge status accuracy, LEAD_ACID is default.
// 1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM

#define DEFAULT_PIN 36
#define DEFAULT_READS 20
class Battery12vStats {
 public:
  Battery12vStats();
  ~Battery12vStats();
  Battery12vStats(int adcPin);
  Battery12vStats(int adcPin, int reads);

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

#endif
