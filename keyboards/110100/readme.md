# 110100

![110100](imgur.com image replace me!)

4x4 macro pad.

Keyboard Maintainer: [Takuya Urakawa (dm9records.com 5z6p.com)](https://github.com/hsgw)  
Hardware Supported: STM32F042K6  
Hardware Availability: TODO

Make example for this keyboard (after setting up your build environment):

    make 110100:default

## Update firmware
### Enter bootloader
1. Unplug USB cable (or push reset)
2. Push SW_MX2 key
3. Plug USB
4. Release SW_MX2 key

### Burn with dfu-util

    make 110100:default:dfu-util


See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
