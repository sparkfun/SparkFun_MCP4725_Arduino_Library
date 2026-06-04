/**
 * @file Example04_Read.ino
 * @brief Example that reads the currently used DAC values as well as its' EEPROM.
 *
 * @author SparkFun Electronics
 * @date 2026
 * @copyright Copyright (c) 2026, SparkFun Electronics Inc. All rights reserved.
 *
 * @section License License
 * SPDX-License-Identifier: MIT
 *
 * @section Product_Links Product Links
 * - Qwiic 1x1: https://www.sparkfun.com/sparkfun-qwiic-12-bit-dac-breakout-mcp4725.html
 * - Breakout: https://www.sparkfun.com/sparkfun-i2c-dac-breakout-mcp4725.html
 *
 *
 * @see https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library
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
