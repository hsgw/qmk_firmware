# nigo

![nigo](imgur.com image replace me!)

2x5 low profile macropad.

Two variations are available depending on the orientation of the keyboard. Either one can be used by changing the firmware.

-   Keyboard Maintainer: [Takuya Urakawa(Dm9Records, 5z6p.com)](https://github.com/hsgw)
-   Hardware Supported: _The PCBs, controllers supported_
-   Hardware Availability: _Links to where you can find this hardware_

Make example for this keyboard (after setting up your build environment):

    make dm9records/nigo/default
    (or)
    make dm9records/nigo/default

Flashing example for this keyboard:

    make dm9records/nigo/default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader:

-   **Physical reset button**: Press Reset and Boot on the PCB, disconnect from the PC, and then release Reset first.
-   **keycode and bootmagic reset is not working**: stm32f042xx devices are not able to enter bootloader from software.
