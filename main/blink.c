#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern uint32_t BLINK_INTERVAL_MS;
extern uint32_t LED_ON_TIME;

static void configure_led(void) {
    // ...
}

// state: true - on, false - off 
static void set_led(bool state) {
    // ...
}

void blink_task(void *pvParameters) {
    // TODO: configure LED
    while (true) {
        // ...
        vTaskDelay(LED_ON_TIME / portTICK_PERIOD_MS);
        // ...
        vTaskDelay(BLINK_INTERVAL_MS - LED_ON_TIME / portTICK_PERIOD_MS);
    }
}