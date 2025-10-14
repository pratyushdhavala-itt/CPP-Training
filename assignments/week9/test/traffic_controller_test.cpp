#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <mutex>
#include <vector>
#include <thread>
#include "Writer.h"
#include "TrafficController.h"
#include "Lane.h"

class MockTrafficSignal : public TrafficSignal {
public:
    MOCK_METHOD(void, waitForGreenLight, (), (override));
    MOCK_METHOD(void, setGreenLight, (), (override));
    MOCK_METHOD(void, setRedLight, (), (override));
    MOCK_METHOD(bool, isGreenLight, (), (override));
};

class MockWriter : public IWriter {
public:
    MOCK_METHOD(void, Call, (const std::string& content, std::ios_base::openmode mode));
    void operator()(const std::string& content, std::ios_base::openmode mode) {
        Call(content, mode);
    }
};

class TrafficControllerTest : public testing::Test {

protected:
    std::mutex printMtx;
    std::vector<Lane*> lanes;
    TrafficController* controller;
    
public:

    void SetUp() override {

    }

    void TearDown() override {

        delete controller;
    }

};

TEST_F(TrafficControllerTest, GivenLanes_WhenSorted_ThenLanesOrderedByDescendingCarCount) {
    MockTrafficSignal* signal1 = new MockTrafficSignal();
    MockTrafficSignal* signal2 = new MockTrafficSignal();

    Lane* lane1 = new Lane(1, 5, signal1, &printMtx);
    Lane* lane2 = new Lane(2, 10, signal2, &printMtx);

    lanes.assign({lane1, lane2});
    controller = new TrafficController(lanes, &printMtx);

    controller->sortLanes();

    EXPECT_EQ(lanes[0]->getId(), 2);
    EXPECT_EQ(lanes[1]->getId(), 1);
}

TEST_F(TrafficControllerTest, GivenLanesAlreadySorted_WhenSorted_ThenOrderRemainsSame) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();
    MockTrafficSignal* s3 = new MockTrafficSignal();

    Lane* l1 = new Lane(1, 20, s1, &printMtx);
    Lane* l2 = new Lane(2, 10, s2, &printMtx);
    Lane* l3 = new Lane(3, 5, s3, &printMtx);

    lanes = {l1, l2, l3};
    controller = new TrafficController(lanes, &printMtx);

    controller->sortLanes();

    EXPECT_EQ(lanes[0]->getId(), 1);
    EXPECT_EQ(lanes[1]->getId(), 2);
    EXPECT_EQ(lanes[2]->getId(), 3);
}


TEST_F(TrafficControllerTest, GivenLaneWithZeroCars_WhenSorted_ThenItIsLast) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();
    Lane* l1 = new Lane(1, 0, s1, &printMtx);
    Lane* l2 = new Lane(2, 5, s2, &printMtx);

    lanes = {l1, l2};
    controller = new TrafficController(lanes, &printMtx);

    controller->sortLanes();

    EXPECT_EQ(lanes[0]->getId(), 2);
    EXPECT_EQ(lanes[1]->getId(), 1);
}

TEST_F(TrafficControllerTest, GivenNoLanes_WhenSorted_ThenDoesNotCrash) {
    controller = new TrafficController(lanes, &printMtx);

    EXPECT_NO_THROW(controller->sortLanes());
    EXPECT_TRUE(lanes.empty());
}

TEST_F(TrafficControllerTest, GivenThreeLanes_WhenSecondLaneIsGreen_ThenItIsPrintedCorrectly) {
    
    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();
    MockTrafficSignal* s3 = new MockTrafficSignal();

    Lane* l1 = new Lane(1, 3, s1, &printMtx);
    Lane* l2 = new Lane(2, 4, s2, &printMtx);
    Lane* l3 = new Lane(3, 5, s3, &printMtx);

    lanes = {l1, l2, l3};
    controller = new TrafficController(lanes, &printMtx);

    std::string result = controller->allLanesStatusToString(2);

    std::string expected =
        "\nTraffic Lights of all the Lanes:-\n"
        "LANE: 1 -> RED\n"
        "LANE: 2 -> GREEN\n"
        "LANE: 3 -> RED\n";

    EXPECT_EQ(result, expected);
}

