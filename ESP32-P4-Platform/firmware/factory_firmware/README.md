# Factory Firmware

This directory contains prebuilt ESP32-P4-Platform factory firmware packages.

Default package:

- `ESP32-P4-Platform_Factory_Firmware_10.1-DSI-TOUCH-A_rev3.x-or-later`

Additional package:

- `ESP32-P4-Platform_Factory_Firmware_7-DSI-TOUCH-A_rev3.x-or-later`

Each package includes:

- individual flash images and `flash_args`
- `merged-factory.bin`
- `flasher_args.json`
- `SHA256SUMS.txt`
- `README.txt`

Flash separate images from inside a package directory:

```sh
python -m esptool --chip esp32p4 -b 460800 --before default_reset --after hard_reset write_flash @flash_args
```

Flash the merged image:

```sh
python -m esptool --chip esp32p4 -b 460800 --before default_reset --after hard_reset write_flash 0x0 merged-factory.bin
```
