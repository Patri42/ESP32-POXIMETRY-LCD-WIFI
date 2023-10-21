#include "gtest/gtest.h"
#include "thingspeak-manager.h"
#include "max30102-data.h"
#include "esp_http_client.h"
#include "mock_freertos.h"

static esp_http_client_handle_t mock_http_client_handle = (esp_http_client_handle_t) 1;  // Some dummy value.
static int mock_http_status_code = 200;  // Default to success. Can be adjusted for different tests.
static const char* mock_last_set_header_value;

// Mocks

// Mock FreeRTOS Queue
BaseType_t xQueueReceive(QueueHandle_t xQueue, void *pvBuffer, TickType_t xTicksToWait) {

    ((SensorData*)pvBuffer)->heartrate = 70.5;
    ((SensorData*)pvBuffer)->pctspo2 = 99.0;
    return pdTRUE;
}

// Mock for the infinite loop in thingspeak_send_data
int iteration_count = 0;
bool mock_should_continue() {
    iteration_count++;
    return iteration_count <= 2;  // Only run twice for testing
}

esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config) {
    return mock_http_client_handle;  // Always return a mock handle.
}

esp_err_t esp_http_client_set_header(esp_http_client_handle_t client, const char *key, const char *value) {
    if (strcmp(key, "Content-Type") == 0) {
        mock_last_set_header_value = value;  // Record for later verification.
    }
    return ESP_OK;  // Simulate success.
}

esp_err_t esp_http_client_perform(esp_http_client_handle_t client) {
    return ESP_OK;  // Simulate success.
}

int esp_http_client_get_status_code(esp_http_client_handle_t client) {
    return mock_http_status_code;
}

esp_err_t esp_http_client_cleanup(esp_http_client_handle_t client) {
    mock_http_client_handle = NULL;  // Reset.
    return ESP_OK;
}

// Test

TEST(ThingSpeakSendData, SuccessfulDataSend) {
    // Setup: Mock any necessary functions. Set conditions for success.

    // Execute the function:
    thingspeak_send_data(NULL);

    // Assertions: 
    EXPECT_EQ(mock_last_set_header_value, "application/x-www-form-urlencoded");
    // ... Additional assertions based on behavior ...

    // Reset mock behavior/state for the next test.
    mock_last_set_header_value = NULL;
    mock_http_status_code = 200;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}