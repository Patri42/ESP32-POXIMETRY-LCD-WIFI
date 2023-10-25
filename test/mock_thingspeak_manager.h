#ifndef MOCK_THINGSPEAK_MANAGER_H_
#define MOCK_THINGSPEAK_MANAGER_H_

#include "esp_http_client.h"  // Needed for esp_http_client_config_t and other http client types

typedef struct {
    float heartrate;
    float pctspo2;
} SensorData;

// Function prototype for the mock
void thingspeak_send_data(void *pvParameters);

#endif // MOCK_THINGSPEAK_MANAGER_H_