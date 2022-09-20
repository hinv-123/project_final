#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
// #include "esp_timer.h"
#define BLINK_GPIO 2

uint32_t count = 0;
volatile uint8_t led_status =0;
//isr
void timer_callback(void *args)
{
    printf("INTERRUPT\n");
}

void hello_task(void *pvParameter)
{
	while(1)
	{
        
	    printf("Hello world: %d!\n",count++);
	    vTaskDelay(2000 / portTICK_RATE_MS);
	}
}
void blinky(void *pvParameter)
{
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    while(1) {
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(1000 / portTICK_RATE_MS);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void comunication(void *pvParameter)
{
    // const esp_timer_create_args_t esp_timer_create_args = {
    //     .callback = timer_callback,
    //     .name = "My timer"};
    // esp_timer_handle_t esp_timer_handle; //handler
    // esp_timer_create(&esp_timer_create_args, &esp_timer_handle);
    // esp_timer_start_periodic(esp_timer_handle, 4000); //Inicia el timer en microsegundos
    while(1)
	{
        
	    printf("Goodbye: %d!\n",count++);
	    vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

void app_main()
{
    xTaskCreate(&hello_task, "hello_task", 2048, NULL, 5, NULL);
    xTaskCreate(&blinky, "blinky", 512,NULL,5,NULL );
    xTaskCreate(&comunication, "comunication", 2048,NULL,5,NULL );
}
