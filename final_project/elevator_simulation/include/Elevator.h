#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <atomic>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <map>
#include <list>
#include <set>
#include "ElevatorLogger.h"
#include "ElevatorRequest.h"
#include "Floor.h"

class Elevator {

public:
    enum ElevatorState {
        GOING_UP = 1,
        GOING_DOWN = 2,
        IDLE = 3,
        DEFAULT = 4,
    };

private:

    int elevatorId;
    int liftDelay;
    ElevatorLogger& logger;
    ElevatorState currentElevatorState;
    std::vector<Floor>::iterator currentFloorIterator;
    std::mutex loggerMutex;
    std::mutex elevatorMutex;
    std::condition_variable elevatorCV;
    std::vector<int> personsInsideElevator;
    std::vector<Floor> floors;
    std::set<int> upQueue;
    std::set<int, std::greater<int>> downQueue;
    std::atomic<bool> stopSignal;

public:

    Elevator(int elevatorId, ElevatorLogger& logger);  
    void runElevator();
    virtual ElevatorState getElevatorState();
    void performActionOnCurrentFloor();
    void openElevatorDoors();
    void closeElevatorDoors();
    template <typename SetType>
    void moveElevator(SetType& queue);
    virtual int getCurrentFloorNumber();
    virtual void addPersonActionToFloor(int floorNumber, int personId, Floor::PersonAction action);
    virtual void processElevatorRequest(const ElevatorRequest& request);
    virtual void changePersonDestinationFloor(int personId, int newDestinationFloor);
    virtual bool personExistsInsideElevator(int personId);
    void removePersonFromElevator(int personId);
    virtual int pendingRequests();
    virtual void stopElevator();
    virtual void waitForElevatorRequest();
    virtual void setCurrentElevatorState(ElevatorState elevatorState);
    virtual void addToUpQueue(int floorNumber);
    virtual void addToDownQueue(int floorNumber);
    virtual void removeFromUpQueue(int floorNumber);
    virtual void removeFromDownQueue(int floorNumber);
    virtual bool existsInUpQueue(int floorNumber);
    virtual bool existsInDownQueue(int floorNumber);
    virtual int getUpQueueSize();
    virtual int getDownQueueSize();
    virtual void moveElevatorUp();
    virtual void moveElevatorDown();
    Floor& getFloorByNumber(int floorNumber);
    std::vector<Floor>::iterator& getFloorIterator();
    std::condition_variable& getElevatorCV();
    std::vector<int>& getPersonArray();
    void handleGoingUp();
    void handleGoingDown();
    virtual ~Elevator();
    Elevator(const Elevator&) = delete;
    Elevator& operator=(const Elevator&) = delete;
};

#endif