/*
  This is an example written for the MCP4725 DAC Breakout
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/12918

  Written by SparkFun Electronics, December, 2024

  This example writes the DAC and EEPROM With a single command.

  https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.13

  SparkFun code, firmware, and software is released under the MIT License.
  Please see LICENSE.md for more details.
*/

#include "SparkFun_MCP4725_Arduino_Library.h"

SfeMCP4725ArdI2C myDac;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("MCP4725 Example 3 - Write EEPROM");

    // Start device and I2C
    if (myDac.begin() == false)
    {
        Serial.println("Device not found. Please check wiring.");
        while (1)
            ;
    }

    // The MCP4725 has an EEROM that can store a single 12-bit DAC value as well
    // as two configuration bits for the power down mode. The DAC will output this
    // value on reset or power-cycle.
    Serial.println("Writing 1.65V to DAC");
    myDac.writeDacEeprom(2048); // ~1.65 V if VDD = 3.3V

    // Now, you can unplug the DAC from your controller and plug it back in,
    // and you will see that the value we wrote persists even after a power-cycle.
}

void loop()
{
    // loop forever
}
