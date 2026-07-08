ESP32-P4-Platform factory firmware

Board build: 7-DSI-TOUCH-A
Chip revision: ESP32-P4 rev3.x or later
Flash size: 16MB
ESP-IDF: v5.5.4
Default package: no

Flash separate images:
python -m esptool --chip esp32p4 -b 460800 --before default_reset --after hard_reset write_flash @flash_args

Flash merged image:
python -m esptool --chip esp32p4 -b 460800 --before default_reset --after hard_reset write_flash 0x0 merged-factory.bin
