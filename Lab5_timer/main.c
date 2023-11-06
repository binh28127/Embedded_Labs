#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#define TIMER1_PERIOD_MS 2000
#define TIMER1_STOP_AFTER 10

#define TIMER2_PERIOD_MS 3000
#define TIMER2_STOP_AFTER 5

// Timer IDs
#define TIMER1_ID 1
#define TIMER2_ID 2

static int timer1Count = 0;
static int timer2Count = 0;

void TimerCallback(TimerHandle_t xTimer)
{
	int timerID = (int)pvTimerGetTimerID(xTimer);

    if (timerID == TIMER1_ID) {
        printf("ahihi -- Count[1]: %d -- TimeStamp[1]: %lu\n", ++timer1Count, xTaskGetTickCount()/100);

        if (timer1Count >= TIMER1_STOP_AFTER) {
            xTimerStop(xTimer, 0);
            printf("Timer 1 stopped\n");
        }
    } else if (timerID == TIMER2_ID) {
        printf("ihaha -- Count[2]: %d -- TimeStamp[2]: %lu\n", ++timer2Count, xTaskGetTickCount()/100);

        if (timer2Count >= TIMER2_STOP_AFTER) {
            xTimerStop(xTimer, 0);
            printf("Timer 2 stopped\n");
        }
    }
}

void app_main(void)
{
    // Create timer 1
    TimerHandle_t timer1Handle = xTimerCreate("Timer1", pdMS_TO_TICKS(TIMER1_PERIOD_MS), pdTRUE, (void *)TIMER1_ID, TimerCallback);
    if (timer1Handle == NULL) {
        printf("Failed to create Timer 1\n");
        return;
    }

    // Start timer 1
    if (xTimerStart(timer1Handle, 0) != pdPASS) {
        printf("Failed to start Timer 1\n");
    }

    // Create timer 2
    TimerHandle_t timer2Handle = xTimerCreate("Timer2", pdMS_TO_TICKS(TIMER2_PERIOD_MS), pdTRUE, (void *)TIMER2_ID, TimerCallback);
    if (timer2Handle == NULL) {
        printf("Failed to create Timer 2\n");
        return;
    }

    // Start timer 2
    if (xTimerStart(timer2Handle, 0) != pdPASS) {
        printf("Failed to start Timer 2\n");
    }
}
