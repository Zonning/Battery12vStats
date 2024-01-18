#include <Arduino.h>
#include <Battery12vStats.h>

int adcPin = 36; //Define your ADC pin, Default is pin 36.
int nrReads = 20; //Around 20 reads is good, if you want a more stable input you should use ADS1115 with 16bits and more filter.

int dt = 2000; //Delay time in loop.

BatteryStatsInternal battery(adcPin, nrReads);

void setup() {
  Serial.begin(115200);

  //Define battery type for better charge status accuracy, LEAD_ACID is default.
  battery.set_battType(1); // 1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM

  battery.set_conversionFactor(4.855); //Default is 4.855

  
}

void loop(){
  Serial.print("Volts: ");
  Serial.println(battery.getBatteryVolts());
	
  Serial.print("Charge level: ");
  Serial.println(battery.getBatteryChargeLevel());

  Serial.print("Battery type: ");
  Serial.println(battery.get_battType());

  Serial.print("Conversion Factor: ");
  Serial.println(battery.get_conversionFactor());
  delay(dt);
}