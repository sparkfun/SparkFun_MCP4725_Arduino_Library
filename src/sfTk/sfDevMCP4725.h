#pragma once

#include <SparkFun_Toolkit.h>
#include <stdint.h>

// This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
// Please note that this breakout is for the MCP4725A0.
#define MCP4725_DEFAULT_ADDR 0x60 // For devices with A0 pulled HIGH, use 0x61

/*
See datasheet pg. 20:
When the normal mode is selected, the device
operates a normal digital-to-analog conversion. If the
power-down mode is selected, the device  enters power save
mode with a fixed resistive load
*/
enum MCP4725PowerDownModes
{
    MCP4725_POWER_DOWN_MODE_NORMAL = 0, // PD1=0, PD0=0
    MCP4725_POWER_DOWN_MODE_1K = 1,     // PD1=0, PD0=1
    MCP4725_POWER_DOWN_MODE_100K = 2,   // PD1=1, PD0=0
    MCP4725_POWER_DOWN_MODE_500K = 3    // PD1=1, PD0=1
};

// TODO: could optionally make bitfields for these to save space.
// TODO: if we wanted, we could also define a 12 bit value type.
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
    // TODO: Is our preference to have general functions like these return bools or sfeTkError codes?

    /// @brief Default constructor
    sfDevMCP4725() {};

    /// @brief Checks if device is connected by seeing if it acknowledges over I2C
    /// @return true if connected, false otherwise
    sfeTkError_t isConnected();

    /// @brief Begins the device
    /// @param theBus SparkFun Toolkit bus to use for communication
    /// @return 0 for sccess, negative for errors, positive for warnings
    sfeTkError_t begin(const uint8_t address = MCP4725_DEFAULT_ADDR, TwoWire &wirePort = Wire);

    /// @brief Updates DAC register in fast mode
    /// @param value 12-bit value to write to DAC register
    /// @param powerDownMode Power down mode to write to DAC register
    /// @return true if successful, false otherwise
    sfeTkError_t writeFastMode(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

    /// @brief Updates DAC register
    /// @param value 12-bit value to write to DAC register
    /// @return true if successful, false otherwise
    sfeTkError_t writeDac(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

    /// @brief Updates DAC register and EEPROM register
    /// @param value 12-bit value to write to DAC register
    /// @param powerDownMode Power down mode to write to DAC register
    /// @return true if successful, false otherwise
    sfeTkError_t writeDacEeprom(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

    /// @brief Reads DAC register and EEPROM register
    /// @param data Data structure to store read data
    /// @return true if successful, false otherwise
    sfeTkError_t readDacEeprom(Mcp4725Data &data);

  protected:
    sfeTkArdI2C *_theBus;
};
