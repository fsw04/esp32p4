# Firmware

This directory contains ESP32-P4 Platform factory firmware sources and prebuilt factory firmware packages.

## Layout

- `brookesia/`: ESP-IDF firmware project.
- `factory_firmware/`: prebuilt factory firmware packages.

## Default Factory Firmware

The default prebuilt firmware is:

- `factory_firmware/ESP32-P4-Platform_Factory_Firmware_10.1-DSI-TOUCH-A_rev3.x-or-later`

It targets ESP32-P4 rev3.x or later hardware with 16 MB flash. A 7-DSI-TOUCH-A build is also provided for the existing 7-inch configuration.

## Build

Use ESP-IDF v5.5 or later:

```sh
cd firmware/brookesia
idf.py set-target esp32p4
idf.py build
```

The firmware project resolves LVGL and `waveshare/esp32_p4_platform` from the ESP-IDF Component Registry.
