#include <gtest/gtest.h>
#include <future>
#include <chrono>
#include "TrafficSignal.h"

class TrafficSignalTest : public testing::Test {

protected:

    TrafficSignal trafficSignal;

};

TEST_F(TrafficSignalTest, GivenTrafficSignal_WhenConstructed_ThenTrafficLightIsRed) {

    EXPECT_FALSE(trafficSignal.isGreenLight());
}

TEST_F(TrafficSignalTest, GivenTrafficSignal_WhenCalledSetGreenLight_ThenTrafficLightIsGreen) {

    trafficSignal.setGreenLight();
    
    EXPECT_TRUE(trafficSignal.isGreenLight());
}

TEST_F(TrafficSignalTest, GivenTrafficSignal_WhenCalledSetRedLight_ThenTrafficLightIsRed) {

    TrafficSignal testTrafficSignal(TrafficSignal::GREEN);

    trafficSignal.setRedLight();
    EXPECT_FALSE(trafficSignal.isGreenLight());
}

TEST_F(TrafficSignalTest, GivenRedLight_WhenWaitForGreenLightCalled_ThenThreadIsBlocked) {

    ASSERT_FALSE(trafficSignal.isGreenLight());

    std::future testResult = std::async(std::launch::async, [&]() {
        trafficSignal.waitForGreenLight();
    });

    EXPECT_EQ(testResult.wait_for(std::chrono::seconds(1)), std::future_status::timeout);

    trafficSignal.setGreenLight();
}

TEST_F(TrafficSignalTest, GivenGreenLight_WhenWaitForGreenLightCalled_ThenThreadIsUnBlocked) {

    std::future testResult = std::async(std::launch::async, [&]() {
        trafficSignal.waitForGreenLight();
    });

    trafficSignal.setGreenLight();

    EXPECT_EQ(testResult.wait_for(std::chrono::seconds(1)), std::future_status::ready);
}


