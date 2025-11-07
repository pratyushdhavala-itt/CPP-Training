#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ElevatorController.h"
#include "MockElevator.h"
#include "MockElevatorController.h"
#include "MockElevatorLogger.h"
#include "ElevatorException.h"

class ElevatorControllerTest : public testing::Test {

protected:
    MockElevatorLogger logger;
    MockElevator mockElevatorOne{1, logger};
    MockElevator mockElevatorTwo{2, logger};
    std::vector<Elevator*> elevators;
    ElevatorController* controller;
    MockElevatorController* mockController;

public:

    void SetUp() override {
        elevators = {&mockElevatorOne, &mockElevatorTwo};
        controller = new ElevatorController(elevators);
        mockController = new MockElevatorController{elevators};
    }

    void TearDown() override {
        delete controller;
    }
};

TEST_F(ElevatorControllerTest, GivenElevatorIdle_WhenReceivedRequest_ThenCanBeAssigned) {
    ElevatorRequest req(ElevatorRequest::UP, 2, 6);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::IDLE));
    EXPECT_TRUE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}

TEST_F(ElevatorControllerTest, GivenElevatorDefault_WhenReceivedRequest_ThenCanBeAssigned) {
    ElevatorRequest req(ElevatorRequest::DOWN, 7, 2);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::DEFAULT));
    EXPECT_TRUE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingUp_WhenReceivedUpRequestAndCurrentFloorBelowThanSourceFloor_ThenCanBeAssigned) {
    ElevatorRequest req(ElevatorRequest::UP, 6, 8);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_UP));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(5));
    EXPECT_TRUE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingUp_WhenReceivedUpRequestAndCurrentFloorAboveThanSourceFloor_ThenNotAssigned) {
    ElevatorRequest req(ElevatorRequest::UP, 3, 8);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_UP));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(5));
    EXPECT_FALSE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingUp_WhenReceivedDownRequest_ThenNotAssigned) {
    ElevatorRequest req(ElevatorRequest::DOWN, 6, 2);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_UP));
    EXPECT_FALSE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingDown_WhenReceivedDownRequestAndCurrentFloorAboveThanSourceFloor_ThenCanBeAssigned) {
    ElevatorRequest req(ElevatorRequest::DOWN, 2, 0);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_DOWN));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(4));
    EXPECT_TRUE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingDown_WhenReceivedDownRequestAndCurrentFloorBelowThanSourceFloor_ThenNotAssigned) {
    ElevatorRequest req(ElevatorRequest::DOWN, 5, 1);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_DOWN));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(5));
    EXPECT_FALSE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingDown_WhenReceivedUpRequest_ThenNotAssigned) {
    ElevatorRequest req(ElevatorRequest::UP, 2, 6);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_DOWN));
    EXPECT_FALSE(controller->canAssignRequestToElevator(mockElevatorOne, req));
}


TEST_F(ElevatorControllerTest, GivenElevatorIdle_WhenRequestReceivedAtSameFloor_ThenScoreIsMinusOne) {
    ElevatorRequest req(ElevatorRequest::UP, 5, 8);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::IDLE));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(5));
    EXPECT_CALL(mockElevatorOne, pendingRequests()).WillOnce(::testing::Return(0));

    int score = controller->calculateScore(mockElevatorOne, req);
    EXPECT_EQ(score, -1); 
}

