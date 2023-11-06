#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define ESP_INR_FLAG_DEFAULT 0
#define PUSH_BUTTON_PIN  39

TaskHandle_t myTaskHandle = NULL;
TaskHandle_t ISR = NULL;

int count = 3;

void print_ID(void *arg)
{
    while(1){
        printf("2010928\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void IRAM_ATTR button_isr_handler(void *arg){
	xTaskResumeFromISR(ISR);
}

void interrupt_task(void *arg){
	while(1){
		vTaskSuspend(NULL);
		if (count == 0) {
			printf("ESP32\n");
			count = 3;
		}

		if (gpio_get_level(PUSH_BUTTON_PIN) == 0) {
			count--;
		}
		else {
			count = 3;
		}
	}
}

void app_main(void)
{
	esp_rom_gpio_pad_select_gpio(PUSH_BUTTON_PIN);
	gpio_set_direction(PUSH_BUTTON_PIN, GPIO_MODE_INPUT);
	gpio_set_intr_type(PUSH_BUTTON_PIN, GPIO_INTR_POSEDGE);
	gpio_set_pull_mode(PUSH_BUTTON_PIN, GPIO_PULLUP_ONLY);
	gpio_install_isr_service(ESP_INR_FLAG_DEFAULT);
	gpio_isr_handler_add(PUSH_BUTTON_PIN, button_isr_handler, NULL);

	xTaskCreate(interrupt_task, "interrupt_task", 4096, NULL, 10, &ISR);
	xTaskCreatePinnedToCore(print_ID, "print_ID", 4096, NULL, 10, &myTaskHandle, 1);
}
