/**
 * @file Example01_Basic.ino
 * @brief Example demonstrating how to set voltages using the MCP4725 DAC.
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
 * @see https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library
 */

#include "SparkFun_MCP4725_Arduino_Library.h"

SfeMCP4725ArdI2C myDac;

void setup()
{
    Wire.begin();

    Serial.begin(115200);

    // Hang out until the terminal is open.
    while (!Serial)
        ;

    Serial.println("MCP4725 Example 1 - Basic");

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
    // 500ms delays in between each write, so you can see the voltage
    // change on the output with a multimeter or oscilloscope.

    // The full range of the 12-bit DAC is 0-4095, which corresponds to VSS (Ground) to VDD (3.3V).
    // The equation for output voltage is (see datasheet pg. 19): VDD * (DAC Value / 4096)
    Serial.println("Writing 0V to DAC");
    myDac.writeDac(0); // ~0V if VDD = 3.3V

    delay(500);

    Serial.println("Writing 1.6V to DAC");
    myDac.writeDac(1985); // ~1.6V if VDD = 3.3V
    delay(500);

    Serial.println("Writing 3.3V to DAC");
    myDac.writeDac(4095); // ~3.3 V if VDD = 3.3V

    delay(500);
}
