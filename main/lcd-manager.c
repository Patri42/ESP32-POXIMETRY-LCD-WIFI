#include "lcd.h"
#include "lcd-manager.h"
#include "max30102.h"
#include "max30102-data.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

extern QueueHandle_t sensorDataQueue;

void lcd_task(void *pvParameters)
{
    printf ("LCD task started");
    /* Create LCD object */
    lcd_t lcd;

    /* Set default pinout */
    lcdDefault(&lcd);

    /* Initialize LCD object */
    lcdInit(&lcd);

    /* Clear previous data on LCD */
    lcdClear(&lcd);

    //SensorData_t receivedData;
    SensorData receivedData;
    while (1)
    {
        if (xQueueReceive(sensorDataQueue, &receivedData, portMAX_DELAY) == pdTRUE){
            char buffer[16];
            
            sprintf(buffer, "Pulse: %.1f", receivedData.heartrate);
            //printf("Displaying: %s\n", buffer);
            lcd_err_t ret = lcdSetText(&lcd, buffer, 0, 0);
            assert_lcd(ret);

            sprintf(buffer, "Oximetry: %.1f", receivedData.pctspo2);
            //printf("Displaying: %s\n", buffer);
            ret = lcdSetText(&lcd, buffer, 0, 1);
            assert_lcd(ret);

        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    // Free LCD if and when task is being deleted
    lcdFree(&lcd);
}