#ifndef THINGSPEAK_MANAGER_H
#define THINGSPEAK_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

extern QueueHandle_t sensorDataQueue;

//QueueHandle_t sensorDataQueue = NULL;

void thingspeak_send_data(void *pvParameters);

#endif