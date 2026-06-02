/**
 * @file SparkFun_MCP4725_Arduino_Library.h
 * @brief Arduino-specific implementation for the SparkFun MCP4725 DAC.
 *
 * @details
 * This file provides the Arduino-specific implementation of the MCP4725 driver
 * class. The SfeMCP4725ArdI2C class inherits from the base driver class and
 * implements the I2C communication interface using Arduino's Wire library.
 *
 * Key features:
 * - Arduino I2C initialization
 * - Connection verification
 * - Toolkit integration
 *
 * @section Class SfeMCP4725ArdI2C Class
 * - begin(): Initializes I2C communication
 * - isConnected(): Verifies device connection
 *
 * @section Dependencies Dependencies
 * - Arduino.h
 * - SparkFun_Toolkit.h
 * - sfDevMCP4725.h
 *
 * @author SparkFun Electronics
 * @date 2026
 * @copyright Copyright (c) 2026, SparkFun Electronics Inc. All rights reserved.
 *
 * @section License License
 * SPDX-License-Identifier: MIT
 *
 * @section Product_Links Product Links
 * - MCP4725 Breakout: https://www.sparkfun.com/products/12918
 *
 * @see https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library
 */

#pragma once

// clang-format off
 #include <SparkFun_Toolkit.h>
 #include "sfTk/sfDevMCP4725.h"
 #include <Arduino.h>
// clang-format on

/**
 * @class SfeMCP4725ArdI2C
 * @brief Arduino I2C implementation for the MCP4725 digital-to-analog converter.
 *
 * @details
 * This class provides Arduino-specific I2C communication implementation for the MCP4725 DAC.
 * It inherits from the base driver class and implements the I2C interface using Arduino's Wire library.
 * The class manages device addressing and connection verification.
 *
 * @note This class uses the Arduino Wire library for I2C communication
 *
 * @see sfDevMCP4725
 * @see TwoWire
 *
 */
class SfeMCP4725ArdI2C : public sfDevMCP4725
{
  public:
    SfeMCP4725ArdI2C()
    {
    }

    /**
     * @brief Initializes the MCP4725 DAC with I2C communication.
     *
     * @details
     * This method performs the following initialization steps:
     * 1. Initializes I2C communication with device address and Wire port
     * 2. Enables repeat start support
     * 3. Sets up communication bus
     * 4. Verifies device connection
     * 5. Calls base class initialization
     *
     * @param address I2C address of the device (default: MCP4725_ADDRESS)
     * @param wirePort TwoWire instance to use for I2C communication (default: Wire)
     *
     * @return true If initialization successful
     * @return false If any initialization step fails
     */
    bool begin(const uint8_t &address = MCP4725_ADDRESS, TwoWire &wirePort = Wire)
    {
        if (_theI2CBus.init(wirePort, address, true) != ksfTkErrOk)
            return false;

        sfDevMCP4725::begin(&_theI2CBus);

        if (isConnected() == false)
            return false;

        return true;
    }

    /**
     * @brief Checks if the MCP4725 DAC is connected and responding.
     *
     * @details
     * This method attempts to ping the device at the current I2C address
     *
     * @return true If device responds to ping and false otherwise.
     */
    bool isConnected(void)
    {
        return (_theI2CBus.ping() == ksfTkErrOk);
    }

    /**
     * @brief Gets the currently configured I2C address of the MCP4725 DAC.
     *
     * @details
     * Returns the I2C address currently being used to communicate with the device.
     *
     * @return uint8_t The current I2C address
     */
    uint8_t getDeviceAddress(void)
    {
        return _theI2CBus.address();
    }

  private:
    /**
     * @brief Arduino I2C bus interface instance for the MCP4725 DAC.
     *
     * @details
     * This member handles the low-level I2C communication between the Arduino and the MCP4725 DAC.
     *
     * The bus interface is configured during begin() and used by all communication methods.
     *
     * @see sfTkArdI2C
     * @see begin()
     */
    sfTkArdI2C _theI2CBus;
};
