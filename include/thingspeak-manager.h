#ifndef THINGSPEAK_MANAGER_H
#define THINGSPEAK_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

//typedef void QueueHandle_t;

extern QueueHandle_t sensorDataQueue;

void thingspeak_send_data(void *pvParameters);

#endif