/*
  This is an example written for the MCP4725 DAC Breakout
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/12918

  Written by SparkFun Electronics, December, 2024

  This example writes the DAC with three example voltages: 0V, 1.65V, and 3.3V.

  https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.13

  SparkFun code, firmware, and software is released under the MIT License.
  Please see LICENSE.md for more details.
*/

#include "SparkFun_MCP4725_Arduino_Library.h"

sfeMcp4725 myDac;

void setup()
{
    // Start serial
    Serial.begin(115200);
    Serial.println("MCP4725 Example 1 - Basic");

    // Start device and I2C
    if (myDac.begin() != kSTkErrOk){
        Serial.println("Device not found. Please check wiring.");
        while(1);
    }
}

void loop()
{
  // This loop will write three different voltages to the DAC with 
  // 2 second delays in between each write, so you can see the voltage
  // change on the output with a multimeter or oscilloscope.
  
  // The full range of the 12-bit DAC is 0-4095, which corresponds to VSS (Ground) to VDD (3.3V). 
  // The equation for output voltage is (see datasheet pg. 19): VDD * (DAC Value / 4096) 
  
  Serial.println("Writing 0V to DAC");
  myDac.writeDac(0); // ~0V if VDD = 3.3V
  
  delay(2000);

  Serial.println("Writing 1.65V to DAC");
  myDac.writeDac(2048); // ~1.65 V if VDD = 3.3V

  delay(2000);

  Serial.println("Writing 3.3V to DAC");
  myDac.writeDac(4095); // ~3.3 V if VDD = 3.3V
  
  delay(2000);
}