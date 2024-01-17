#include <Arduino.h>
#include <Battery12vStats.h>

//Define battery type for better charge status accuracy, LEAD_ACID is default.
// 1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM
int battType = 1;

int adcPin = 36; //Define your ADC pin, Default is pin 36.
float convFactor = 4.855; //Get this value by measure the battery with a multimeter and adjust it until its the same in the terminal.
int nrReads = 20; //Around 20 reads is good, if you want a more stable input you should use ADS1115 with 16bits and more filter.

int dt = 2000; //Delay time in loop.

Battery12vStats battery(adcPin, convFactor, nrReads, battType);

void setup() {
  Serial.begin(115200);
  
}

void loop(){
  Serial.print("Volts: ");
  Serial.println(battery.getBatteryVolts());
	
  Serial.print("Charge level: ");
  Serial.println(battery.getBatteryChargeLevel());
  delay(dt);
}