#ifndef FLOOR_H
#define FLOOR_H

#include <map>
#include <vector>

class Floor {

public:
    enum PersonAction {
        GETTING_IN = 1,
        GETTING_OUT = 2,
    };

private:
    int floorNumber;
    std::vector<std::pair<int, PersonAction>> personActions;
public:
    Floor(int floorNumber);
    int getFloorNumber();
    std::vector<std::pair<int, PersonAction>>& getPersonActions();
    void addPersonAction(int personId, PersonAction action);
    bool isFloorEmpty();
    bool checkAndRemovePersonAction(int personId);
    int getPersonActionCount();
};

#endif