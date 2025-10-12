#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include "TrafficSignal.h"
#include "Lane.h"

class MockTrafficSignal : public TrafficSignal {
public:
    MOCK_METHOD(void, waitForGreenLight, (), ());
    MOCK_METHOD(void, setGreenLight, (), ());
    MOCK_METHOD(void, setRedLight, (), ());
    MOCK_METHOD(bool, isGreenLight, (), ());
};

class LaneTest : public testing::Test {

protected:

    Lane* lane;
    MockTrafficSignal* mockTrafficSignal;
    std::mutex printMtx;

    void SetUp() override {

        int laneId = 1;
        int totalNumberOfCars = 5;
        mockTrafficSignal = new MockTrafficSignal;
        lane = new Lane(laneId, totalNumberOfCars, mockTrafficSignal, &printMtx);

        ON_CALL(*mockTrafficSignal, isGreenLight())
            .WillByDefault(testing::Return(false));
    }

    void TearDown() override {
        delete lane;
    }

};

TEST_F(LaneTest, GivenLane_WhenConstructed_ThenTrafficLightIsRed) {

    ASSERT_NE(lane->getTrafficSignal(), nullptr);
    EXPECT_FALSE(lane->getTrafficSignal()->isGreenLight());
}

TEST_F(LaneTest, GivenLane_WhenGetIdCalled_ThenCorrectIdRetrieved) {

    EXPECT_EQ(lane->getId(), 1);
}

TEST_F(LaneTest, GivenLane_WhenGetCarCountCalled_ThenCorrectCarCountRetrieved) {

    EXPECT_EQ(lane->getCarCount(), 5);
}

TEST_F(LaneTest, GivenLane_WhenConstructed_ThenCurrentCarCountEqualsTotalCarCount) {

    EXPECT_EQ(lane->getCarCount(), lane->getCurrentCarCount());
}

TEST_F(LaneTest, GivenLane_WhenCrossTrafficSignalCalled_ThenExpectTrafficSignalCalls) {

    EXPECT_CALL(*mockTrafficSignal, waitForGreenLight())
        .Times(1);

    EXPECT_CALL(*mockTrafficSignal, isGreenLight())
        .WillRepeatedly(testing::Return(true));

    lane->crossTrafficSignal();
}

TEST_F(LaneTest, GivenLane_WhenCarCountIsZero_ThenNoErrorOccured) {

    int laneId = 2;
    int totalNumberOfCars = 0;
    lane = new Lane(laneId, totalNumberOfCars, mockTrafficSignal, &printMtx);

    ON_CALL(*mockTrafficSignal, isGreenLight())
        .WillByDefault(testing::Return(true));

    std::thread laneThread(&Lane::crossTrafficSignal, lane);
    laneThread.join();

    ASSERT_EQ(lane->getCarCount(), 0);
    EXPECT_EQ(lane->getCurrentCarCount(), 0);
}

TEST_F(LaneTest, GivenLane_WhenRedLight_ThenNoCarCrosses) {

    std::future testResult = std::async(std::launch::async, [&]() {
        lane->crossTrafficSignal();
    });

    EXPECT_EQ(lane->getCurrentCarCount(), lane->getCarCount());

    EXPECT_CALL(*mockTrafficSignal, isGreenLight())
        .WillRepeatedly(testing::Return(true));
}


TEST_F(LaneTest, GivenLane_WhenGreenLight_ThenSomeCarsCrossSignal) {

    std::thread laneThread(&Lane::crossTrafficSignal, lane);
    EXPECT_CALL(*mockTrafficSignal, isGreenLight())
        .WillRepeatedly(testing::Return(true));

    std::this_thread::sleep_for(std::chrono::seconds(2));
    laneThread.join();

    EXPECT_LT(lane->getCurrentCarCount(), lane->getCarCount());
}

