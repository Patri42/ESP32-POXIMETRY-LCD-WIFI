#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "i2c-driver.h"
#include "max30102.h"
#include "max30102-data.h"

#include "connect_wifi.h"
#include "lcd-manager.h"
#include "thingspeak-manager.h"

    
QueueHandle_t sensorDataQueue = NULL;

void app_main(void)
{

    esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

    // Initialize I2C and MAX30102
    i2c_init();
    max30102_init();


    // Create the sensor data queue right after system initialization but before task creation.
    sensorDataQueue = xQueueCreate(10, sizeof(SensorData));
    ESP_LOGE("APP_MAIN", "Completed to create sensor data queue");
    if (sensorDataQueue == NULL) {
        // Handle the error. Maybe log an error message or halt the system.
        ESP_LOGE("APP_MAIN", "Failed to create sensor data queue");
        return;  // or handle error in another suitable way
    }

    // Always create the LCD task to display data
    xTaskCreate(lcd_task, "lcd_task", 4096, NULL, 4, NULL);

    // Create tasks
    xTaskCreate(max30102_task, "max30102_task", 4096, NULL, 6, NULL);

    // Initialize WiFi and connect
    connect_wifi();

    // Conditionally create the ThingSpeak task if WiFi is connected
    if (wifi_connect_status)
    {
        xTaskCreate(thingspeak_send_data, "thingspeak_send_data", 8192, NULL, 5, NULL);
    }
    
}