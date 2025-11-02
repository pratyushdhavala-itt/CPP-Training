#ifndef ELEVATOR_REQUEST
#define ELEVATOR_REQUEST

struct ElevatorRequest {

    enum Direction {
        UP = 1,
        DOWN = 2,
    };

    static inline int totalPersonCount = -1;
    Direction direction;
    int personId;
    int sourceFloor;
    int destinationFloor;

    ElevatorRequest(Direction direction, int sourceFloor, int destinationFloor);
};

#endif
