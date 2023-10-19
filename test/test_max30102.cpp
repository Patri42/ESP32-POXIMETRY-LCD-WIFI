#include "unity.h"
#include "max30102.h" // Make sure your main code is modularized for testing
#include "thingspeak-manager.h"
#include "mocks.h" // A file to include the mocks you'll use

extern char api_key[]; 



void test_max30102_init(void)
{
    max30102_init(); // This should have some return value or set a global state for testing
    // Here we assume there's a function is_max30102_initialized() which tells us if initialization was successful
    TEST_ASSERT_TRUE_MESSAGE(is_max30102_initialized(), "Failed to initialize MAX30102");
}

void test_thingspeak_send_data_successful(void)
{
    SensorData expected_data = { .heartrate = 75.0, .pctspo2 = 98.0 };
    mock_xQueueReceive_returns(pdTRUE, &expected_data); // mock_xQueueReceive_returns is a mock function
    
    char expected_url[200];
    snprintf(expected_url, sizeof(expected_url), "https://api.thingspeak.com/update?api_key=%s&field1=%f&field2=%f", api_key, expected_data.heartrate, expected_data.pctspo2);
    mock_esp_http_client_config_matches(expected_url); // mock_esp_http_client_config_matches is a mock function

    thingspeak_send_data(NULL);
    TEST_ASSERT_MESSAGE(was_correct_url_used(), "Incorrect URL used"); // was_correct_url_used is a mock utility
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_max30102_init);
    RUN_TEST(test_thingspeak_send_data_successful);

    return UNITY_END();
}