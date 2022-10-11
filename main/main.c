
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"
#include "driver/timer.h"
#include "ble.h"

#define ESP_INTR_FLAG_DEFAULT 0
#define BLINK_GPIO 2
#define BUTTON_PIN 0

static bool led_status = false;
TaskHandle_t ISR = NULL;

void IRAM_ATTR button_isr_handler (void* arg) {
    xTaskResumeFromISR(ISR);
}
void button_task (void* arg) {
    gpio_pad_select_gpio(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN,GPIO_MODE_INPUT);

    gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT); 

    gpio_isr_handler_add(BUTTON_PIN, button_isr_handler, NULL);
    
    while(1) {
        vTaskSuspend(NULL);
        led_status = !led_status;
        gpio_set_level(BLINK_GPIO, led_status);
        printf("Button pressed \n");
    }
}

void app_main()
{ 
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO,GPIO_MODE_OUTPUT);

    xTaskCreate(button_task,"button", 2048, NULL, 10, &ISR);
}
