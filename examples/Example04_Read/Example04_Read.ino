/*
  This is an example written for the MCP4725 DAC Breakout
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/12918

  Written by SparkFun Electronics, December, 2024

  This example writes the DAC and then reads the DAC value back from the device.

  https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.13

  SparkFun code, firmware, and software is released under the MIT License.
  Please see LICENSE.md for more details.
*/

#include "SparkFun_MCP4725_Arduino_Library.h"

SfeMCP4725ArdI2C myDac;
Mcp4725Data myReadData;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("MCP4725 Example 4 - Read");

    // Start device and I2C
    if (myDac.begin() == false)
    {
        Serial.println("Device not found. Please check wiring.");
        while (1)
            ;
    }

    // Write both the DAC and EEPROM
    myDac.writeDacEeprom(1024); // ~0.825V if VDD = 3.3V

    // Wait for initial write to complete
    delay(250);

    // Now write just the DAC with a different value
    myDac.writeDac(2048); // ~1.65 V if VDD = 3.3V
}

void loop()
{
    // Read the DAC value into our myReadData object
    myDac.readDacEeprom(myReadData);

    // Print to terminal
    Serial.print("EEPROM Value: ");
    Serial.println(myReadData.eepromValue);
    Serial.print("DAC Value: ");
    Serial.println(myReadData.dacValue);

    delay(1000); // delay to not overwhelm the serial port

    // Notice, if you unplug and replug the DAC from your controller, the
    // EEPROM value will persist, but the DAC value read will reset to the EEPROM value.
}
