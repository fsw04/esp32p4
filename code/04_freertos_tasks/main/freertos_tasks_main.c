/*
 * SPDX-FileCopyrightText: 2026 Waveshare
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"

// sequence 占 4 字节（地址 0~3）
// 填充 4 字节（地址 4~7），让 uptime_ms 对齐到 8 的倍数
// uptime_ms 占 8 字节（地址 8~15）
// 结构体总大小必须是最大成员对齐值（8）的整数倍 → 16 刚好满足

typedef struct {
    uint32_t sequence;
    int64_t uptime_ms;
} demo_message_t;



static const char *TAG = "freertos_tasks";
static QueueHandle_t s_demo_queue;

static void producer_task(void *arg)
{
    uint32_t sequence = 0;

    while (true) {
        demo_message_t msg = {
            .sequence = sequence++,
            .uptime_ms = esp_timer_get_time() / 1000,
        };

        //每 1 秒（vTaskDelay(pdMS_TO_TICKS(1000))）生产一条消息
        // xQueueSend 的阻塞时间为 100ms：如果队列已满，等待 100ms 后返回 errQUEUE_FULL
        // 由于消费者处理很快（只是打印日志），队列几乎不会满

        if (xQueueSend(s_demo_queue, &msg, pdMS_TO_TICKS(100)) == pdPASS) {
            ESP_LOGI(TAG, "producer sent message %" PRIu32, msg.sequence);
        } else {
            ESP_LOGW(TAG, "producer queue full");
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

static void consumer_task(void *arg)
{
    demo_message_t msg;

    while (true) {
        //portMAX_DELAY 表示无限阻塞：队列空时，任务挂起，不消耗 CPU
        // 一旦队列有数据，消费者立即被唤醒并处理
        
        if (xQueueReceive(s_demo_queue, &msg, portMAX_DELAY) == pdPASS) {
            ESP_LOGI(TAG, "consumer received message %" PRIu32 " at %" PRId64 " ms",
                     msg.sequence, msg.uptime_ms);
        }
    }
}

void app_main(void)
{
    printf("\n");
    printf("========================================\n");
    printf(" FreeRTOS Tasks Demo\n");
    printf("========================================\n");
    printf("This demo creates a producer task, a consumer task, and a queue.\n");
    printf("Watch the serial monitor to see messages move between tasks.\n");
    printf("\n");

    //创建队列, 队列大小为5
    //队列在 FreeRTOS 中是深拷贝机制：xQueueSend 会把整个结构体的数据复制到队列内部缓冲区，而不是传递指针。

    s_demo_queue = xQueueCreate(5, sizeof(demo_message_t));
    if (s_demo_queue == NULL) {
        ESP_LOGE(TAG, "failed to create queue");
        return;
    }

    xTaskCreate(producer_task, "producer", 3072, NULL, 5, NULL);
    xTaskCreate(consumer_task, "consumer", 3072, NULL, 5, NULL);
    ESP_LOGI(TAG, "sizeof(demo_message_t) = %d", sizeof(demo_message_t));
}
