#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "example"; // 定义日志标签

static const gpio_num_t LED_PIN = GPIO_NUM_2; // LED 连接的 GPIO 引脚
#define LEDC_CHANNEL LEDC_CHANNEL_0           // LEDC 通道
#define LEDC_TIMER LEDC_TIMER_0               // LEDC 定时器
#define LEDC_MODE LEDC_LOW_SPEED_MODE         // LEDC 速度模式, 低速模式
#define LEDC_DUTY_RES LEDC_TIMER_10_BIT       // PWM 占空比分辨率 (10-bit, 0-1023)
#define LEDC_FREQUENCY 1000                   // PWM 频率 (1 kHz)

void app_main(void)
{
    // 配置 LEDC 定时器
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_MODE,          // 设置速度模式
        .duty_resolution = LEDC_DUTY_RES, // 设置占空比分辨率
        .timer_num = LEDC_TIMER,          // 选择定时器
        .freq_hz = LEDC_FREQUENCY         // 设置 PWM 频率
    };
    ledc_timer_config(&ledc_timer);       // 应用定时器配置

    // 配置 LEDC 通道
    ledc_channel_config_t ledc_channel = {
        .gpio_num = LED_PIN,     // 通道输出的 GPIO 引脚
        .speed_mode = LEDC_MODE, // 设置速度模式 (与定时器一致)
        .channel = LEDC_CHANNEL, // 选择 LEDC 通道
        .timer_sel = LEDC_TIMER, // 选择该通道使用的定时器
        .duty = 0                // 设置初始占空比为 0
    };
    ledc_channel_config(&ledc_channel); // 应用通道配置

    while (1)
    {
        // 渐亮
        ESP_LOGI(TAG, "LED Fade in");
        for (int duty = 0; duty <= 1023; duty += 16)
        {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty); // 设置占空比
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);    // 更新占空比使其生效
            vTaskDelay(pdMS_TO_TICKS(20));                // 延时 20 毫秒
        }

        // 渐暗
        ESP_LOGI(TAG, "LED Fade out");
        for (int duty = 1023; duty >= 0; duty -= 16)
        {
            ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, duty); // 设置占空比
            ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);    // 更新占空比使其生效
            vTaskDelay(pdMS_TO_TICKS(20));                // 延时 20 毫秒
        }
    }
}