#pragma once

// TODO: Add includes as needed (e.g. #include <Wire.h>, #include <SPI.h>)
#include "Arduino.h"
#include <Wire.h>
#include <stdint.h>

//This is the I2C Address of the MCP4725, by default (A0 pulled to GND).
//Please note that this breakout is for the MCP4725A0. 
#define MCP4725_ADDR 0x60   
//For devices with A0 pulled HIGH, use 0x61

/* 
See datasheet pg. 20: 
When the normal mode is selected, the device
operates a normal digital-to-analog conversion. If the
power-down mode is selected, the device enters a
power saving condition by shutting down most of the
internal circuits. During the power-down mode, all
internal circuits except the I2C interface are disabled
and there is no data conversion event, and no VOUT is
available. The device also switches the output stage
from the output of the amplifier to a known resistive
load. The value of the resistive load is determined by
the state of the power-down bits (PD1 and PD0).
*/
enum MCP4725PowerDownModes {
    MCP4725_POWER_DOWN_MODE_NORMAL = 0, // PD1=0, PD0=0
    MCP4725_POWER_DOWN_MODE_1K = 1,     // PD1=0, PD0=1
    MCP4725_POWER_DOWN_MODE_100K = 2,   // PD1=1, PD0=0
    MCP4725_POWER_DOWN_MODE_500K = 3    // PD1=1, PD0=1
};

//TODO: could optionally make bitfields for these to save space
typedef struct {
    uint8_t rdyFlag;
    uint8_t porFlag;
    MCP4725PowerDownModes dacPowerDownMode;
    uint16_t dacValue;
    MCP4725PowerDownModes eepromPowerDownMode;
    uint16_t eepromValue;
} MCP4725Data_t;

// TODO: Implement class
class MCP4725
{
    public:
        /// @brief TODO
        MCP4725();

        /// @brief TODO
        /// @return TODO
        bool begin();

        /// @brief Checks if device is connected by seeing if it acknowledges over I2C
        /// @return true if connected, false otherwise
        bool isConnected();

        /// @brief Updates DAC register in fast mode
        /// @param value 12-bit value to write to DAC register
        /// @param powerDownMode Power down mode to write to DAC register
        /// @return true if successful, false otherwise
        bool writeFastMode(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

        /// @brief Updates DAC register
        /// @param value 12-bit value to write to DAC register
        /// @return true if successful, false otherwise
        bool writeDac(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

        /// @brief Updates DAC register and EEPROM register
        /// @param value 12-bit value to write to DAC register
        /// @param powerDownMode Power down mode to write to DAC register
        /// @return true if successful, false otherwise
        bool writeDacEeprom(uint16_t value, MCP4725PowerDownModes powerDownMode = MCP4725_POWER_DOWN_MODE_NORMAL);

        /// @brief Reads DAC register and EEPROM register
        /// @param dacValue 12-bit value read from DAC register
        /// @param dacPowerDownMode Power down mode read from DAC register
        /// @param eepromValue 12-bit value read from EEPROM register
        /// @param eepromPowerDownMode Power down mode read from EEPROM register
        /// @return true if successful, false otherwise
        bool readDacEeprom(MCP4725Data_t &data);        
};
