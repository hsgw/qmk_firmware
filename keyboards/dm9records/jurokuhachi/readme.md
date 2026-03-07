# dm9records/jurokuhachi

![dm9records/jurokuhachi](https://i.imgur.com/8replace.jpg)

16x8 or 16x16 matrix keyboard with RP2040 and LP5868 LED Driver.

* Keyboard Maintainer: [Takuya Urakawa](https://github.com/hsgw)
* Hardware Supported: jurokuhachi PCB, RP2040
* Hardware Availability: [5z6p.com](https://5z6p.com/products/jurokuhachi)

## Revisions

This keyboard supports two hardware configurations:
- **128**: 128-key version (16x8 matrix).
- **256**: 256-key version (16x16 matrix). Note: Due to QMK's `led_matrix` implementation using `uint8_t` for LED indices, only 255 LEDs are enabled in this revision.

## Build and Flash

Make example for this keyboard (after setting up your build environment):

    make dm9records/jurokuhachi/128:default
    make dm9records/jurokuhachi/256:default

Flashing example for this keyboard:

    make dm9records/jurokuhachi/128:default:flash
    make dm9records/jurokuhachi/256:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (the top left key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

