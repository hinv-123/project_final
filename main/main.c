
// #include "esp_timer.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
//#include "Ds1302.h"
#include "blink.h"
#include "ble.h"

#define BLINK_GPIO 2
#define LDR 12
#define Button 13


Ds1302 rtc(15,14,16);
uint32_t count = 0;
volatile uint8_t led_status =0;

void IRAM_ATTK gpio_handler(void *pvParameter)
{
    while(1) {
        printf("Button pressed/n");
        if(led_status == 0) 
        {      
            led_status = 1;
        } 
        else if (led_status == 1)
        { 
            led_status = 0;
        }
    }
}

void LED_LDR(void *pvParameter)
{
	int LightLevel = analogRead(LDR);
	while(1)
	{
	    if(LightLevel <= 500) 
        {      
            led_status = 1;
        } 
        else 
        { 
            led_status = 0;
        }
	}
}


void RTC(void *pvParameter)
{    
    rtc.begin();
    rtc.adjust(DateTime(__DATE__, __TIME__));
    while (1)
    {
        DateTime t = rtc.now();
        if(rtc.sec>0&&rtc.min==0&&rtc.hour==12)
        {
            led_state = 1;
        } 
        else
        {
            led_state = 0;
        }
    }
}

void app_main()
{
    xTaskCreate(&LED_LDR, "LDR", 2048, NULL, 5, NULL); // prority esp: button đọc từ ngắt -> freeRTOS ISR
	xTaskCreate(&RTC, "rtc", 2048,NULL,5,NULL );
    gpio_isr_handler_add(BLINK_GPIO, gpio_handler, (void*) BLINK_GPIO);
}
