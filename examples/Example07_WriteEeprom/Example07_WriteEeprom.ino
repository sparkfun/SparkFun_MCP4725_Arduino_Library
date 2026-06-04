/**
 * @file Example07_WriteEeprom.ino
 * @brief Example demonstrates how to write to EEPROM.
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

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("MCP4725 Example 7 - Write EEPROM");

    // Start device and I2C
    if (myDac.begin() == false)
    {
        Serial.println("Device not found. Please check wiring.");
        while (1)
            ;
    }

    // The MCP4725 has an EEPROM that can store a single 12-bit DAC value as well
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
