
![SparkFun MCP4725 Arduino Library](docs/images/gh-banner-mcp4725-ard.png  "SparkFun 12-Bit DAC Breakout - MCP4725")

# SparkFun MCP4725 Arduino Library

Arduino Library for the SparkFun MCP4725 Arduino Library

![GitHub License](https://img.shields.io/github/license/sparkfun/SparkFun_MCP4725_Arduino_Library)
![Release](https://img.shields.io/github/v/release/sparkfun/SparkFun_MCP4725_Arduino_Library)
![Release Date](https://img.shields.io/github/release-date/sparkfun/SparkFun_MCP4725_Arduino_Library)
![Documentation - build](https://img.shields.io/github/actions/workflow/status/sparkfun/SparkFun_MCP4725_Arduino_Library/build-deploy-ghpages.yml?label=doc%20build)
[![Compile Test](https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library/actions/workflows/cross-compilation.yml/badge.svg)](https://github.com/sparkfun/SparkFun_MCP4725_Arduino_Library/actions/workflows/cross-compilation.yml)
![GitHub issues](https://img.shields.io/github/issues/sparkfun/SparkFun_MCP4725_Arduino_Library)

The SparkFun MCP4725 Arduino Library provides full control over Microchip's MCP4725, a 12-bit single-channel I2C digital-to-analog converter (DAC). The MCP4725 is compatible with SparkFun's Qwiic connect system, so no soldering is required to get started. An onboard EEPROM allows the device to retain its DAC value and power-down settings across power cycles, making it ideal for applications that require a consistent analog output at startup.

This library is available in the Arduino Library Manager; search for **SparkFun MCP4725**.

This library allows you to:

* Set a 12-bit DAC output value (0–4095)
* Use fast-mode writes for high-speed waveform generation
* Persist DAC values and power-down settings to onboard EEPROM
* Read back the current DAC register and EEPROM contents
* Configure three power-down modes (1 kΩ, 100 kΩ, and 500 kΩ load to GND)

# Repository Contents

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE.
* **/src** - Source files for the library (.cpp, .h).
* **/docs** - Datasheet for the MCP4725.
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE.
* **library.properties** - General library properties for the Arduino package manager.

# Documentation

* **[Library Documentation](https://docs.sparkfun.com/SparkFun_MCP4725_Arduino_Library/)** - Arduino Library Documentation for the SparkFun MCP4725 breakout boards.
* **[Hookup Guide](https://docs.sparkfun.com/SparkFun_Qwiic_DAC_MCP4725/)** - Hookup guide for the SparkFun MCP4725 breakout boards.
* **[Installing an Arduino Library Guide](https://learn.sparkfun.com/tutorials/installing-an-arduino-library)** - Basic information on how to install an Arduino library.
* **[Hardware GitHub Repository - Qwiic 1x1](TODO)** - Main repository (including hardware files) for the SparkFun Qwiic MCP4725 Breakout.
* **[Hardware GitHub Repository - Breakout](TODO)** - Main repository (including hardware files) for the SparkFun I2C DAC Breakout.

## Products That Use This Library

* [[BOB-31206]](https://www.sparkfun.com/sparkfun-qwiic-12-bit-dac-breakout-mcp4725.html) - SparkFun Qwiic 12-Bit DAC Breakout - MCP4725
* [[TODO: SKU]](https://www.sparkfun.com/sparkfun-i2c-dac-breakout-mcp4725.html) - SparkFun I2C DAC Breakout - MCP4725

## License Information

This product is ***open source***!

This product is licensed using the [MIT Open Source License](https://opensource.org/license/mit)
