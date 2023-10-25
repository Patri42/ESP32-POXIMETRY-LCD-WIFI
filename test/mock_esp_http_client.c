#include "mock_esp_http_client.h"
#include "mock_thingspeak_manager.h"
#include "esp_log.h"

char last_url[256];
char* last_content_type = NULL;

char* g_mock_header_name = NULL;
char* g_mock_header_value = NULL;

static const char *TAG = "ThingSpeakMock";
static const char *api_key = "IWCH9QP5IUIQOI0Z";

// Mocking the HTTP client initialization. We simply return a dummy handle.
esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config) {
    static esp_http_client_handle_t dummy_handle = (esp_http_client_handle_t) 1234;
    return dummy_handle; 
}

// Mocking the HTTP header setter. Let's assume you want to check if the correct headers are set.
esp_err_t esp_http_client_set_header(esp_http_client_handle_t client, const char *key, const char *value) {
    // Check if the right headers are being set. This is just a basic example; adjust as needed.
    if (strcmp(key, "Content-Type") == 0 && strcmp(value, "application/x-www-form-urlencoded") == 0) {
        return ESP_OK; 
    }
    return ESP_FAIL;  // Indicate failure if the headers are not what you expect.
}

// Mocking the HTTP client perform. This function just returns success.
esp_err_t esp_http_client_perform(esp_http_client_handle_t client) {
    return ESP_OK; 
}

// Mocking the HTTP status code getter. This function returns a successful status.
int esp_http_client_get_status_code(esp_http_client_handle_t client) {
    return 200;
}

// Mocking the HTTP client cleanup.
esp_err_t esp_http_client_cleanup(esp_http_client_handle_t client) {
    return ESP_OK;
}

void mock_esp_http_client_set_header(esp_http_client_handle_t client, const char* header, const char* value)
{
    // Capture the arguments
    g_mock_header_name = strdup(header);
    g_mock_header_value = strdup(value);
}

void mock_thingspeak_send_data(void *pvParameters)
{
    SensorData sensorData;
    sensorData.heartrate = 75.0;  // Mock value
    sensorData.pctspo2 = 98.0;    // Mock value
    int send_count = 0;  // Initialize a counter to track the number of sends

    while (send_count < 10) // Limit the loop to 10 sends
    {    
        char thingspeak_url[200];
        snprintf(thingspeak_url,
                sizeof(thingspeak_url),
                "%s%s%s%f%s%f",
                "https://api.thingspeak.com/update?api_key=",
                api_key,
                "&field1=",
                sensorData.heartrate,
                "&field2=",
                sensorData.pctspo2);

        ESP_LOGI(TAG, "Mock client initialized with URL: %s", thingspeak_url);

        ESP_LOGI(TAG, "Mock header set: Content-Type = application/x-www-form-urlencoded");
        g_mock_header_name = strdup("Content-Type");
        g_mock_header_value = strdup("application/x-www-form-urlencoded");

        ESP_LOGI(TAG, "Mock HTTP request performed.");

        
        ESP_LOGI(TAG, "Message sent Successfully (Mocked)");

        vTaskDelay(1000 / portTICK_PERIOD_MS); 

        send_count++;  // Increment the send counter
    }
}
