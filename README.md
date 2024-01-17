# Battery 12v Stats

Library to keeps easy to obtain a 12v (battery) charge level in Arduino environment.

This lib was made on top of [danilopinotti Battery18650Stats](https://github.com/danilopinotti/Battery18650Stats.git)

## Compatibility

This Lib theoretically compatible with any ESP that has ACP pins and want to monitor a 12v Battery. It's tested with:

- [x] [WEMOS LOLIN32 Lite]

## Usage

### Import and setup
To use this Lib, you need to import and setup:
```cpp
#include <Battery12vStats.h>

// #define ADC_PIN 36
// #define CONVERSION_FACTOR 4.855
// #define READS 5
// #define BATTTYPE 1

Battery12vStats battery();
// Battery12vStats battery(ADC_PIN);
// Battery12vStats battery(ADC_PIN, CONVERSION_FACTOR);
// Battery12vStats battery(ADC_PIN, CONVERSION_FACTOR, READS);
// Battery12vStats battery(ADC_PIN, CONVERSION_FACTOR, READS, BATTTYPE);
```

Constructor parameters:
```cpp
Battery12vStats(<adc_pin>, <conversion_factor>, <reads>, <batttype>);
```

- `adc_pin` (optional): The ADC Pin that lib will read (analogRead) to calculate charge level. Can be obtained at device datasheet. Default Value: `36`;
- `conversion_factor` (optional): Value used to convert ADC pin reading in real battery voltage. This value can be obtained through comparisons between code result and a voltmeter result. Default Value: `4.855`;
- `reads` (optional): Quantity of reads to get an average of pin readings. Its used due pin reading instabilities. Default Value: `20`;
- `battType` (optional): For accurate charge level you should choose your battery type here. Default is `1` (Lead Acid);
### Battery Type

Default is Lead Acid battery, if you have wrong type of battery Defined the Battery Charge Level is not correct.
1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM

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

//Define battery type for better charge status accuracy, LEAD_ACID is default.
// 1 - Lead Acid, 2 - AGM, 3 - GEL, 4 - LIFEPO4, 5 - CUSTOM
int battType = 1;

int adcPin = 36; //Define your ADC pin, Default is pin 36.
float convFactor = 4.855; //Get this value by measure the battery with a multimeter and adjust it until its the same in the terminal.
int nrReads = 20; //Around 20 reads is good, if you want a more stable input you should use ADS1115 with 16bits and more filter.


Battery12vStats battery(adcPin, convFactor, nrReads, battType);

void setup() {
  Serial.begin(115200);
  
}

void loop(){
  Serial.print("Volts: ");
  Serial.println(battery.getBatteryVolts());
	
  Serial.print("Charge level: ");
  Serial.println(battery.getBatteryChargeLevel());
  delay(2000);
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