#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define QUEUE_SIZE 10

#define TOTAL_TASKS 3
#define TASK1_ID    0
#define TASK2_ID    1
#define TASK3_ID    2

typedef struct {
    int  taskID;
    char requestMsg[50];
} Request;

QueueHandle_t xQueue;

void ReceptionTask(void *pvParameter)
{
    Request xRequest;
    while(1)
	{
        xRequest.taskID = rand() % TOTAL_TASKS;
        if(xQueueSend(xQueue, &xRequest, pdMS_TO_TICKS(100)) != pdPASS) {
            printf("ReceptionTask: Failed to send request to the queue\n");
        } else {
            printf("ReceptionTask: Request for Task %d\n", xRequest.taskID + 1);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void FunctionalTask1(void *pvParameter)
{
    Request xRequest;
    while(1)
	{
        if(xQueuePeek(xQueue, &xRequest, pdMS_TO_TICKS(100)) == pdPASS) {
            if (xRequest.taskID == TASK1_ID) {
                xQueueReceive(xQueue, &xRequest, pdMS_TO_TICKS(100));
                // HANDLE
                printf("FunctionalTask 1: Handle request %s\n", xRequest.requestMsg);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void FunctionalTask2(void *pvParameter)
{
    Request xRequest;
    while(1)
	{
        if(xQueuePeek(xQueue, &xRequest, pdMS_TO_TICKS(100)) == pdPASS) {
            if (xRequest.taskID == TASK2_ID) {
                xQueueReceive(xQueue, &xRequest, pdMS_TO_TICKS(100));
                // HANDLE
                printf("FunctionalTask 2: Handle request %s\n", xRequest.requestMsg);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void FunctionalTask3(void *pvParameter)
{
    Request xRequest;
    while(1)
	{
        if(xQueuePeek(xQueue, &xRequest, pdMS_TO_TICKS(100)) == pdPASS) {
            if (xRequest.taskID == TASK3_ID) {
                xQueueReceive(xQueue, &xRequest, pdMS_TO_TICKS(100));
                // HANDLE
                printf("FunctionalTask 3: Handle request %s\n", xRequest.requestMsg);
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void app_main(void)
{
    xQueue = xQueueCreate(QUEUE_SIZE, sizeof(Request));

    xTaskCreate(ReceptionTask, "ReceptionTask", 2048, NULL, 1, NULL);

    xTaskCreate(FunctionalTask1, "FunctionalTask1", 2048, NULL, 1, NULL);
    xTaskCreate(FunctionalTask2, "FunctionalTask2", 2048, NULL, 1, NULL);
    xTaskCreate(FunctionalTask3, "FunctionalTask3", 2048, NULL, 1, NULL);
}
