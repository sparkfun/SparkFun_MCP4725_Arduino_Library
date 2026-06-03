/*
  This is a library written for the MCP4725 DAC Breakout
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/12918

  Written by SparkFun Electronics, June 2026

  https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library

  SparkFun code, firmware, and software is released under the MIT License.
  Please see LICENSE.md for more details.
*/

#include "sfDevMCP4725.h"
#include <cstddef>
#include <cstdint>

bool sfDevMCP4725::begin(sfTkIBus *theBus)
{
    // Setup Arduino I2C bus
    if (theBus == nullptr)
        return false;

    setCommunicationBus(theBus);

    // Check if device is connected
    return true;
}
void sfDevMCP4725::setCommunicationBus(sfTkIBus *theBus)
{
    _theBus = theBus;
}

bool sfDevMCP4725::writeFastMode(uint16_t value, MCP4725PowerDownModes powerDownMode)
{
    /*
    In Fast mode, writes take the form (see datasheet pg. 24):
    byte 0: C2=0 | C0=0 | PD1 | PD0 | D11 | D10 | D9 | D8
    byte 1: D7   | D6   | D5  | D4  | D3  | D2  | D1 | D0
    */
    size_t length = 2;
    uint8_t bytesToWrite[length];
    bytesToWrite[0] = (powerDownMode << 4) | ((value & 0x0F00) >> 8);
    bytesToWrite[1] = value & 0x00FF;

    if (_theBus->writeData(bytesToWrite, length) != ksfTkErrOk)
        return false;

    return true;
}

bool sfDevMCP4725::writeDac(uint16_t value, MCP4725PowerDownModes powerDownMode)
{
    /*
    Dac writes take the form (see datasheet pg. 25):
    byte 0: C2=0 | C1=1  | C0=0 | X  | X  | PD1 | PD0 | X
    byte 1: D11  | D10   | D9   | D8 | D7 | D6  | D5  | D4
    byte 2: D3   | D2    | D1   | D0 | X  | X   | X   | X
    */
    size_t length = 3;
    uint8_t bytesToWrite[length];
    bytesToWrite[0] = (0x40 | (powerDownMode << 1));
    bytesToWrite[1] = ((value & 0x0FF0) >> 4);
    bytesToWrite[2] = ((value & 0x000F) << 4);
    if (_theBus->writeData(bytesToWrite, length) != ksfTkErrOk)
        return false;

    return true;
}

bool sfDevMCP4725::writeDacEeprom(uint16_t value, MCP4725PowerDownModes powerDownMode)
{
    /*
    Dac writes take the form (see datasheet pg. 25):
    byte 0: C2=0 | C1=1  | C0=1 | X  | X  | PD1 | PD0 | X
    byte 1: D11  | D10   | D9   | D8 | D7 | D6  | D5  | D4
    byte 2: D3   | D2    | D1   | D0 | X  | X   | X   | X
    */
    size_t length = 3;
    uint8_t bytesToWrite[length];
    bytesToWrite[0] = (0x60 | (powerDownMode << 1));
    bytesToWrite[1] = ((value & 0x0FF0) >> 4);
    bytesToWrite[2] = ((value & 0x000F) << 4);

    if (_theBus->writeData(bytesToWrite, length) != ksfTkErrOk)
        return false;

    return true;
}

bool sfDevMCP4725::readDacEeprom(Mcp4725Data &data)
{
    /*
    Data Returned from Read commands take the form (see datasheet pg. 26):

    byte 0 (Settings):   RDY | POR | X   | X  | X   | PD1 | PD0 | X
    byte 1 (DAC Reg):    D11 | D10 | D9  | D8 | D7  | D6  | D5  | D4
    byte 2 (DAC Reg):    D3  | D2  | D1  | D0 | X   | X   | X   | X
    byte 3 (EEPROM Reg): X   | PD1 | PD0 | X  | D11 | D10 | D9  | D8
    byte 4 (EEPROM Reg): D7  | D6  | D5  | D4 | D3  | D2  | D1  | D0
    */

    size_t readLength = 5;
    uint8_t readBytes[readLength];
    size_t nRead = 0;

    // This device does not have any registers, and returns 6 bytes every time.
    if (_theBus->readRegister(nullptr, 0, readBytes, readLength, nRead) != ksfTkErrOk || nRead == 0)
        return false;

    data.rdyFlag = (readBytes[0] & 0x80) >> 7;
    data.porFlag = (readBytes[0] & 0x40) >> 6;
    data.dacPowerDownMode = static_cast<MCP4725PowerDownModes>((readBytes[0] & 0x06) >> 1);
    data.dacValue = (readBytes[1] << 4) | ((readBytes[2] & 0xF0) >> 4);
    data.eepromPowerDownMode = static_cast<MCP4725PowerDownModes>((readBytes[3] & 0x60) >> 5);
    data.eepromValue = ((readBytes[3] & 0x0F) << 8) | readBytes[4];

    return true;
}
