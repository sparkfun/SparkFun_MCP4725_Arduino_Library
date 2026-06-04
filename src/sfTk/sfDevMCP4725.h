/**
 * @file sfDevMCP4725.h
 * @brief Header file for the SparkFun Qwiic DAC - MCP4725
 *
 * This file contains the class definitions, constants, and enums for interacting with the MCP4725 DAC.
 *
 * @details
 * sfDevMCP4725 is a comms-agnostic driver for the MCP4725 DAC that uses the SparkFun Toolkit.
 * The SfeMCP4725ArdI2C class defines the Arduino specific behavior for initializing and interacting with devices.
 *
 * @author SparkFun Electronics
 * @date 2026
 * @copyright Copyright (c) 2026, SparkFun Electronics Inc. This project is released under the MIT License.
 *
 * SPDX-License-Identifier: MIT
 *
 * @section Classes Classes
 * - sfDevMCP4725
 *
 * @section Repository Repository
 * https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library
 *
 * @section Product_Links Product Links
 * - Qwiic 1x1: https://www.sparkfun.com/sparkfun-qwiic-12-bit-dac-breakout-mcp4725.html
 * - Breakout: https://www.sparkfun.com/sparkfun-i2c-dac-breakout-mcp4725.html
 *
 */
#pragma once

#include <SparkFun_Toolkit.h>
#include <cstdint>
#include <stdint.h>

// This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
// Please note that this breakout is for the MCP4725A0.
#define MCP4725_DEFAULT_ADDRESS 0x60
#define MCP4725_ALTERNATE_ADDRESS 0x61 // For devices with A0 pulled HIGH, use 0x61

/*
See datasheet pg. 20:
When the normal mode is selected, the device
operates a normal digital-to-analog conversion. If the
power-down mode is selected, the device  enters power save
mode with a fixed resistive load
*/
enum MCP4725PowerDownModes : uint8_t
{
    MCP4725_POWER_DOWN_MODE_NORMAL = 0, // PD1=0, PD0=0
    MCP4725_POWER_DOWN_MODE_1K = 1,     // PD1=0, PD0=1
    MCP4725_POWER_DOWN_MODE_100K = 2,   // PD1=1, PD0=0
    MCP4725_POWER_DOWN_MODE_500K = 3    // PD1=1, PD0=1
};

typedef struct
{
    uint8_t rdyFlag;
    uint8_t porFlag;
    MCP4725PowerDownModes dacPowerDownMode;
    uint16_t dacValue;
    MCP4725PowerDownModes eepromPowerDownMode;
    uint16_t eepromValue;
} Mcp4725Data;

class sfDevMCP4725
{
  public:
    /// @brief Default constructor
    sfDevMCP4725() : _theBus{nullptr}
    {
    }

    /// @brief Begins the device
    /// @param theBus SparkFun Toolkit bus to use for communication
    /// @return 0 for success, negative for errors, positive for warnings
    bool begin(sfTkIBus *theBus = nullptr);

    /// @brief Sets the communication bus to the specified bus.
    /// @param theBus Bus to set as the communication device.
    void setCommunicationBus(sfTkIBus *theBus);

    /// @brief Updates DAC register in fast mode
    /// @param value 12-bit value to write to DAC register
    /// @param powerDownMode Power down mode to write to DAC register
    /// @return true if successful, false otherwise
    bool writeFastMode(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

    /// @brief Updates DAC register
    /// @param value 12-bit value to write to DAC register
    /// @param powerDownMode Power down mode to write to DAC register
    /// @return true if successful, false otherwise
    bool writeDac(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

    /// @brief Updates DAC register and EEPROM register
    /// @param value 12-bit value to write to DAC register
    /// @param powerDownMode Power down mode to write to DAC register
    /// @return true if successful, false otherwise
    bool writeDacEeprom(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

    /// @brief Reads DAC register and EEPROM register
    /// @param data Data structure to store read data
    /// @return true if successful, false otherwise
    bool readDacEeprom(Mcp4725Data &data);

  protected:
    sfTkIBus *_theBus;
};
