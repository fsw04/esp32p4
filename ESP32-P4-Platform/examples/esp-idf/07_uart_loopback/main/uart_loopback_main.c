/*
 * SPDX-FileCopyrightText: 2026 Waveshare
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

static const char *TAG = "uart_loopback";
static const uart_port_t UART_PORT = CONFIG_EXAMPLE_UART_PORT_NUM;
static const char *LOOPBACK_TEXT = "hello from esp32-p4 uart loopback\n";

void app_main(void)
{
    const uart_config_t uart_config = {
        .baud_rate = CONFIG_EXAMPLE_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    printf("\n");
    printf("========================================\n");
    printf(" UART Loopback Demo\n");
    printf("========================================\n");
    printf("Connect TX GPIO %d to RX GPIO %d.\n", CONFIG_EXAMPLE_UART_TX_GPIO, CONFIG_EXAMPLE_UART_RX_GPIO);
    printf("Baud rate: %d\n", CONFIG_EXAMPLE_UART_BAUD_RATE);
    printf("\n");

    ESP_ERROR_CHECK(uart_driver_install(UART_PORT, 1024, 1024, 0, NULL, 0));
    ESP_ERROR_CHECK(uart_param_config(UART_PORT, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_PORT,
                                 CONFIG_EXAMPLE_UART_TX_GPIO,
                                 CONFIG_EXAMPLE_UART_RX_GPIO,
                                 UART_PIN_NO_CHANGE,
                                 UART_PIN_NO_CHANGE));

    uint8_t rx_buffer[128];

    while (true) {
        uart_write_bytes(UART_PORT, LOOPBACK_TEXT, strlen(LOOPBACK_TEXT));

        int len = uart_read_bytes(UART_PORT, rx_buffer, sizeof(rx_buffer) - 1, pdMS_TO_TICKS(500));
        if (len > 0) {
            rx_buffer[len] = '\0';
            ESP_LOGI(TAG, "received %d bytes: %s", len, (char *)rx_buffer);
        } else {
            ESP_LOGW(TAG, "no data received; check TX/RX jumper and GPIO settings");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
