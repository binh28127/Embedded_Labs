#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//#define configUSE_PREEMPTION 0	//C:\Espressif\frameworks\esp-idf-v5.0.2\components\freertos\esp_additions\include\freertos\FreeRTOSConfig.h
//#define configUSE_TIME_SLICING 0
//#define configIDLE_SHOULD_YIELD 0

//static const char *pcTextForTask1 = "Task 1 is running\r\n";
//static const char *pcTextForTask2 = "Task 2 is running\r\n";

volatile uint32_t ulIdleCycleCount = 0UL ;

void vApplicationIdleHook(void)
{
	ulIdleCycleCount++;
}

//void vTaskFunction(void *pvParameters)
//{
//	char *pcTaskName;
//	const TickType_t xDelay250ms = pdMS_TO_TICKS(250);
//
//	pcTaskName = (char *)pvParameters;
//
//	while(1) {
////		vPrintString(pcTaskName);
//		printf("%s", pcTaskName);
//		vTaskDelay(xDelay250ms);
//	}
//}

void Task1(void *pvParameter) {
	int count = 0;
    while(1) {
		printf("\nTask 1 BEGIN -> [%d] : %lu\n", count, xTaskGetTickCount());
		for(int i = 0; i < 1000 ; i++) {
			printf("1");
		}
		count++;
		printf("\nTask 1 END : %lu\n", xTaskGetTickCount());
		vTaskDelay(pdMS_TO_TICKS(150));
    }
    vTaskDelete(NULL);
}

void Task2(void * pvParameter) {
	int count = 0;
    while(1) {
		printf("\nTask 2 BEGIN -> [%d] : %lu\n", count, xTaskGetTickCount());
		for(int i = 0; i < 200 ; i++) {
			printf("2");
		}
		count++;
		printf("\nTask 2 END : %lu\n", xTaskGetTickCount());
		vTaskDelay(pdMS_TO_TICKS(50));
    }
    vTaskDelete(NULL);
}

void Task3(void * pvParameter) {
	int count = 0;
    while(1) {
        printf("\nTask 3 BEGIN -> [%d] : %lu\n", count, xTaskGetTickCount());
        for(int i = 0; i < 5000 ; i++) {
        	printf("3");
        }
        count++;
        printf("\nTask 3 END : %lu\n", xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(10));
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
	xTaskCreate(Task1, "Task 1", 2048, NULL, 1, NULL);
	xTaskCreate(Task2, "Task 2", 2048, NULL, 2, NULL);
	xTaskCreate(Task3, "Task 3", 4096, NULL, 0, NULL);

//	vTaskStartScheduler();
}