TEST_F(ElevatorControllerTest, GivenElevator_WhenReceivedRequest_ThenAddDistanceAndLoadToScore) {
    ElevatorRequest req(ElevatorRequest::DOWN, 2, 0);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::IDLE));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(7));
    EXPECT_CALL(mockElevatorOne, pendingRequests()).WillOnce(::testing::Return(2));

    int expected = std::abs(7 - 2) - 1 + 2; 
    int score = controller->calculateScore(mockElevatorOne, req);
    EXPECT_EQ(score, expected);
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingUp_WhenReceivedRequestInSameDirection_ThenScoreIsSubtractedByFour) {
    ElevatorRequest req(ElevatorRequest::UP, 3, 8);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_UP));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(1));
    EXPECT_CALL(mockElevatorOne, pendingRequests()).WillOnce(::testing::Return(0));

    int expected = std::abs(1 - 3) - 4;
    int score = controller->calculateScore(mockElevatorOne, req);
    EXPECT_EQ(score, expected);
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingUp_WhenReceivedRequestInOppositeDirection_ThenScoreIsAddedByThree) {
    ElevatorRequest req(ElevatorRequest::DOWN, 5, 1);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_UP));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(4));
    EXPECT_CALL(mockElevatorOne, pendingRequests()).WillOnce(::testing::Return(1));

    int expected = std::abs(4 - 5) + 3 + 1;
    int score = controller->calculateScore(mockElevatorOne, req);
    EXPECT_EQ(score, expected);
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingDown_WhenReceivedRequestInSameDirection_ThenScoreIsSubtractedByFour) {
    ElevatorRequest req(ElevatorRequest::DOWN, 7, 1);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_DOWN));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(9));
    EXPECT_CALL(mockElevatorOne, pendingRequests()).WillOnce(::testing::Return(0));

    int expected = std::abs(9 - 7) - 4;
    int score = controller->calculateScore(mockElevatorOne, req);
    EXPECT_EQ(score, expected);
}

TEST_F(ElevatorControllerTest, GivenElevatorGoingDown_WhenReceivedRequestInOppositeDirection_ThenScoreIsAddedByThree) {
    ElevatorRequest req(ElevatorRequest::UP, 1, 6);
    EXPECT_CALL(mockElevatorOne, getElevatorState()).WillOnce(::testing::Return(Elevator::GOING_DOWN));
    EXPECT_CALL(mockElevatorOne, getCurrentFloorNumber()).WillOnce(::testing::Return(3));
    EXPECT_CALL(mockElevatorOne, pendingRequests()).WillOnce(::testing::Return(2));

    int expected = std::abs(3 - 1) + 3 + 2;
    int score = controller->calculateScore(mockElevatorOne, req);
    EXPECT_EQ(score, expected);
}

TEST_F(ElevatorControllerTest, GivenController_WhenReceivedRequest_ThenRequestAssignedToAvailableElevatorOnly) {
    ElevatorRequest req(ElevatorRequest::UP, 2, 5);

    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorOne), ::testing::Ref(req))).WillOnce(::testing::Return(true));
    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorTwo), ::testing::Ref(req))).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mockController, calculateScore(::testing::Ref(mockElevatorOne), ::testing::Ref(req))).WillOnce(::testing::Return(10));
    EXPECT_CALL(mockElevatorOne, processElevatorRequest(::testing::_)).Times(1);
    EXPECT_CALL(mockElevatorTwo, processElevatorRequest(::testing::_)).Times(0);

    mockController->assignRequestToSuitableElevator(req);
}

TEST_F(ElevatorControllerTest, GivenController_WhenReceivedRequest_ThenAssignToElevatorWithLowestScore) {
    ElevatorRequest req(ElevatorRequest::DOWN, 8, 2);

    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorOne), ::testing::Ref(req))).WillOnce(::testing::Return(true));
    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorTwo), ::testing::Ref(req))).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockController, calculateScore(::testing::Ref(mockElevatorOne), ::testing::Ref(req))).WillOnce(::testing::Return(5));
    EXPECT_CALL(*mockController, calculateScore(::testing::Ref(mockElevatorTwo), ::testing::Ref(req))).WillOnce(::testing::Return(10));

    EXPECT_CALL(mockElevatorOne, processElevatorRequest(::testing::_)).Times(1);
    EXPECT_CALL(mockElevatorTwo, processElevatorRequest(::testing::_)).Times(0);

    mockController->assignRequestToSuitableElevator(req);
}

