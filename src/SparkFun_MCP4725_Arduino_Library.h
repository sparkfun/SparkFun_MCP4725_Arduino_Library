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
 * - isConnected(): Verifies sensor connection
 *
 * @section Dependencies Dependencies
 * - Arduino.h
 * - SparkFun_Toolkit.h
 * - sfeTCS3430.h
 *
 * @author SparkFun Electronics
 * @date 2026
 * @copyright Copyright (c) 2026, SparkFun Electronics Inc. All rights reserved.
 *
 * @section License License
 * SPDX-License-Identifier: MIT
 *
 * @section Product_Links Product Links
 *  TODO: Update link or remove
 * - Qwiic 1x1: https://www.sparkfun.com/products/
 *
 * @see https://github.com/sparkfun/SparkFun_TCS3430_Arduino_Library
 */

#pragma once

// clang-format off
 #include <SparkFun_Toolkit.h>
 #include "sfTk/sfDevMCP4725.h"
 #include <Arduino.h>
// clang-format on

/**
 * @class sfMCP4725
 * @brief Arduino I2C implementation for the MCP4725 digtal to analog converter.
 *
 * @details
 * This class provides Arduino-specific I2C communication implementation for the TCS3430 sensor.
 * It inherits from the base driver class and implements the I2C interface using Arduino's Wire library.
 * The class manages device addressing and connection verification.
 *
 * Example usage:
 * @code
 * SfeMCP4725ArdI2C sensor;
 * if (sensor.begin()) {
 *     // Sensor initialized successfully
 * }
 * @endcode
 *
 * @note This class uses the Arduino Wire library for I2C communication
 *
 * @see sfDevTCS3430
 * @see TwoWire
 *
 */
class SfeMCP4725ArdI2C : public sfMCP4725
{
  public:
    SfeMCP4725ArdI2C()
    {
    }

    /**
     * @brief Initializes the TCS3430 sensor with I2C communication.
     *
     * @details
     * This method performs the following initialization steps:
     * 1. Initializes I2C communication with device address and Wire port
     * 2. Enables repeat start support
     * 3. Sets up communication bus
     * 4. Verifies device connection
     * 5. Calls base class initialization
     *
     * @param address I2C address of the device (default: kDefaultTCS3430Addr)
     * @param wirePort TwoWire instance to use for I2C communication (default: Wire)
     *
     * @return true If initialization successful
     * @return false If any initialization step fails
     *
     * Example:
     * @code
     * SfeMCP4725ArdI2C sensor;
     * if (!sensor.begin()) {
     *     Serial.println("Sensor initialization failed!");
     *     while (1); // halt
     * }
     * @endcode
     */
    bool begin(const uint8_t &address = kTCS3430Addr, TwoWire &wirePort = Wire)
    {
        if (_theI2CBus.init(wirePort, address) != ksfTkErrOk)
            return false;

        setCommunicationBus(&_theI2CBus);

        if (!isConnected())
            return false;

        sfDevTCS3430::begin(&_theI2CBus);

        return true;
    }

    /**
     * @brief Checks if the TCS3430 sensor is connected and responding.
     *
     * @details
     * This method performs two checks:
     * 1. Attempts to ping the device at the current I2C address
     * 2. Verifies the device ID matches the expected TCS3430 ID
     *
     * @return true If device responds to ping and returns correct device ID
     * @return false If communication fails or device ID is incorrect
     *
     * Example:
     * @code
     * SfeMCP4725ArdI2C sensor;
     * if (!sensor.isConnected()) {
     *     Serial.println("Device not found or incorrect ID!");
     *     return;
     * }
     * @endcode
     */
    bool isConnected(void)
    {
        if (_theI2CBus.ping() != ksfTkErrOk)
            return false;

        // Check the device ID
        return (kDefaultTCS3430DeviceID == getDeviceID());
    }

    /**
     * @brief Gets the currently configured I2C address of the TCS3430 sensor.
     *
     * @details
     * Returns the I2C address currently being used to communicate with the sensor.
     *
     * @return uint8_t The current I2C address
     *
     * Example:
     * @code
     * SfeMCP4725ArdI2C sensor;
     * uint8_t address = sensor.getDeviceAddress();
     * Serial.print("Current I2C address: 0x");
     * Serial.println(address, HEX);
     * @endcode
     */
    uint8_t getDeviceAddress(void)
    {
        return _theI2CBus.address();
    }

  private:
    /**
     * @brief Arduino I2C bus interface instance for the TCS3430 sensor.
     *
     * @details
     * This member handles the low-level I2C communication between the Arduino and the TCS3430 sensor.
     *
     * The bus interface is configured during begin() and used by all communication methods.
     *
     * @see sfTkArdI2C
     * @see begin()
     */
    sfTkArdI2C _theI2CBus;
};
