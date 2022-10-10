#include <stdio.h>
#include "ble.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
void comunication(void *pvParameter){
    while(1)
	{
        
	    printf("Goodbye:");
	    vTaskDelay(1000 / portTICK_RATE_MS);
	}
}