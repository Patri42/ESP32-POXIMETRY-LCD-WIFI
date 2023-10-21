// mock_freertos.h

#ifndef MOCK_FREERTOS_H
#define MOCK_FREERTOS_H

#define pdTRUE 1
#define portMAX_DELAY 0xFFFFFFFFU

typedef void* QueueHandle_t;
typedef unsigned long TickType_t;
typedef int BaseType_t;


BaseType_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait);


#endif // MOCK_FREERTOS_H
