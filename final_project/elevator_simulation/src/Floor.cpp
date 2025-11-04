#include <map>
#include <vector>
#include <algorithm>
#include "Floor.h"

Floor::Floor(int floorNumber) : floorNumber{floorNumber} {}

int Floor::getFloorNumber() {
    return floorNumber;
}
std::vector<std::pair<int, Floor::PersonAction>>& Floor::getPersonActions() {
    return personActions;
}
    
bool Floor::isFloorEmpty() {
    return personActions.empty();
}

bool Floor::checkAndRemovePersonAction(int personId) {
    std::vector<std::pair<int, Floor::PersonAction>>::iterator it = std::find_if(personActions.begin(), personActions.end(), [&](const std::pair<int, PersonAction>& p) {
        return personId == p.first;
    });
    if (it != personActions.end()) {
        personActions.erase(it);
        return true;
    }
    return false;
}

void Floor::addPersonAction(int personId, PersonAction action) {
    personActions.push_back({personId, action});
}

int Floor::getPersonActionCount() {
    return personActions.size();
}