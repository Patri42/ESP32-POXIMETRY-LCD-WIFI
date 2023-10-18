#include "max30102.h"
#include "unity.h"
#include "esp_err.h"


static int i2c_write_call_count = 0;
static bool simulate_i2c_error = false;

esp_err_t i2c_write(uint8_t addr, uint8_t reg, uint8_t data) {
    i2c_write_call_count++;
    
    if (simulate_i2c_error) {
        return ESP_FAIL;
    }
    
    return ESP_OK;
}

void test_max30102_init_normal_operation(void) {
    // Reset
    i2c_write_call_count = 0;
    simulate_i2c_error = false;

    max30102_init();

    // Check if i2c_write was called the expected number of times
    TEST_ASSERT_EQUAL_INT(5, i2c_write_call_count);

}

void test_max30102_init_i2c_error(void) {
    // Reset
    i2c_write_call_count = 0;
    simulate_i2c_error = true;  // Simulate an error in i2c_write

    max30102_init();

    TEST_ASSERT_EQUAL_INT(1, i2c_write_call_count);
}