TEST_F(TrafficControllerTest, GivenOneLane_WhenGreen_ThenItIsPrintedCorrectly) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    Lane* l1 = new Lane(1, 2, s1, &printMtx);
    lanes = {l1};
    controller = new TrafficController(lanes, &printMtx);

    std::string result = controller->allLanesStatusToString(1);

    std::string expected =
        "\nTraffic Lights of all the Lanes:-\n"
        "LANE: 1 -> GREEN\n";

    EXPECT_EQ(result, expected);
}

TEST_F(TrafficControllerTest, GivenThreeLanes_WhenInvalidLaneIdIsGreen_ThenAllLanesAreRed) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();
    MockTrafficSignal* s3 = new MockTrafficSignal();

    Lane* l1 = new Lane(1, 2, s1, &printMtx);
    Lane* l2 = new Lane(2, 2, s2, &printMtx);
    Lane* l3 = new Lane(3, 2, s3, &printMtx);

    lanes = {l1, l2, l3};
    controller = new TrafficController(lanes, &printMtx);

    std::string result = controller->allLanesStatusToString(5);

    std::string expected =
        "\nTraffic Lights of all the Lanes:-\n"
        "LANE: 1 -> RED\n"
        "LANE: 2 -> RED\n"
        "LANE: 3 -> RED\n";

    EXPECT_EQ(result, expected);
}

TEST_F(TrafficControllerTest, GivenThreeLanes_WhenRemainingCarsStatusCalled_ThenCorrectStringReturned) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();
    MockTrafficSignal* s3 = new MockTrafficSignal();

    Lane* l1 = new Lane(1, 5, s1, &printMtx);
    Lane* l2 = new Lane(2, 10, s2, &printMtx);
    Lane* l3 = new Lane(3, 15, s3, &printMtx);

    lanes = {l1, l2, l3};
    controller = new TrafficController(lanes, &printMtx);

    std::string result = controller->remainingCarsStatusToString();

    std::string expected =
        "\nRemaining cars in each lane:-\n"
        "Lane 1: 5 cars\n"
        "Lane 2: 10 cars\n"
        "Lane 3: 15 cars\n";

    EXPECT_EQ(result, expected);
}

TEST_F(TrafficControllerTest, GivenOneLane_WhenRemainingCarsStatusCalled_ThenPrintsThatLaneOnly) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    Lane* l1 = new Lane(1, 8, s1, &printMtx);
    lanes = {l1};
    controller = new TrafficController(lanes, &printMtx);

    std::string result = controller->remainingCarsStatusToString();

    std::string expected =
        "\nRemaining cars in each lane:-\n"
        "Lane 1: 8 cars\n";

    EXPECT_EQ(result, expected);
}

TEST_F(TrafficControllerTest, GivenZeroCarLanes_WhenRemainingCarsStatusCalled_ThenShowsZeroCars) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();

    Lane* l1 = new Lane(1, 0, s1, &printMtx);
    Lane* l2 = new Lane(2, 0, s2, &printMtx);

    lanes = {l1, l2};
    controller = new TrafficController(lanes, &printMtx);

    std::string result = controller->remainingCarsStatusToString();

    std::string expected =
        "\nRemaining cars in each lane:-\n"
        "Lane 1: 0 cars\n"
        "Lane 2: 0 cars\n";

    EXPECT_EQ(result, expected);
}

TEST_F(TrafficControllerTest, GivenNoLanes_WhenGettingRemainingCarsStatus_ThenShowsHeaderOnly) {
    controller = new TrafficController(lanes, &printMtx); 

    std::string result = controller->remainingCarsStatusToString();

    EXPECT_EQ(result, "\nRemaining cars in each lane:-\n");
}

TEST_F(TrafficControllerTest, GivenLane_WhenWriteSignalStatusToFileCalled_ThenCorrectDataPassedToWriter) {

    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();
    Lane* l1 = new Lane(1, 3, s1, &printMtx);
    Lane* l2 = new Lane(2, 5, s2, &printMtx);
    lanes = {l1, l2};

    controller = new TrafficController(lanes, &printMtx);

    MockWriter mockWriter;

    std::string expected =
        "\nTraffic Lights of all the Lanes:-\n"
        "LANE: 1 -> RED\n"
        "LANE: 2 -> GREEN\n";

    EXPECT_CALL(mockWriter, Call(expected, std::ios::app)).Times(1);

    controller->writeSignalStatusToFile(mockWriter, l2);

    EXPECT_TRUE(l2->canWrite);
}

