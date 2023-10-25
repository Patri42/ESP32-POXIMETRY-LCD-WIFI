#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

void lcd_task(void *pvParameters);

#endif