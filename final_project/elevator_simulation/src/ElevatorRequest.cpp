#include "ElevatorRequest.h"

ElevatorRequest::ElevatorRequest(Direction direction, int sourceFloor, int destinationFloor) : direction{direction}, sourceFloor{sourceFloor}, destinationFloor{destinationFloor} {

    personId = ++totalPersonCount;
}