TEST_F(TrafficControllerTest, GivenLanes_WhenWriteRemainingCarStatusToFileCalled_ThenCorrectDataPassedToWriter) {
    MockTrafficSignal* s1 = new MockTrafficSignal();
    MockTrafficSignal* s2 = new MockTrafficSignal();
    Lane* l1 = new Lane(1, 5, s1, &printMtx);
    Lane* l2 = new Lane(2, 10, s2, &printMtx);
    lanes = {l1, l2};

    controller = new TrafficController(lanes, &printMtx);
    MockWriter mockWriter;

    std::string expected =
        "\nRemaining cars in each lane:-\n"
        "Lane 1: 5 cars\n"
        "Lane 2: 10 cars\n";

    EXPECT_CALL(mockWriter, Call(expected, std::ios::out)).Times(1);

    controller->writeRemainingCarStatusToFile(mockWriter, l1);

    EXPECT_TRUE(l1->canWrite);
}

TEST_F(TrafficControllerTest, GivenOneLane_WhenControlTrafficRuns_ThenGreenAndRedCalledOnce) {
    MockTrafficSignal* signal = new MockTrafficSignal();
    Lane* lane = new Lane(1, 3, signal, &printMtx);
    lanes = { lane };
    controller = new TrafficController(lanes, &printMtx);

    MockWriter mockWriter;

    EXPECT_CALL(*signal, setGreenLight()).Times(1);
    EXPECT_CALL(*signal, setRedLight()).Times(1);

    extern bool exitProgram;
    exitProgram = false;
    std::thread stopper([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        exitProgram = true;
    });

    controller->controlTraffic();

    stopper.join();
}

TEST_F(TrafficControllerTest, GivenLaneWithZeroCars_WhenControlTrafficRuns_ThenNoSignalCalls) {

    MockTrafficSignal* signal = new MockTrafficSignal();
    Lane* lane = new Lane(1, 0, signal, &printMtx);
    lanes = { lane };
    controller = new TrafficController(lanes, &printMtx);

    MockWriter mockWriter; 

    EXPECT_CALL(*signal, setGreenLight()).Times(0);
    EXPECT_CALL(*signal, setRedLight()).Times(0);


    extern bool exitProgram;
    exitProgram = false;

    std::thread stopper([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        exitProgram = true;
    });

    controller->controlTraffic();

    stopper.join();
}

TEST_F(TrafficControllerTest, GivenMultipleLanes_WhenControlTrafficRuns_ThenEachLaneGetsGreenAndRedOnce) {
    
    MockTrafficSignal* signal1 = new MockTrafficSignal();
    MockTrafficSignal* signal2 = new MockTrafficSignal();
    Lane* lane1 = new Lane(1, 3, signal1, &printMtx);
    Lane* lane2 = new Lane(2, 5, signal2, &printMtx);
    lanes = { lane1, lane2 };
    controller = new TrafficController(lanes, &printMtx);

    MockWriter mockWriter;

    EXPECT_CALL(*signal1, setGreenLight()).Times(1);
    EXPECT_CALL(*signal1, setRedLight()).Times(1);
    EXPECT_CALL(*signal2, setGreenLight()).Times(1);
    EXPECT_CALL(*signal2, setRedLight()).Times(1);

    extern bool exitProgram;
    exitProgram = false;
    std::thread stopper([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        exitProgram = true;
    });

    controller->controlTraffic();

    stopper.join();
}

TEST_F(TrafficControllerTest, GivenNoLanes_WhenControlTrafficRuns_ThenDoesNotCrash) {
    controller = new TrafficController(lanes, &printMtx); 
    MockWriter mockWriter; 

    extern bool exitProgram;
    exitProgram = false;
    std::thread stopper([] {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        exitProgram = true;
    });

    EXPECT_NO_THROW(controller->controlTraffic());

    stopper.join();
}
