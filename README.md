# Battery 12v Stats

Library to keep it easy to monitor a 12 Volts Battery charge level and Voltage in Arduino environment.

This lib was made on top of [danilopinotti Battery18650Stats](https://github.com/danilopinotti/Battery18650Stats.git)

## Compatibility

This Lib is theoretically compatible with any ESP that has ADC pins and want to monitor a 12 Volt Battery. It's tested with:

- [x] [WEMOS LOLIN32 Lite]

## Usage

### Import and setup
To use this Lib, you need to import and setup:
```cpp
#include <Battery12vStats.h>

// #define ADC_PIN 36
// #define READS 5

Battery12vStats battery();
// Battery12vStats battery(ADC_PIN);
// Battery12vStats battery(ADC_PIN, READS);
```

Constructor parameters:
```cpp
Battery12vStats(<adc_pin>, <reads>);
```

- `adc_pin` (optional): The ADC Pin that lib will read (analogRead) to calculate charge level. Can be obtained at device datasheet. Default Value: `36`;
- `reads` (optional): Quantity of reads to get an average of pin readings. Its used due pin reading instabilities. Default Value: `20`;
### Battery Type

Default is Lead Acid battery, if you have wrong type of battery Defined the Battery Charge Level is not correct.
1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM

You change with:
battery.set_battType(1); Change 1 to the battery you got.

Too print your current you can call:
Serial.println(battery.get_battType());

### Conversion Factor

To get this number you should use a multimeter and measure the battery voltage and compare with the example code output.
Default is 4.855

You change with:
battery.set_conversionFactor(4.855);

Too print your current you can call:
Serial.println(battery.get_conversionFactor());

### Methods

After the installation and instantiation, we are able to obtain the charge level and current battery voltage.

#### Method `double getBatteryVolts()`
Returns the current battery voltage.

#### Method `int getBatteryChargeLevel(bool useConversionTable = true)`
Returns the current battery charge level.
  - Parameter `bool useConversionTable`: Indicates if the internal charge level will be obtained using the internal predefined conversion table. Default value: `true`

### Usage example
```cpp
#include <Arduino.h>
#include <Battery12vStats.h>

int adcPin = 36; //Define your ADC pin, Default is pin 36.
int nrReads = 20; //Around 20 reads is good, if you want a more stable input you should use ADS1115 with 16bits and more filter.

int dt = 2000; //Delay time in loop.

Battery12vStats battery(adcPin, nrReads);

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
```
### Voltage Divider
In the example we are using a voltage divider to measure a 12v source:
R1 47k Ohm
R2 10k Ohm

So in this case if you get 12v in, you get 2.105v on the ADC pin through the voltage divider.

You cant measure more then 3.3v with an esp32 ADC pin, check that carefully before hooking anything up to the board!


## Troubleshoot and Finding Conversion Factor
Sometimes the result of `getBatteryChargeLevel` and `getBatteryVolts` may not represents the real state of the battery.

There are two main problems that could be happening:
- Your code is using the wrong ADC port or
- Your code is using the wrong conversion factor.

### Finding the right ADC port
You can find the ADC ports in the device datasheet. The port can change according to the hardware you are using.

### Finding the right conversion factor
To find the right conversion factor you will need a voltmeter.

Steps:
1. Measure the voltage of the battery with the voltmeter
2. Print the voltage obtained by the lib through `getBatteryVolts` method

If the measurements (library and voltmeter) match, the conversion factor is right.
If they are different, you will need to increment or decrement the conversion factor until the measurements match.

## Tested devices
This is the tested parameters and calibrations for given devices

| Device          | ADC Pin | Conversion Factor |
|-----------------|---------|-------------------|
| [WEMOS LOLIN32 Lite] | 36      | 4.855             |

## License
The MIT License (MIT). Please see License File for more information.