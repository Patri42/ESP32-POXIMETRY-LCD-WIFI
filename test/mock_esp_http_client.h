#ifndef MOCK_ESP_HTTP_CLIENT_H
#define MOCK_ESP_HTTP_CLIENT_H

#include "esp_http_client.h"

extern char last_url[256];
extern char* last_content_type;
extern char* g_mock_header_name;
extern char* g_mock_header_value;

// Mock function declarations
esp_http_client_handle_t esp_http_client_init(const esp_http_client_config_t *config);
esp_err_t esp_http_client_set_header(esp_http_client_handle_t client, const char *key, const char *value);
esp_err_t esp_http_client_perform(esp_http_client_handle_t client);
int esp_http_client_get_status_code(esp_http_client_handle_t client);
esp_err_t esp_http_client_cleanup(esp_http_client_handle_t client);
void mock_esp_http_client_set_header(esp_http_client_handle_t client, const char* header, const char* value);
void mock_thingspeak_send_data(void *pvParameters);

#endif // MOCK_ESP_HTTP_CLIENT_H



