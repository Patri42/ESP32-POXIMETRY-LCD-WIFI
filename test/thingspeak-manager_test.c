//#include "test_helpers.h"
#include "mock_thingspeak_manager.h"
#include "mock_esp_http_client.h"
#include "unity.h"


static int mock_http_status_code = 200;  // Default to success. Can be adjusted for different tests.

// Mock for sensorDataQueue 
QueueHandle_t sensorDataQueue = NULL;

// Setup and Teardown for each test
void setUp(void) {
    last_content_type = NULL;  // Reset the content-type. This is assumed to be defined in test_helpers.c
    mock_http_status_code = 200; // Resetting default value.
}

void tearDown(void) {
    // Any cleanup after test if needed
}

void test_successful_data_send(void) {
    mock_thingspeak_send_data(NULL);  // Call your function
    TEST_ASSERT_EQUAL_STRING("Content-Type", g_mock_header_name);
    TEST_ASSERT_EQUAL_STRING("application/x-www-form-urlencoded", g_mock_header_value);  // Checking that the header was set correctly

    // Free the memory allocated for the mock headers
    free(g_mock_header_name);
    free(g_mock_header_value);
    g_mock_header_name = NULL;
    g_mock_header_value = NULL;
}

int app_main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_successful_data_send);
    return UNITY_END();
}
