/**
 * @file Example05_PowerDown.ino
 * @brief Example demonstrates the DAC's behavior in its' power down state.
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
    Serial.println("MCP4725 Example 5 - Power Down");

    // Start device and I2C
    if (myDac.begin() == false)
    {
        Serial.println("Device not found. Please check wiring.");
        while (1)
            ;
    }
}

void loop()
{
    // We'll start by writing 3.3V to the DAC in normal mode
    Serial.println("Writing 3.3V to DAC");
    // By default, the writeDac() function will write to the DAC in normal mode if no mode is specified.
    myDac.writeDac(4095); // ~3.3 V if VDD = 3.3V.

    delay(2000);

    // Now, we will put the dac in power down mode.
    // This will reduce the current consumption of the DAC to ~60nA (typical).
    // The DAC will not output any voltage in power down mode, but it can still receive I2C commands.
    // The output stage will switch from an amplifier output to a known resistive load (1k, 100k, or 500k).
    // To wake the DAC from power down mode, write a value to the DAC, with normal mode enabled.
    // See datasheet pg. 20
    Serial.println("Entering Power Down Mode...");
    myDac.writeDac(2048, MCP4725_POWER_DOWN_MODE_100K); // Note, it doesn't matter what value we write here, the DAC
                                                        // will stop performing conversions
    delay(2000);

    Serial.println("Writing to the DAC in Power Down Mode (will not output conversion)...");
    myDac.writeDac(4095, MCP4725_POWER_DOWN_MODE_100K); // We should see no change in output voltage, as the DAC is
                                                        // still in power down mode

    delay(2000);

    // Now by issuing a writeDac command with normal mode enabled, we will wake the DAC from power down mode and again
    // will see the value change
    Serial.println("Writing 0.825V to DAC");
    myDac.writeDac(1024, MCP4725_POWER_DOWN_MODE_NORMAL); // ~0.825V if VDD = 3.3V

    delay(2000);
}
