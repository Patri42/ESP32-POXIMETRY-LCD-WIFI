#include "mocks.h"

static BaseType_t mocked_xQueueReceive_return;
static SensorData *mocked_sensor_data;
static char *expected_http_url;
static bool correct_url_used = false;

void mock_xQueueReceive_returns(BaseType_t ret_val, SensorData *data) {
    mocked_xQueueReceive_return = ret_val;
    mocked_sensor_data = data;
}

BaseType_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait) {
    memcpy(pvBuffer, mocked_sensor_data, sizeof(SensorData));
    return mocked_xQueueReceive_return;
}

void mock_esp_http_client_config_matches(char *expected_url) {
    expected_http_url = expected_url;
}

esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config) {
    if (strcmp(config->url, expected_http_url) == 0) {
        correct_url_used = true;
    }
    return NULL;  // We're not creating a real client in the mock
}

bool was_correct_url_used() {
    return correct_url_used;
}