TEST_F(ElevatorControllerTest, GivenController_WhenReceivedRequestAndScoreEqual_ThenAssignToElevatorOne) {
    ElevatorRequest req(ElevatorRequest::UP, 3, 6);

    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorOne), ::testing::Ref(req))).WillOnce(::testing::Return(true));
    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorTwo), ::testing::Ref(req))).WillOnce(::testing::Return(true));

    EXPECT_CALL(*mockController, calculateScore(::testing::Ref(mockElevatorOne), ::testing::Ref(req))).WillOnce(::testing::Return(7));
    EXPECT_CALL(*mockController, calculateScore(::testing::Ref(mockElevatorTwo), ::testing::Ref(req))).WillOnce(::testing::Return(7));

    EXPECT_CALL(mockElevatorOne, processElevatorRequest(::testing::_)).Times(1);
    EXPECT_CALL(mockElevatorTwo, processElevatorRequest(::testing::_)).Times(0);

    mockController->assignRequestToSuitableElevator(req);
}

TEST_F(ElevatorControllerTest, GivenController_WhenReceivedRequestAndNoElevatorCanHandleIt_ThenDelayRequest) {
    ElevatorRequest req(ElevatorRequest::DOWN, 9, 1);

    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorOne), ::testing::Ref(req))).WillOnce(::testing::Return(false));
    EXPECT_CALL(*mockController, canAssignRequestToElevator(::testing::Ref(mockElevatorTwo), ::testing::Ref(req))).WillOnce(::testing::Return(false));

    EXPECT_CALL(*mockController, delayRequest(::testing::Ref(req))).Times(1);
    EXPECT_CALL(mockElevatorOne, processElevatorRequest(::testing::_)).Times(0);
    EXPECT_CALL(mockElevatorTwo, processElevatorRequest(::testing::_)).Times(0);

    mockController->assignRequestToSuitableElevator(req);
}

TEST_F(ElevatorControllerTest, GivenController_WhenReceivedAddedToQueue_ThenCorrectRequestReceived) {
    ElevatorRequest input(ElevatorRequest::UP, 1, 4);
    ElevatorRequest output(ElevatorRequest::UP, 0, 0);

    controller->addRequestToQueue(input);

    bool got = controller->waitAndGetElevatorRequest(output);

    EXPECT_TRUE(got);
    EXPECT_EQ(output.sourceFloor, input.sourceFloor);
    EXPECT_EQ(output.destinationFloor, input.destinationFloor);
}

TEST_F(ElevatorControllerTest, GivenController_WhenStopSignalIsTrue_ThenElevatorRequestReturnsFalse) {
    ElevatorRequest req(ElevatorRequest::UP, 0, 0);

    controller->stopElevatorController();

    bool got = controller->waitAndGetElevatorRequest(req);
    EXPECT_FALSE(got);
}

TEST_F(ElevatorControllerTest, GivenController_WhenMultipleRequestsAddedToQueue_ThenRequestsReceivedInFIFOOrder) {
    ElevatorRequest r1(ElevatorRequest::UP, 1, 5);
    ElevatorRequest r2(ElevatorRequest::DOWN, 7, 3);
    ElevatorRequest out(ElevatorRequest::UP, 0, 0);

    controller->addRequestToQueue(r1);
    controller->addRequestToQueue(r2);

    controller->waitAndGetElevatorRequest(out);
    EXPECT_EQ(out.sourceFloor, 1);

    controller->waitAndGetElevatorRequest(out);
    EXPECT_EQ(out.sourceFloor, 7);
}

TEST_F(ElevatorControllerTest, GivenController_WhenRequestReceived_ThenThreadIsUnblocked) {
    ElevatorRequest input(ElevatorRequest::DOWN, 8, 2);
    ElevatorRequest output(ElevatorRequest::UP, 0, 0);

    std::thread t([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        controller->addRequestToQueue(input);
    });

    auto start = std::chrono::steady_clock::now();
    bool got = controller->waitAndGetElevatorRequest(output);
    auto end = std::chrono::steady_clock::now();

    EXPECT_TRUE(got);
    EXPECT_GE(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(), 250);
    EXPECT_EQ(output.sourceFloor, 8);

    t.join();
}

