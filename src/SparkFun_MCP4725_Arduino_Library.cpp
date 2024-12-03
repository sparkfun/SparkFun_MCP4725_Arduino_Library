/*
  This is a library written for the MCP4725 DAC Breakout
  SparkFun sells these at its website: www.sparkfun.com
  Do you like this library? Help support SparkFun. Buy a board!
  https://www.sparkfun.com/products/12918

  Written by SparkFun Electronics, December, 2024

  https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library

  Development environment specifics:
  Arduino IDE 1.8.13

  SparkFun code, firmware, and software is released under the MIT License.
  Please see LICENSE.md for more details.
*/

#include "SparkFun_MCP4725_Arduino_Library.h"

//TODO: We likely will pull in the sfe_bus toolkit which will make all the Wire calls look a bit different...
MCP4725::MCP4725()
{
    Wire.begin();
}

bool MCP4725::isConnected(){
    Wire.beginTransmission(MCP4725_ADDR);
    return Wire.endTransmission() == 0;
}

bool MCP4725::begin()
{
    return isConnected();
}

bool MCP4725::writeFastMode(uint16_t value, MCP4725PowerDownModes powerDownMode){
    Wire.beginTransmission(MCP4725_ADDR);
    /*
    In Fast mode, writes take the form (see datasheet pg. 24): 
    byte 0: C2=0 | C0=0 | PD1 | PD0 | D11 | D10 | D9 | D8
    byte 1: D7   | D6   | D5  | D4  | D3  | D2  | D1 | D0
    */
    Wire.write ((powerDownMode << 4) | ( (value & 0x0F00) >> 8 )); // byte 0 
    Wire.write (value & 0x00FF); // byte 1
    return Wire.endTransmission() == 0;
}

bool MCP4725::writeDac(uint16_t value, MCP4725PowerDownModes powerDownMode){
    wire.beginTransmission(MCP4725_ADDR);
    /*
    Dac writes take the form (see datasheet pg. 25): 
    byte 0: C2=0 | C1=1  | C0=0 | X  | X  | PD1 | PD0 | X
    byte 1: D11  | D10   | D9   | D8 | D7 | D6  | D5  | D4
    byte 2: D3   | D2    | D1   | D0 | X  | X   | X   | X
    */
    Wire.write(0x40 | (powerDownMode << 1)) // byte 0
    Wire.write((value & 0x0FF0 >> 4)); // byte 1
    Wire.write((value & 0x000F) << 4); // byte 2
    return Wire.endTransmission() == 0;
}

bool MCP4725::writeDacEeprom(uint16_t value, MCP4725PowerDownModes powerDownMode){
    wire.beginTransmission(MCP4725_ADDR);
    /*
    Dac writes take the form (see datasheet pg. 25): 
    byte 0: C2=0 | C1=1  | C0=1 | X  | X  | PD1 | PD0 | X
    byte 1: D11  | D10   | D9   | D8 | D7 | D6  | D5  | D4
    byte 2: D3   | D2    | D1   | D0 | X  | X   | X   | X
    */
    Wire.write(0x60 | (powerDownMode << 1)) // byte 0
    Wire.write((value & 0x0FF0 >> 4)); // byte 1
    Wire.write((value & 0x000F) << 4); // byte 2
    return Wire.endTransmission() == 0;
}

bool MCP4725::readDacEeprom(MCP4725Data_t &data){
    Wire.beginTransmission(MCP4725_ADDR);
    /*
    Data Returned from Read commands take the form (see datasheet pg. 26):
    
    byte 0 (Settings):   RDY | POR | X   | X  | X   | PD1 | PD0 | X
    byte 1 (DAC Reg):    D11 | D10 | D9  | D8 | D7  | D6  | D5  | D4
    byte 2 (DAC Reg):    D3  | D2  | D1  | D0 | X   | X   | X   | X
    byte 3 (EEPROM Reg): X   | PD1 | PD0 | X  | D11 | D10 | D9  | D8
    byte 4 (EEPROM Reg): D7  | D6  | D5  | D4 | D3  | D2  | D1  | D0
    */

    uint16_t nRead = Wire.requestFrom(MCP4725_ADDR, 5);
    if (nRead != 5){
        return false;
    }

    uint8_t readBytes[5];
    for (int i = 0; i < 5; i++){
        readBytes[i] = Wire.read();
    }

    Wire.endTransmission();

    data.rdyFlag = (readBytes[0] & 0x80) >> 7;
    data.porFlag = (readBytes[0] & 0x40) >> 6;
    data.dacPowerDownMode = static_cast<MCP4725PowerDownModes>((readBytes[0] & 0x06) >> 1);
    data.dacValue = (readBytes[1] << 4) | ( (readBytes[2] & 0xF0) >> 4);
    data.eepromPowerDownMode = static_cast<MCP4725PowerDownModes>((readBytes[3] & 0x60) >> 1);
    data.eepromValue = ( (readBytes[3] & 0x0F) << 8) | readBytes[4];

    return true;
}