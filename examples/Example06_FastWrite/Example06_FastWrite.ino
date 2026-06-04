/**
 * @file Example06_FastWrite.ino
 * @brief Example demonstrates the DAC's "fast write" functionality.
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
    Serial.println("MCP4725 Example 6 - Fast Write");

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
    // This loop will write three different voltages to the DAC with
    // 2 second delays in between each write, so you can see the voltage
    // change on the output with a multimeter or oscilloscope.

    // The full range of the 12-bit DAC is 0-4095, which corresponds to VSS (Ground) to VDD (3.3V).
    // The equation for output voltage is (see datasheet pg. 19): VDD * (DAC Value / 4096)

    // We will use the fast write function which uses only two data bytes to
    // write the DAC value faster than a typical write. (see datasheet pg. 23 and 24)
    Serial.println("Writing 0V to DAC");
    myDac.writeFastMode(0); // ~0V if VDD = 3.3V

    delay(2000);

    Serial.println("Writing 1.65V to DAC");
    myDac.writeFastMode(2048); // ~1.65 V if VDD = 3.3V

    delay(2000);

    Serial.println("Writing 3.3V to DAC");
    myDac.writeFastMode(4095); // ~3.3 V if VDD = 3.3V

    delay(2000);
}
