#include "gtest/gtest.h"
#include "../main/thingspeak-manager.h"

// Mocks
bool send_data_to_thingspeak(data) {
    return true;  // Mocked success
}

TEST(ThingSpeakManagerTest, CheckDataSend) {
    thingspeak_send_data();
    // Check conditions/assertions related to mocked send
}