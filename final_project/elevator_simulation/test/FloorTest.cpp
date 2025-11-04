#include <gtest/gtest.h>
#include "Floor.h"

class FloorTest : public ::testing::Test {
protected:

    Floor floor{3};

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(FloorTest, GivenFloor_WhenPositive_ThenReturnPositiveInteger) {
    
    Floor positiveFloor{5};
    EXPECT_EQ(positiveFloor.getFloorNumber(), 5);
}

TEST_F(FloorTest, GivenFloor_WhenNegative_ThenReturnNegativeInteger) {

    Floor negativeFloor{-2};
    EXPECT_EQ(negativeFloor.getFloorNumber(), -2);
}

TEST_F(FloorTest, GivenFloor_WhenInZeroFloor_ThenReturnZero) {

    Floor zeroFloor{0};
    EXPECT_EQ(zeroFloor.getFloorNumber(), 0);
}

TEST_F(FloorTest, GivenFloor_WhenAddedGettingInAction_ThenActionsVectorContainsGettingInAction) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    std::vector<std::pair<int, Floor::PersonAction>>& actions = floor.getPersonActions();

    ASSERT_EQ(actions.size(), 1);
    EXPECT_EQ(actions[0].first, 1);
    EXPECT_EQ(actions[0].second, Floor::GETTING_IN);
}

TEST_F(FloorTest, GivenFloor_WhenAddedGettingOutAction_ThenActionsVectorContainsGettingOutAction) {
    floor.addPersonAction(2, Floor::GETTING_OUT);
    std::vector<std::pair<int, Floor::PersonAction>>& actions = floor.getPersonActions();

    ASSERT_EQ(actions.size(), 1);
    EXPECT_EQ(actions[0].first, 2);
    EXPECT_EQ(actions[0].second, Floor::GETTING_OUT);
}

TEST_F(FloorTest, GivenFloor_WhenAddedMultipleActions_ThenActionsVectorContainsMultipleActionsInOrder) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);
    floor.addPersonAction(3, Floor::GETTING_IN);

    std::vector<std::pair<int, Floor::PersonAction>>& actions = floor.getPersonActions();

    ASSERT_EQ(actions.size(), 3);
    EXPECT_EQ(actions[0].first, 1);
    EXPECT_EQ(actions[1].first, 2);
    EXPECT_EQ(actions[2].first, 3);
    EXPECT_EQ(actions[1].second, Floor::GETTING_OUT);
}

TEST_F(FloorTest, GivenFloor_WhenAddedAction_ThenActionsVectorSizeIncreases) {
    EXPECT_EQ(floor.getPersonActions().size(), 0);

    floor.addPersonAction(10, Floor::GETTING_IN);
    EXPECT_EQ(floor.getPersonActions().size(), 1);

    floor.addPersonAction(11, Floor::GETTING_OUT);
    EXPECT_EQ(floor.getPersonActions().size(), 2);
}

TEST_F(FloorTest, GivenFloor_WhenInstantiated_ThenActionVectorSizeIsZero) {
    std::vector<std::pair<int, Floor::PersonAction>>& actions = floor.getPersonActions();
    EXPECT_TRUE(actions.empty());
    EXPECT_EQ(actions.size(), 0);
}

TEST_F(FloorTest, GivenFloor_WhenGetPersonActionsCalled_ThenReturnReferenceToActionVector) {
    std::vector<std::pair<int, Floor::PersonAction>>& ref1 = floor.getPersonActions();
    ref1.push_back({303, Floor::GETTING_IN});

    std::vector<std::pair<int, Floor::PersonAction>>& ref2 = floor.getPersonActions();
    ASSERT_EQ(ref2.size(), 1);
    EXPECT_EQ(ref2[0].first, 303);
    EXPECT_EQ(ref2[0].second, Floor::GETTING_IN);
}

TEST_F(FloorTest, GivenFloor_WhenNoActionsExist_ThenIsFloorEmptyReturnsTrue) {
    EXPECT_TRUE(floor.isFloorEmpty());
}

TEST_F(FloorTest, GivenFloor_WhenActionsExist_ThenIsFloorEmptyReturnsFalse) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    EXPECT_FALSE(floor.isFloorEmpty());
}

TEST_F(FloorTest, GivenFloor_WhenAllActionsRemoved_ThenIsFloorEmptyReturnsTrue) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);

    std::vector<std::pair<int, Floor::PersonAction>>& actions = floor.getPersonActions();
    actions.clear();

    EXPECT_TRUE(floor.isFloorEmpty());
}

TEST_F(FloorTest, GivenFloor_WhenActionExists_ThenCheckAndRemoveActionReturnsTrue) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);
    floor.addPersonAction(3, Floor::GETTING_IN);
    bool result = floor.checkAndRemovePersonAction(2);

    EXPECT_TRUE(result);
    std::vector<std::pair<int, Floor::PersonAction>>& actions = floor.getPersonActions();
    EXPECT_EQ(actions.size(), 2);
    EXPECT_EQ(std::count_if(actions.begin(), actions.end(), [](std::pair<int, Floor::PersonAction>& p) { 
        return p.first == 2; }), 0);
}

TEST_F(FloorTest, GivenFloor_WhenMatchingActionDoesNotExist_ThenCheckAndRemoveActionReturnsFalse) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);
    floor.addPersonAction(3, Floor::GETTING_IN);

    bool result = floor.checkAndRemovePersonAction(99);

    EXPECT_FALSE(result);
    EXPECT_EQ(floor.getPersonActions().size(), 3); 
}

TEST_F(FloorTest, GivenFloorWithMultipleActions_WhenCheckAndRemoveActionCalled_ThenOnlyMatchingPersonIdActionsRemoved) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);
    floor.addPersonAction(3, Floor::GETTING_IN);
    
    bool result = floor.checkAndRemovePersonAction(1);

    EXPECT_TRUE(result);
    std::vector<std::pair<int, Floor::PersonAction>>& actions = floor.getPersonActions();

    EXPECT_EQ(actions.size(), 2);
    EXPECT_EQ(actions[0].first, 2);
    EXPECT_EQ(actions[1].first, 3);
}

TEST_F(FloorTest, GivenFloorWithoutActions_WhenGetPersonActionCountCalled_ThenReturnZero) {
    EXPECT_EQ(floor.getPersonActionCount(), 0);
}

TEST_F(FloorTest, GivenFloorWithAddedActions_WhenGetPersonActionCountCalled_ThenReturnCorrectCount) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);
    floor.addPersonAction(3, Floor::GETTING_IN);

    EXPECT_EQ(floor.getPersonActionCount(), 3);
}

TEST_F(FloorTest, GivenFloorWithRemovedActions_WhenGetPersonActionCountCalled_ThenReturnCorrectCount) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);
    floor.checkAndRemovePersonAction(1);

    EXPECT_EQ(floor.getPersonActionCount(), 1);
}

TEST_F(FloorTest, GivenFloorWithAllActionsRemoved_WhenGetPersonActionCountCalled_ThenReturnZero) {
    floor.addPersonAction(1, Floor::GETTING_IN);
    floor.addPersonAction(2, Floor::GETTING_OUT);

    auto& actions = floor.getPersonActions();
    actions.clear(); 
    EXPECT_EQ(floor.getPersonActionCount(), 0);
}
