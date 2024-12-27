#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "freertos/queue.h"
#include "esp_timer.h"

#include "blink.h"

const uint32_t COUNTER_INCR_TASK_STACK_DEPTH = 4096;
const uint32_t COUNTER_LOG_TASK_STACK_DEPTH = 4096;
const uint32_t BLINK_TASK_STACK_DEPTH = 4096;

const UBaseType_t COUNTER_QUEUE_SIZE = 8;
const UBaseType_t LOG_INTERVAL_QUEUE_SIZE = 1024;

const uint32_t COUNTER_INCR_INTERVAL_MS = 5000;
const uint32_t LOG_CHECK_INTERVAL_MS = 100;
const uint32_t BLINK_INTERVAL_MS = 1000;
const uint32_t LED_ON_TIME_MS = 100;

static const char *TAG = "Main";

static TaskHandle_t counter_incr_task_handle = NULL;
static TaskHandle_t counter_log_task_handle = NULL;
static TaskHandle_t blink_task_handle = NULL;

static QueueHandle_t counter_queue_handle = NULL;
static QueueHandle_t log_interval_queue_handle = NULL;

static void counter_incr_task(void *pvParameters) {
    uint32_t counter = 0;
    while (true) {
        counter++;

        if (xQueueSendToBack(counter_queue_handle, (void *)&counter, 0) != pdTRUE) {
            ESP_LOGE(TAG, "The counter queue is full. Counter value was not pushed to the queue.");
        }
        
        vTaskDelay(COUNTER_INCR_INTERVAL_MS / portTICK_PERIOD_MS);
    }
}

static void counter_log_task(void *pvParameters) {
    uint32_t counter_record;
    // time is in microseconds
    int64_t prev_time_usec = 0;
    
    while (true) {
        if (xQueueReceive(counter_queue_handle, (void *)&counter_record, 0)) {
            ESP_LOGI(TAG, "%lu", counter_record);

            int64_t delta_time_usec = esp_timer_get_time() - prev_time_usec;
            
            if (prev_time_usec != 0) {
                if (xQueueSendToBack(log_interval_queue_handle, (void *)&delta_time_usec, 0) != pdTRUE) {
                    ESP_LOGE(TAG, "The log interval queue is full. Time difference between logs was not pushed to the queue.");
                }
            }

            prev_time_usec += delta_time_usec;
        }
        vTaskDelay(LOG_CHECK_INTERVAL_MS / portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    counter_queue_handle = xQueueCreate(COUNTER_QUEUE_SIZE, sizeof(uint32_t));
    assert(counter_queue_handle != NULL);
    
    log_interval_queue_handle = xQueueCreate(LOG_INTERVAL_QUEUE_SIZE, sizeof(int64_t));
    assert(log_interval_queue_handle != NULL);

    xTaskCreate(counter_incr_task, "COUNTER_INCR", COUNTER_INCR_TASK_STACK_DEPTH, NULL, 1, &counter_incr_task_handle);
    xTaskCreate(counter_log_task, "COUNTER_LOG", COUNTER_LOG_TASK_STACK_DEPTH, NULL, 1, &counter_log_task_handle);
    xTaskCreate(blink_task, "BLINK", BLINK_TASK_STACK_DEPTH, NULL, 1, &blink_task_handle);

    int64_t test;
    while (true) {
        if (xQueueReceive(log_interval_queue_handle, (void *)&test, 0)) {
            printf("%lld\n", test);
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
