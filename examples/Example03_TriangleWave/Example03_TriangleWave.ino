/**
 * @file Example03_TriangleWave.ino
 * @brief Example that generates a triangle wave ranging from 0V - 3.3V
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
    Wire.begin();

    Serial.begin(115200);

    Serial.println("MCP4725 Example 3 - TriangleWave");

    if (myDac.begin() == false)
    {
        Serial.println("Device not found. Please check wiring.");
        while (1)
            ;
    }
}

void loop()
{
    uint32_t counter;

    // Run through the full 12-bit scale for a triangle wave
    for (counter = 0; counter < 4095; counter++)
    {
        myDac.writeDac(counter);
    }
    for (counter = 4095; counter > 0; counter--)
    {
        myDac.writeDac(counter);
    }
}
