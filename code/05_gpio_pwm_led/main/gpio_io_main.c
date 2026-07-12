#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "example";

static const gpio_num_t LED_PIN = GPIO_NUM_2;
#define LEDC_CHANNEL    LEDC_CHANNEL_0
#define LEDC_TIMER      LEDC_TIMER_0
#define LEDC_MODE       LEDC_LOW_SPEED_MODE
#define LEDC_DUTY_RES   LEDC_TIMER_10_BIT
#define LEDC_FREQUENCY  1000

void app_main(void)
{
    // 配置 LEDC 定时器
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_DUTY_RES,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,
        .clk_cfg          = LEDC_AUTO_CLK,
        .deconfigure      = false
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // 配置 LEDC 通道
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = LED_PIN,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0,
        .hpoint         = 0,
        .flags          = {
            .output_invert = 0
        }
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    while (1)
    {
        // 渐亮
        ESP_LOGI(TAG, "LED Fade in");
        for (int duty = 0; duty <= 1023; duty += 16)
        {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(20));
        }

        // 渐暗
        ESP_LOGI(TAG, "LED Fade out");
        for (int duty = 1023; duty >= 0; duty -= 16)
        {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty);
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
            vTaskDelay(pdMS_TO_TICKS(20));
        }
    }
}