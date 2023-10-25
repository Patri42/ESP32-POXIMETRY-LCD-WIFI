#ifndef MAX30102_H
#define MAX30102_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

// Define the I2C address for MAX30102 sensor
#define I2C_ADDR_MAX30102 0x57

extern QueueHandle_t sensorDataQueue;

void max30102_init(void); 
void max30102_task(void *pvParameters) ; 


#endif // MAX30102_H