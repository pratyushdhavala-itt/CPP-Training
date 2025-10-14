#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mutex>
#include <thread>
#include <chrono>
#include <future>
#include "TrafficSignal.h"
#include "Lane.h"
#include "Writer.h"

extern bool exitProgram;

class MockTrafficSignal : public TrafficSignal {

public:
    MOCK_METHOD(void, waitForGreenLight, (), (override));
    MOCK_METHOD(void, setGreenLight, (), (override));
    MOCK_METHOD(bool, isGreenLight, (), (override));
    MOCK_METHOD(void, setRedLight, (), (override));
};

class MockWriter : public IWriter {
public:
    MOCK_METHOD(void, Call, (const std::string& content, std::ios_base::openmode mode));
    void operator()(const std::string& content, std::ios_base::openmode mode) {
        Call(content, mode);
    }
};
class LaneTest : public ::testing::Test {
protected:
    MockTrafficSignal mockSignal;
    MockWriter mockWriter;
    std::mutex printMtx;
    Lane* lane;

    void SetUp() override {
        exitProgram = false;
        lane = new Lane(1, 3, &mockSignal, &printMtx);
    }

    void TearDown() override {
        exitProgram = true;
    }
};

TEST_F(LaneTest, GivenLane_WhenConstructed_ThenValuesAssignedCorrectly) {
    EXPECT_EQ(lane->getId(), 1);
    EXPECT_EQ(lane->getCarCount(), 3);
    EXPECT_EQ(lane->getCurrentCarCount(), 3);
    EXPECT_EQ(lane->getTrafficSignal(), &mockSignal);
}

TEST_F(LaneTest, GivenLane_WhenCarsAdded_ThenNumberOfCarsIncreases) {
    int totalCars = lane->getCarCount();
    int remainingCars = lane->getCurrentCarCount();

    lane->addCars(2);

    EXPECT_EQ(lane->getCarCount(), totalCars + 2);
    EXPECT_EQ(lane->getCurrentCarCount(), remainingCars + 2);
}

TEST_F(LaneTest, GivenGreenLight_WhenCrossTrafficSignalCalled_ThenAllCarsPass) {
    EXPECT_CALL(mockSignal, waitForGreenLight()).Times(1);
    EXPECT_CALL(mockSignal, isGreenLight()).WillRepeatedly(testing::Return(true));

    lane->canWrite = true;

    std::thread t([&]() {
        lane->crossTrafficSignal();
    });

    exitProgram = true;
    t.join();

    EXPECT_EQ(lane->getCurrentCarCount(), 0);
}

TEST_F(LaneTest, GivenRedLight_WhenCrossTrafficSignalCalled_ThenNoCarsPass) {
    EXPECT_CALL(mockSignal, waitForGreenLight()).Times(testing::AtLeast(1));
    EXPECT_CALL(mockSignal, isGreenLight())
        .WillRepeatedly(testing::Return(false));

    exitProgram = false;
    
    std::thread t([&]() {
        lane->crossTrafficSignal();
    });

    EXPECT_EQ(lane->getCurrentCarCount(), 3);

    exitProgram = true;
    t.join();
}


TEST_F(LaneTest, GivenZeroCarsRemaining_WhenCrossTrafficSignalCalled_ThenNothingHappens) {
    EXPECT_CALL(mockSignal, waitForGreenLight()).Times(testing::AtLeast(1));
    EXPECT_CALL(mockSignal, isGreenLight()).WillRepeatedly(testing::Return(true));

    lane->addCars(-lane->getCurrentCarCount());
    EXPECT_EQ(lane->getCurrentCarCount(), 0);

    lane->canWrite = true;
    exitProgram = false;

    std::thread t([&]() {
        lane->crossTrafficSignal();
    });

    exitProgram = true; 
    t.join();

    EXPECT_EQ(lane->getCurrentCarCount(), 0);
}
