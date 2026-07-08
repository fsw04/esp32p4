/*
 * SPDX-FileCopyrightText: 2026 Waveshare
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <stdio.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

static const char *TAG = "gpio_io";

void app_main(void)
{
    const gpio_num_t output_gpio = CONFIG_EXAMPLE_GPIO_OUTPUT;
    const gpio_num_t input_gpio = CONFIG_EXAMPLE_GPIO_INPUT;

    printf("\n");
    printf("========================================\n");
    printf(" GPIO IO Demo\n");
    printf("========================================\n");
    printf("Output GPIO: %d\n", output_gpio);
    printf("Input GPIO: %d\n", input_gpio);
    printf("Optional test: connect output GPIO to input GPIO and watch the input follow.\n");
    printf("\n");

    gpio_config_t output_config = {
        .pin_bit_mask = 1ULL << output_gpio,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&output_config));

    gpio_config_t input_config = {
        .pin_bit_mask = 1ULL << input_gpio,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = CONFIG_EXAMPLE_GPIO_INPUT_PULLUP ? GPIO_PULLUP_ENABLE : GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&input_config));

    bool level = false;

    while (true) {
        level = !level;
        ESP_ERROR_CHECK(gpio_set_level(output_gpio, level));

        int input_level = gpio_get_level(input_gpio);
        ESP_LOGI(TAG, "output=%d input=%d", level, input_level);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
