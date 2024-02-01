# ichi_pp

![ichi_pp](imgur.com image replace me!)

BIG SWITCH DESK LIGHT!!!!!!!!!!!

* Keyboard Maintainer: [Takuya Urakawa(Dm9Records, 5z6p.com)](https://github.com/hsgw)
* Hardware Supported: *The PCBs, controllers supported*
* Hardware Availability: *Links to where you can find this hardware*

Make example for this keyboard (after setting up your build environment):

    make dm9records/ichi_pp:default


Flashing example for this keyboard:

    make dm9records/ichi_pp/left:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the Big switch and plug in the keyboard
* **Physical reset button**: Press Reset and Boot on the PCB, disconnect from the PC, and then release Reset first.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