TEST_F(ElevatorControllerTest, GivenController_WhenChangeDestinationCalledAndPersonExistsInElevatorOne_ThenForwardsRequestToElevatorContainingThePerson) {
    int personId = 5;
    int newFloor = 8;

    EXPECT_CALL(mockElevatorOne, personExistsInsideElevator(personId)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockElevatorTwo, personExistsInsideElevator(personId)).Times(0);
    EXPECT_CALL(mockElevatorOne, changePersonDestinationFloor(personId, newFloor)).Times(1);

    controller->changeDestinationFloor(personId, newFloor);
}

TEST_F(ElevatorControllerTest, GivenController_WhenChangeDestinationCalledAndPersonExistsInElevatorTwo_ThenForwardsRequestToElevatorContainingThePerson) {
    int personId = 3;
    int newFloor = 10;

    EXPECT_CALL(mockElevatorOne, personExistsInsideElevator(personId)).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockElevatorTwo, personExistsInsideElevator(personId)).WillOnce(::testing::Return(true));
    EXPECT_CALL(mockElevatorTwo, changePersonDestinationFloor(personId, newFloor)).Times(1);

    controller->changeDestinationFloor(personId, newFloor);
}

TEST_F(ElevatorControllerTest, GivenController_WhenChangeDestinationCalledAndPersonDoesNotExist_ThenThrowException) {
    int personId = 9;
    int newFloor = 5;

    EXPECT_CALL(mockElevatorOne, personExistsInsideElevator(personId)).WillOnce(::testing::Return(false));
    EXPECT_CALL(mockElevatorTwo, personExistsInsideElevator(personId)).WillOnce(::testing::Return(false));

    EXPECT_THROW(controller->changeDestinationFloor(personId, newFloor), ElevatorException);
}

TEST_F(ElevatorControllerTest, GivenController_WhenStopped_ThenAllElevatorsAlsoStopped) {
    EXPECT_CALL(mockElevatorOne, stopElevator()).Times(1);
    EXPECT_CALL(mockElevatorTwo, stopElevator()).Times(1);

    controller->stopElevatorController();
}

TEST_F(ElevatorControllerTest, GivenController_WhenStopSignalled_ThenThreadIsUnblocked) {
    ElevatorRequest out(ElevatorRequest::UP, 0, 0);
    bool result = false;

    std::thread waiter([&]() {
        result = controller->waitAndGetElevatorRequest(out);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_CALL(mockElevatorOne, stopElevator()).Times(1);
    EXPECT_CALL(mockElevatorTwo, stopElevator()).Times(1);
    controller->stopElevatorController();

    waiter.join();

    EXPECT_FALSE(result);  
}

TEST_F(ElevatorControllerTest, GivenController_WhenDelayRequestCalled_ThenRequestSentBackToQueue) {
    ElevatorRequest req(ElevatorRequest::UP, 3, 7);
    ElevatorRequest received(ElevatorRequest::DOWN, 0, 0);

    controller->delayRequest(req);
    bool got = controller->waitAndGetElevatorRequest(received);

    EXPECT_TRUE(got);
    EXPECT_EQ(received.sourceFloor, 3);
    EXPECT_EQ(received.destinationFloor, 7);
    EXPECT_EQ(received.direction, ElevatorRequest::UP);
}

TEST_F(ElevatorControllerTest, GivenController_WhenDelayRequestCalled_ThenThreadIsUnblocked) {
    ElevatorRequest req(ElevatorRequest::DOWN, 5, 2);
    ElevatorRequest received(ElevatorRequest::UP, 0, 0);
    bool got = false;

    std::thread waiter([&]() {
        got = controller->waitAndGetElevatorRequest(received);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200)); 

    controller->delayRequest(req); 

    waiter.join();

    EXPECT_TRUE(got);
    EXPECT_EQ(received.sourceFloor, 5);
    EXPECT_EQ(received.destinationFloor, 2);
}
