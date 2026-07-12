/*
 * SPDX-FileCopyrightText: 2026 Waveshare
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"

static const char *TAG = "nvs_counter";
static const char *NVS_NAMESPACE = "demo";
static const char *NVS_KEY_BOOT_COUNT = "boot_count";

static void init_nvs(void)
{
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());  // 空间不足或版本不兼容时擦除
        err = nvs_flash_init();              // 重新初始化
    }
    ESP_ERROR_CHECK(err);
}

void app_main(void)
{
    nvs_handle_t nvs_handle;
    uint32_t boot_count = 0;

    // 1.初始化 NVS
    init_nvs();

    // 2.打开 NVS 读写句柄，配置命名空间
    ESP_ERROR_CHECK(nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs_handle));

    //3.首次烧录或擦除 flash 后，键 "boot_count" 不存在，返回 ESP_ERR_NVS_NOT_FOUND
    esp_err_t err = nvs_get_u32(nvs_handle, NVS_KEY_BOOT_COUNT, &boot_count);
    if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGI(TAG, "No saved boot count yet. Starting from zero.");
    } else {
        ESP_ERROR_CHECK(err);
    }

    // 4.nvs_set_u32 将新值写入内存缓存
    // 5.nvs_commit 至关重要：只有调用它后，数据才真正写入 Flash，掉电后才不会丢失
    // 6.nvs_close 关闭句柄，释放资源
    // open → use → commit → close
    boot_count++;
    ESP_ERROR_CHECK(nvs_set_u32(nvs_handle, NVS_KEY_BOOT_COUNT, boot_count));
    ESP_ERROR_CHECK(nvs_commit(nvs_handle));
    nvs_close(nvs_handle);

    printf("\n");
    printf("========================================\n");
    printf(" NVS Counter Demo\n");
    printf("========================================\n");
    printf("Saved boot count: %" PRIu32 "\n", boot_count);
    printf("Press reset. The number should increase after each boot.\n");
    printf("Erase flash if you want to reset the counter.\n");
    printf("\n");

    while (true) {
        ESP_LOGI(TAG, "running: boot_count=%" PRIu32, boot_count);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
