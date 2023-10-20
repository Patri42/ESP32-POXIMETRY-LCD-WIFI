#include "gtest/gtest.h"
#include "../main/max30102.h"  // path might vary based on your project structure

// Mocks
int read_sensor_value() {
    return 12345;  // Mocked value
}

TEST(Max30102Test, CheckSensorReading) {
    // Assuming max30102_task uses read_sensor_value internally
    max30102_task();
    // Now, check conditions/assertions related to the mock value 12345
}