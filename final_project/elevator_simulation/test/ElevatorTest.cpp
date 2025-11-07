#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include "Elevator.h"
#include "MockElevatorLogger.h"

class MockElevator : public Elevator {
public:
    MockElevator(int id, ElevatorLogger& logger) : Elevator(id, logger) {}

    MOCK_METHOD(void, moveElevatorUp, (), (override));
    MOCK_METHOD(void, moveElevatorDown, (), (override));
    MOCK_METHOD(void, waitForElevatorRequest, (), (override));

    MockElevator(const MockElevator&) = delete;
    MockElevator& operator=(const MockElevator&) = delete;

};

class ElevatorTest : public testing::Test {

protected:
    MockElevatorLogger mockLogger;
    Elevator elevator{1, mockLogger};

public:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(ElevatorTest, GivenElevator_WhenReceivedUpRequest_ThenAddFloorToUpQueueAndChangeStateToGoingUp) {
    ElevatorRequest req(ElevatorRequest::UP, 2, 7);

    elevator.processElevatorRequest(req);

    EXPECT_TRUE(elevator.existsInUpQueue(2));
    EXPECT_TRUE(elevator.existsInUpQueue(7));
    EXPECT_EQ(elevator.getElevatorState(), Elevator::GOING_UP);
    EXPECT_EQ(elevator.getUpQueueSize(), 2);
}

TEST_F(ElevatorTest, GivenElevator_WhenReceivedDownRequest_ThenAddFloorToDownQueueAndChangeStateToGoingDown) {
    ElevatorRequest req(ElevatorRequest::DOWN, 8, 3);

    elevator.processElevatorRequest(req);

    EXPECT_TRUE(elevator.existsInDownQueue(8));
    EXPECT_TRUE(elevator.existsInDownQueue(3));
    EXPECT_EQ(elevator.getElevatorState(), Elevator::GOING_DOWN);
    EXPECT_EQ(elevator.getDownQueueSize(), 2);
}

TEST_F(ElevatorTest, GivenElevator_WhenInDefaultStateAndReceivedRequest_ThenRemoveGroundFloorFromDownQueue) {
    elevator.setCurrentElevatorState(Elevator::DEFAULT);
    elevator.addToDownQueue(0);

    ElevatorRequest req(ElevatorRequest::UP, 4, 6);
    elevator.processElevatorRequest(req);

    EXPECT_FALSE(elevator.existsInDownQueue(0));
    EXPECT_TRUE(elevator.existsInUpQueue(4));
    EXPECT_TRUE(elevator.existsInUpQueue(6));
    EXPECT_EQ(elevator.getElevatorState(), Elevator::GOING_UP);
}

TEST_F(ElevatorTest, GivenElevator_WhenGoingUpAndReceivedUpRequest_ThenDoesNotChangeState) {
    elevator.setCurrentElevatorState(Elevator::GOING_UP);

    ElevatorRequest req(ElevatorRequest::UP, 3, 5);
    elevator.processElevatorRequest(req);

    EXPECT_EQ(elevator.getElevatorState(), Elevator::GOING_UP);
    EXPECT_TRUE(elevator.existsInUpQueue(3));
    EXPECT_TRUE(elevator.existsInUpQueue(5));
}

TEST_F(ElevatorTest, GivenElevator_WhenGoingDownAndReceivedDownRequest_ThenDoesNotChangeState) {
    elevator.setCurrentElevatorState(Elevator::GOING_DOWN);

    ElevatorRequest req(ElevatorRequest::DOWN, 9, 2);
    elevator.processElevatorRequest(req);

    EXPECT_EQ(elevator.getElevatorState(), Elevator::GOING_DOWN);
    EXPECT_TRUE(elevator.existsInDownQueue(9));
    EXPECT_TRUE(elevator.existsInDownQueue(2));
}

TEST_F(ElevatorTest, GivenElevator_WhenReceivedRequest_ThenCorrectPersonActionsAddedToCorrectFloors) {
    ElevatorRequest req(ElevatorRequest::UP, 2, 7);

    elevator.processElevatorRequest(req);

    Floor& sourceFloor = elevator.getFloorByNumber(2);
    Floor& destFloor   = elevator.getFloorByNumber(7);

    std::vector<std::pair<int, Floor::PersonAction>>& sourceActions = sourceFloor.getPersonActions();
    std::vector<std::pair<int, Floor::PersonAction>>& destActions = destFloor.getPersonActions();

    bool foundGettingIn = false;
    for (std::pair<int, Floor::PersonAction>& action : sourceActions) {
        if (action.first == req.personId && action.second == Floor::GETTING_IN) {
            foundGettingIn = true;
            break;
        }
    }

    bool foundGettingOut = false;
    for (std::pair<int, Floor::PersonAction>& action : destActions) {
        if (action.first == req.personId && action.second == Floor::GETTING_OUT) {
            foundGettingOut = true;
            break;
        }
    }

    EXPECT_TRUE(foundGettingIn);
    EXPECT_TRUE(foundGettingOut);
}


TEST_F(ElevatorTest, GivenElevator_WhenReceivedRequest_ThenThreadUnblocksImmediately) {
    elevator.addToUpQueue(3);

    auto start = std::chrono::steady_clock::now();
    elevator.waitForElevatorRequest();
    auto end = std::chrono::steady_clock::now();

    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    EXPECT_LT(durationMs, 200);
    EXPECT_EQ(elevator.getElevatorState(), Elevator::IDLE);
}

TEST_F(ElevatorTest, GivenElevator_WhenWaitingForRequestAtGroundFloor_ThenWaitFor10SecondsAndNoChangeInState) {
    auto start = std::chrono::steady_clock::now();
    elevator.waitForElevatorRequest();
    auto end = std::chrono::steady_clock::now();

    auto durationSec = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    EXPECT_GE(durationSec, 9);
    EXPECT_EQ(elevator.getElevatorState(), Elevator::IDLE);
    EXPECT_FALSE(elevator.existsInDownQueue(0));
}

TEST_F(ElevatorTest, GivenElevator_WhenWaitingForRequestAtNonGroundFloor_ThenChangeToDefaultStateAndGoToGroundFloorAfterTimeout) {

    std::vector<Floor>::iterator& it = elevator.getFloorIterator();
    it++;
    EXPECT_EQ(elevator.pendingRequests(), 0);

    elevator.waitForElevatorRequest();

    EXPECT_TRUE(elevator.existsInDownQueue(0));
    EXPECT_EQ(elevator.getElevatorState(), Elevator::DEFAULT);
}

TEST_F(ElevatorTest, GivenElevator_WhenWaitingForElevatorRequest_ThenStopWaitingWhenStopElevatorSignalled) {
    std::thread stopper([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        elevator.stopElevator();
    });

    auto start = std::chrono::steady_clock::now();
    elevator.waitForElevatorRequest();
    auto end = std::chrono::steady_clock::now();

    stopper.join();

    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(durationMs, 1000);
}

TEST_F(ElevatorTest, GivenElevator_WhenStopElevatorCalled_ThenThreadStopsWaitingAndExitsBeforeTimeout) {
    elevator.stopElevator();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));

    auto start = std::chrono::steady_clock::now();
    elevator.waitForElevatorRequest();
    auto end = std::chrono::steady_clock::now();

    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_LT(durationMs, 500);
}

