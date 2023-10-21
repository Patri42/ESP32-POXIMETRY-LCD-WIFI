#include "thingspeak-manager.h"
#include "esp_http_client.h"
#include "connect_wifi.h"
#include "max30102.h"
#include "max30102-data.h"

#include "freertos/FreeRTOS.h"
//#include "mock_freertos.h"
#include "freertos/queue.h"

static const char *TAG = "HTTP_CLIENT";
char api_key[] = "IWCH9QP5IUIQOI0Z";

void thingspeak_send_data(void *pvParameters)
{
    SensorData sensorData;

    while (1) // Ensuring repeated data sending
    {    
        if (xQueueReceive(sensorDataQueue, &sensorData, portMAX_DELAY) == pdTRUE) {   
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

            esp_http_client_config_t config = {
                .url = thingspeak_url,
                .method = HTTP_METHOD_GET
            };

            esp_http_client_handle_t client = esp_http_client_init(&config);
            esp_http_client_set_header(client, "Content-Type", "application/x-www-form-urlencoded");

            esp_err_t err = esp_http_client_perform(client);

            if (err == ESP_OK)
            {
                int status_code = esp_http_client_get_status_code(client);
                if (status_code == 200) // Note: ThingSpeak typically returns a 200 status on successful updates
                {
                    ESP_LOGI(TAG, "Message sent Successfully");
                }
                else
                {
                    ESP_LOGI(TAG, "Message sent Failed");
                }
            }
            else
            {
                ESP_LOGE(TAG, "HTTP client error: %s", esp_err_to_name(err));
            }
            esp_http_client_cleanup(client);

            vTaskDelay(16000 / portTICK_PERIOD_MS); // Delay 16 seconds as per ThingSpeak rate limits
        }
    }
}
