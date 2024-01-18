#include <Arduino.h>
#include <Battery12vStats.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>

//ADS1115 & Battery 
Adafruit_ADS1115 ads1115;
int sdaPin = 19; //Define your sda pin, Default is pin 19.
int sclPin = 23; //Define your scl pin, Default is pin 23.

double sendAdc; //Variable to send ADC Value from ADS1115 to the BatteryStats


BatteryStatsADS1115 battery;

int dt = 2000; //Delay time in loop.

void setup() {
  Serial.begin(115200);

  Wire.begin(sdaPin, sclPin);
  ads1115.begin();

  //Define battery type for better charge status accuracy, LEAD_ACID is default.
  battery.set_battType(1); // 1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM

  battery.set_conversionFactor(1.05); //Default is 1.05

  
}

void loop(){
  
  sendAdc = ads1115.readADC_SingleEnded(3); //Reading ADS1115 and passing value to sendAdc variable.

  battery.send_adcValue(sendAdc); //Send our adc values from ADS1115 to the BatteryStats.

  Serial.print("ADC Val from BatteryStat: ");
  Serial.println(battery.get_adcValue()); //Get current adc value from BatteryStat, mostly for troubleshooting. Is this is 0, your readings dont go to your Battery.
  
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