#include "board_strip.h"
#include "esp_log.h"
#include "led_strip.h"

// Set to 1 to use DMA for driving the LED strip, 0 otherwise
// Please note the RMT DMA feature is only available on chips e.g. ESP32-S3/P4
#define LED_STRIP_USE_DMA  1

#if LED_STRIP_USE_DMA
// Numbers of the LED in the strip
#define LED_STRIP_MEMORY_BLOCK_WORDS 1024 // this determines the DMA block size
#else
// Numbers of the LED in the strip
#define LED_STRIP_MEMORY_BLOCK_WORDS 0 // let the driver choose a proper memory block size automatically
#endif // LED_STRIP_USE_DMA

// GPIO assignment
#define LED_STRIP_GPIO_PIN  18

// 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define LED_STRIP_RMT_RES_HZ  (10 * 1000 * 1000)

static led_strip_handle_t led_strip_dev;

void board_strip_init(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO_PIN, // The GPIO that connected to the LED strip's data line
        .max_leds = BOARD_STRIP_COUNT,        // The number of LEDs in the strip,
        .led_model = LED_MODEL_WS2812,        // LED strip model
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB, // The color order of the strip: GRB
        .flags = {
            .invert_out = false,              // don't invert the output signal
        }
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,        // different clock source can lead to different power consumption
        .resolution_hz = LED_STRIP_RMT_RES_HZ, // RMT counter clock frequency
        .mem_block_symbols = LED_STRIP_MEMORY_BLOCK_WORDS, // the memory block size used by the RMT channel
        .flags = {
            .with_dma = LED_STRIP_USE_DMA,     // Using DMA can improve performance when driving more LEDs
        }
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip_dev));
    ESP_LOGI("Board", "Led strip initialized");
}

void board_strip_set_pixel(uint32_t index, uint32_t red, uint32_t green, uint32_t blue)
{
    ESP_ERROR_CHECK(led_strip_set_pixel(led_strip_dev, index, red, green, blue));
}

void board_strip_refresh(void)
{
    ESP_ERROR_CHECK(led_strip_refresh(led_strip_dev));
}

void board_strip_clear(void)
{
    ESP_ERROR_CHECK(led_strip_clear(led_strip_dev));
}