TEST_F(ElevatorTest, GivenElevator_WhenStopElevatorCalled_ThenItNotifiesThreadWaiting) {
    bool awakened = false;

    std::thread waiter([&]() {
        std::mutex testMutex;
        std::unique_lock<std::mutex> lock(testMutex);
        awakened = elevator.getElevatorCV().wait_for(lock, std::chrono::milliseconds(500), [&]() { return true; });
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    elevator.stopElevator();
    waiter.join();

    EXPECT_TRUE(awakened);
}

TEST_F(ElevatorTest, GivenElevator_WhenInstantiated_ThenItIsIdle) {
    EXPECT_EQ(elevator.getElevatorState(), Elevator::IDLE);
}

TEST_F(ElevatorTest, GivenElevator_WhenSetStateToGoingUp_ThenGetterReturnsCorrectState) {
    elevator.setCurrentElevatorState(Elevator::GOING_UP);
    EXPECT_EQ(elevator.getElevatorState(), Elevator::GOING_UP);
}

TEST_F(ElevatorTest, GivenElevator_WhenSetStateToGoingDown_ThenGetterReturnsCorrectState) {
    elevator.setCurrentElevatorState(Elevator::GOING_DOWN);
    EXPECT_EQ(elevator.getElevatorState(), Elevator::GOING_DOWN);
}

TEST_F(ElevatorTest, GivenElevator_WhenSetStateToDefault_ThenGetterReturnsCorrectState) {
    elevator.setCurrentElevatorState(Elevator::DEFAULT);
    EXPECT_EQ(elevator.getElevatorState(), Elevator::DEFAULT);
}

TEST_F(ElevatorTest, GivenElevator_WhenAddedFloorToUpQueue_ThenItExistsInUpQueueAndUpQueueSizeIncreases) {
    elevator.addToUpQueue(3);

    EXPECT_TRUE(elevator.existsInUpQueue(3));
    EXPECT_EQ(elevator.getUpQueueSize(), 1);
}

TEST_F(ElevatorTest, GivenElevator_WhenAddedMultipleFloorsToUpQueue_ThenItExistsInUpQueueAndUpQueueSizeIncreasesNotIncludingDuplicates) {
    elevator.addToUpQueue(2);
    elevator.addToUpQueue(5);
    elevator.addToUpQueue(2);

    EXPECT_TRUE(elevator.existsInUpQueue(2));
    EXPECT_TRUE(elevator.existsInUpQueue(5));
    EXPECT_EQ(elevator.getUpQueueSize(), 2);
}

TEST_F(ElevatorTest, GivenElevator_WhenRemovedFloorFromUpQueue_ThenItDoesNotExistInUpQueueAndUpQueueSizeDecreases) {
    elevator.addToUpQueue(4);
    elevator.removeFromUpQueue(4);

    EXPECT_FALSE(elevator.existsInUpQueue(4));
    EXPECT_EQ(elevator.getUpQueueSize(), 0);
}

TEST_F(ElevatorTest, GivenElevator_WhenRemovedNonExistentFloorFromUpQueue_ThenNothingHappens) {
    elevator.addToUpQueue(6);
    elevator.removeFromUpQueue(9);

    EXPECT_TRUE(elevator.existsInUpQueue(6));
    EXPECT_EQ(elevator.getUpQueueSize(), 1);
}

TEST_F(ElevatorTest, GivenElevatorWithNoRequests_WhenPendingRequestCalled_ThenReturnsZero) {
    EXPECT_EQ(elevator.pendingRequests(), 0);
}

TEST_F(ElevatorTest, GivenElevator_WhenPendingRequestsCalled_ThenAddsFloorsFromBothQueues) {
    elevator.addToUpQueue(3);
    elevator.addToDownQueue(6);
    elevator.addToDownQueue(8);

    EXPECT_EQ(elevator.pendingRequests(), 3);
}

TEST_F(ElevatorTest, GivenElevator_WhenPendingRequestCalled_ThenReturnsCountAfterRemovals) {
    elevator.addToUpQueue(2);
    elevator.addToUpQueue(3);
    elevator.addToDownQueue(6);

    EXPECT_EQ(elevator.pendingRequests(), 3);

    elevator.removeFromUpQueue(3);
    elevator.removeFromDownQueue(6);

    EXPECT_EQ(elevator.pendingRequests(), 1);
}

TEST_F(ElevatorTest, GivenElevator_WhenInstantiated_ThenCurrentFloorIsGroundFloor) {
    EXPECT_EQ(elevator.getCurrentFloorNumber(), 0);
}

TEST_F(ElevatorTest, GivenElevator_WhenFloorIteratorIsIncremented_ThenCurrentFloorNumberIsUpdated) {
    for (int i = 0; i < 3; ++i) {
        ++elevator.getFloorIterator();
    }

    EXPECT_EQ(elevator.getCurrentFloorNumber(), 3);
}

TEST_F(ElevatorTest, GivenElevator_WhenMoveElevatorCalledAndQueuesAreEmpty_ThenNothingHappens) {
    EXPECT_CALL(mockLogger, call(testing::_, testing::_, testing::_)).Times(0);

    std::set<int> emptyQueue;
    elevator.moveElevator(emptyQueue);

    EXPECT_EQ(elevator.getCurrentFloorNumber(), 0);
}

TEST_F(ElevatorTest, GivenElevator_WhenMoveElevatorCalledAndUpQueueNotEmpty_ThenItMovesUpAndLogsCorrectly) {
    std::set<int> upQueue = {2};

    EXPECT_CALL(mockLogger, call(1, testing::_, ::testing::HasSubstr("MOVING UP"))).Times(::testing::AtLeast(1));

    elevator.moveElevator(upQueue);

    EXPECT_EQ(elevator.getCurrentFloorNumber(), 2);
    EXPECT_TRUE(upQueue.empty());
}

TEST_F(ElevatorTest, GivenElevator_WhenMoveElevatorCalledAndDownQueueNotEmpty_ThenItMovesDownAndLogsCorrectly) {

    std::advance(elevator.getFloorIterator(), 5);
    std::set<int> downQueue = {2};

    EXPECT_CALL(mockLogger, call(1, testing::_, ::testing::HasSubstr("MOVING DOWN"))).Times(::testing::AtLeast(1));

    elevator.moveElevator(downQueue);

    EXPECT_EQ(elevator.getCurrentFloorNumber(), 2);
    EXPECT_TRUE(downQueue.empty());
}

TEST_F(ElevatorTest, GivenElevator_WhenMoveElevatorCalled_ThenItMovesSequentiallyToTargetFloors) {
    std::set<int> queue = {2, 4, 6};

    EXPECT_CALL(mockLogger, call(1, testing::_, ::testing::HasSubstr("MOVING UP")))
        .Times(::testing::AtLeast(3));

    elevator.moveElevator(queue);

    EXPECT_EQ(elevator.getCurrentFloorNumber(), 6);
    EXPECT_TRUE(queue.empty());
}

TEST_F(ElevatorTest, GivenElevator_WhenUpAndDownQueueNotEmpty_ThenItSatisfiesBothRequestsOneAfterAnother) {
    std::set<int> upQueue = {3};
    std::set<int> downQueue = {1};

    EXPECT_CALL(mockLogger, call(1, testing::_, ::testing::HasSubstr("MOVING UP"))).Times(::testing::AtLeast(1));
    elevator.moveElevator(upQueue);
    EXPECT_EQ(elevator.getCurrentFloorNumber(), 3);

    EXPECT_CALL(mockLogger, call(1, testing::_, ::testing::HasSubstr("MOVING DOWN"))).Times(::testing::AtLeast(1));
    elevator.moveElevator(downQueue);
    EXPECT_EQ(elevator.getCurrentFloorNumber(), 1);
}

TEST_F(ElevatorTest, GivenElevator_WhenPersonExistsAndPerformActionCalled_ThenActionLogsPrinted) {
    int floorNum = 0;
    int personId = 101;

    Floor& floor = elevator.getFloorByNumber(floorNum);
    floor.addPersonAction(personId, Floor::GETTING_IN);

    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("STEPPING IN"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("OPENING DOORS"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("CLOSING DOORS"))).Times(1);

    elevator.performActionOnCurrentFloor();

    EXPECT_TRUE(elevator.personExistsInsideElevator(personId));
}

TEST_F(ElevatorTest, GivenElevator_WhenPersonRemovedAndPerformActionCalled_ThenActionLogsPrinted) {
    int floorNum = 0;
    int personId = 202;

    elevator.getPersonArray().push_back(personId);

    Floor& floor = elevator.getFloorByNumber(floorNum);
    floor.addPersonAction(personId, Floor::GETTING_OUT);

    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("STEPPING OUT"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("OPENING DOORS"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("CLOSING DOORS"))).Times(1);

    elevator.performActionOnCurrentFloor();

    EXPECT_FALSE(elevator.personExistsInsideElevator(personId));
}

TEST_F(ElevatorTest, GivenElevator_WhenNoActionsExistAndPerformActionCalled_ThenNothingIsLogged) {
    EXPECT_CALL(mockLogger, call(testing::_, testing::_, testing::_)).Times(0);

    elevator.performActionOnCurrentFloor();

    EXPECT_EQ(elevator.getPersonArray().size(), 0);
}

TEST_F(ElevatorTest, GivenElevator_WhenMultipleActionsExistAndPerformActionCalled_ThenOpenAndCloseDoorOnceOnly) {
    int floorNum = 0;
    int p1 = 10, p2 = 11;

    Floor& floor = elevator.getFloorByNumber(floorNum);
    floor.addPersonAction(p1, Floor::GETTING_IN);
    floor.addPersonAction(p2, Floor::GETTING_IN);

    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("OPENING DOORS"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("CLOSING DOORS"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("STEPPING IN"))).Times(2);

    elevator.performActionOnCurrentFloor();

    EXPECT_TRUE(elevator.personExistsInsideElevator(p1));
    EXPECT_TRUE(elevator.personExistsInsideElevator(p2));
}

TEST_F(ElevatorTest, GivenElevator_WhenPerformActionCalled_ThenActionsAreRemoved) {
    int floorNum = 0;
    int p1 = 111, p2 = 112;

    Floor& floor = elevator.getFloorByNumber(floorNum);
    floor.addPersonAction(p1, Floor::GETTING_IN);
    floor.addPersonAction(p2, Floor::GETTING_IN);

    elevator.performActionOnCurrentFloor();

    EXPECT_TRUE(floor.getPersonActions().empty());
}

TEST_F(ElevatorTest, GivenElevator_WhenMixedActionsExistAndPerformActionCalled_ThenMultipleActionsLogged) {
    int floorNum = 0;
    int pIn = 200, pOut = 201;

    elevator.getPersonArray().push_back(pOut);

    Floor& floor = elevator.getFloorByNumber(floorNum);
    floor.addPersonAction(pIn, Floor::GETTING_IN);
    floor.addPersonAction(pOut, Floor::GETTING_OUT);

    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("STEPPING IN"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("STEPPING OUT"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("OPENING DOORS"))).Times(1);
    EXPECT_CALL(mockLogger, call(1, floorNum, ::testing::HasSubstr("CLOSING DOORS"))).Times(1);

    elevator.performActionOnCurrentFloor();

    EXPECT_TRUE(elevator.personExistsInsideElevator(pIn));
    EXPECT_FALSE(elevator.personExistsInsideElevator(pOut));
}

TEST_F(ElevatorTest, GivenElevator_WhenOpenDoorsCalled_ThenCorrectMessageLogged) {
    int currentFloor = elevator.getCurrentFloorNumber();

    EXPECT_CALL(mockLogger, call(1, currentFloor, ::testing::HasSubstr("OPENING DOORS"))).Times(1);

    elevator.openElevatorDoors();
}

TEST_F(ElevatorTest, GivenElevator_WhenCloseDoorsCalled_ThenCorrectMessageLogged) {
    int currentFloor = elevator.getCurrentFloorNumber();

    EXPECT_CALL(mockLogger, call(1, currentFloor, ::testing::HasSubstr("CLOSING DOORS"))).Times(1);

    elevator.closeElevatorDoors();
}

TEST_F(ElevatorTest, GivenElevator_WhenOpenOrCloseDoorsCalled_ThenCurrentFloorLogged) {

    std::advance(elevator.getFloorIterator(), 3);

    int newFloor = elevator.getCurrentFloorNumber();

    EXPECT_CALL(mockLogger, call(1, newFloor, ::testing::HasSubstr("OPENING DOORS"))).Times(1);
    elevator.openElevatorDoors();

    EXPECT_CALL(mockLogger, call(1, newFloor, ::testing::HasSubstr("CLOSING DOORS"))).Times(1);
    elevator.closeElevatorDoors();
}

TEST_F(ElevatorTest, GivenElevator_WhenAddPersonActionCalled_ThenCorrectPersonActionAdded) {
    int floorNum = 2;
    int personId = 10;

    elevator.addPersonActionToFloor(floorNum, personId, Floor::GETTING_IN);

    Floor& floor = elevator.getFloorByNumber(floorNum);
    const auto& actions = floor.getPersonActions();

    ASSERT_FALSE(actions.empty());
    EXPECT_EQ(actions[0].first, personId);
    EXPECT_EQ(actions[0].second, Floor::GETTING_IN);
}

TEST_F(ElevatorTest, GivenElevator_WhenPersonExists_ThenCheckAndReturnTrue) {
    elevator.getPersonArray().push_back(5);
    EXPECT_TRUE(elevator.personExistsInsideElevator(5));
}

TEST_F(ElevatorTest, GivenElevator_WhenPersonDoesNotExist_ThenCheckAndReturnFalse) {
    elevator.getPersonArray() = {1, 2, 3};
    EXPECT_FALSE(elevator.personExistsInsideElevator(10));
}

TEST_F(ElevatorTest, GivenElevator_WhenPersonRemoved_ThenCorrectPersonRemoved) {
    elevator.getPersonArray() = {1, 2, 3, 4};

    elevator.removePersonFromElevator(3);

    EXPECT_FALSE(elevator.personExistsInsideElevator(3));
    EXPECT_EQ(elevator.getPersonArray().size(), 3);
}

TEST_F(ElevatorTest, GivenElevator_WhenNonExistentPersonRemoved_ThenNothingHappens) {
    elevator.getPersonArray() = {7, 8, 9};

    elevator.removePersonFromElevator(10);

    EXPECT_EQ(elevator.getPersonArray().size(), 3);
    EXPECT_TRUE(elevator.personExistsInsideElevator(7));
}

TEST_F(ElevatorTest, GivenElevator_WhenChangeDestinationCalled_ThenAddActionToNewFloor) {
    int oldFloor = 2, newFloor = 5, personId = 22;

    Floor& oldFloorObj = elevator.getFloorByNumber(oldFloor);
    oldFloorObj.addPersonAction(personId, Floor::GETTING_OUT);

    elevator.setCurrentElevatorState(Elevator::GOING_UP);
    elevator.addToUpQueue(oldFloor);

    elevator.changePersonDestinationFloor(personId, newFloor);

    Floor& newFloorObj = elevator.getFloorByNumber(newFloor);
    const auto& newActions = newFloorObj.getPersonActions();

    EXPECT_TRUE(newActions.size() == 1);
    EXPECT_EQ(newActions[0].first, personId);
    EXPECT_EQ(newActions[0].second, Floor::GETTING_OUT);
}

TEST_F(ElevatorTest, GivenPerson_WhenChangeDirectionCalled_ThenAddNewFloorToCorrectQueue) {
    int floor = 3, personId = 11;

    elevator.removeFromUpQueue(floor);
    elevator.removeFromDownQueue(floor);

    elevator.changePersonDestinationFloor(personId, 6);
    EXPECT_TRUE(elevator.existsInUpQueue(6));
    std::advance(elevator.getFloorIterator(), 6);

    elevator.changePersonDestinationFloor(personId, 1);
    EXPECT_TRUE(elevator.existsInDownQueue(1));
}

TEST_F(ElevatorTest, GivenElevator_WhenChangeDestinationCalled_ThenRemoveOldFloorIfNoPersonActionsExist) {
    int oldFloor = 2, newFloor = 8, personId = 33;

    Floor& floor = elevator.getFloorByNumber(oldFloor);
    floor.addPersonAction(personId, Floor::GETTING_OUT);
    elevator.addToUpQueue(oldFloor);

    elevator.setCurrentElevatorState(Elevator::GOING_UP);
    elevator.changePersonDestinationFloor(personId, newFloor);

    EXPECT_FALSE(elevator.existsInUpQueue(oldFloor));
}
