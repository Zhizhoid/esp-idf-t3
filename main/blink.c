#include "blink.h"
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"

extern const uint32_t BLINK_INTERVAL_MS;
extern const uint32_t LED_ON_TIME_MS;

static const gpio_num_t BLINK_GPIO =  GPIO_NUM_8;
static led_strip_handle_t blink_led_strip_handle;

static const uint32_t col_r = 0, col_g = 16, col_b = 16;

static void configure_led(void) {
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO,
        .max_leds = 1
    };

    led_strip_spi_config_t spi_config = {
        .spi_bus = SPI2_HOST,
        .flags = {
            .with_dma = true,
        }
    };

    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &blink_led_strip_handle));
    
    // TODO: maybe add checks
    led_strip_clear(blink_led_strip_handle);
}

// state: true - on, false - off 
static void set_led(bool state) {
    // TODO: maybe add checks
    if (state) {
        led_strip_set_pixel(blink_led_strip_handle, 0, col_r, col_g, col_b);
        led_strip_refresh(blink_led_strip_handle);
    }
    else {
        led_strip_clear(blink_led_strip_handle);
    }
}

void blink_task(void *pvParameters) {
    configure_led();

    TickType_t ticks_on = LED_ON_TIME_MS / portTICK_PERIOD_MS; 
    assert((BLINK_INTERVAL_MS / portTICK_PERIOD_MS) > ticks_on);

    TickType_t ticks_off = (BLINK_INTERVAL_MS / portTICK_PERIOD_MS) - ticks_on; 

    while (true) {
        set_led(true);
        vTaskDelay(ticks_on);
        set_led(false);
        vTaskDelay(ticks_off);
    }
}