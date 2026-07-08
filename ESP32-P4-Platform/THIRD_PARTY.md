# Third-Party Code

This repository includes or references third-party code so the examples are
easy to build and evaluate. Each third-party component remains governed by its
own license terms.

## Bundled or Example-Local Code

| Path | Project or source | Notes |
| --- | --- | --- |
| `examples/arduino/libraries/lvgl/` | LVGL | Bundled for Arduino examples; see the library's own license file. |
| `examples/arduino/libraries/GFX_Library_for_Arduino/` | Arduino_GFX | Bundled for Arduino display examples; see its metadata and license. |
| `examples/esp-idf/18_esp_brookesia_phone/components/brookesia_core/` | ESP-Brookesia core-related code | Example-local component; see included documentation and metadata. |
| `examples/esp-idf/18_esp_brookesia_phone/components/esp32_p4_platform/` | ESP32-P4 platform BSP-style component | Includes its own license file. |
| `examples/esp-idf/14_lvgl_demo_v9/components/bsp_extra/` | BSP helper code | Includes its own license file. |

## Managed Components

Several ESP-IDF examples use `idf_component.yml` to fetch managed components
from Espressif's component registry during build. Generated
`managed_components/` directories and `dependencies.lock` files are local build
outputs and should not be committed unless maintainers intentionally pin a
specific dependency snapshot.

## Maintainer Notes

When adding or updating third-party code:

- Keep the upstream license file with the bundled code.
- Record the project name, source, and version in this file or the example
  README.
- Prefer ESP-IDF managed components when that keeps the repository smaller and
  easier to update.
