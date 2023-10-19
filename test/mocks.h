#ifndef MOCKS_H_
#define MOCKS_H_

#include "freertos/queue.h"
#include "thingspeak-manager.h"
#include "max30102-data.h"
#include "esp_http_client.h"

// Mocks for xQueueReceive
void mock_xQueueReceive_returns(BaseType_t ret_val, SensorData *data);
BaseType_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait);

// Mocks for esp_http_client_config
void mock_esp_http_client_config_matches(char *expected_url);
esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config);
bool was_correct_url_used();

#endif