#include "blink.h"
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern uint32_t BLINK_INTERVAL_MS;
extern uint32_t LED_ON_TIME_MS;

static void configure_led(void) {
    // TODO
    printf("configuring...\n");
}

// state: true - on, false - off 
static void set_led(bool state) {
    printf("%s\n", state ? "on" : "off");
    // TODO
}

void blink_task(void *pvParameters) {
    assert(LED_ON_TIME_MS <= BLINK_INTERVAL_MS);
    configure_led();

    while (true) {
        set_led(true);
        vTaskDelay(LED_ON_TIME_MS / portTICK_PERIOD_MS);
        set_led(false);
        vTaskDelay((BLINK_INTERVAL_MS - LED_ON_TIME_MS) / portTICK_PERIOD_MS);
    }
}