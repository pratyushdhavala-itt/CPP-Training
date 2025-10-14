#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utility_functions.h"
#include "constants.h"

class MockLane : public Lane {
public:
    MockLane(int id) : Lane(id, 0, nullptr, nullptr) {}
    MOCK_METHOD(void, addCars, (int), (override));
};

class InputChoiceTestFixture : public ::testing::Test {
protected:
    std::streambuf* cinBackup;
    std::streambuf* coutBackup;
    std::ostringstream testOutput;
    std::mutex mtx;

    void SetUp() override {
        cinBackup = std::cin.rdbuf();
        coutBackup = std::cout.rdbuf(testOutput.rdbuf());
    }

    void TearDown() override {
        std::cin.rdbuf(cinBackup);
        std::cout.rdbuf(coutBackup);
    }
};

TEST_F(InputChoiceTestFixture, GivenValidInputWithinRange_WhenCalled_ThenReturnsValue) {
    std::istringstream testInput("3\n");
    std::cin.rdbuf(testInput.rdbuf());   
    int result = inputChoice(1, 5, false);
    EXPECT_EQ(result, 3);
}

TEST_F(InputChoiceTestFixture, GivenNegativeOne_WhenCalled_ThenReturnsMinusOne) {
    std::istringstream testInput("-1\n");
    std::cin.rdbuf(testInput.rdbuf());
    int result = inputChoice(1, 5, true);
    EXPECT_EQ(result, -1);
}

TEST_F(InputChoiceTestFixture, GivenNegativeOtherThanOne_WhenCalled_ThenReturnInvalidInput) {
    std::istringstream testInput("-1\n2\n");
    std::cin.rdbuf(testInput.rdbuf());
    int result = inputChoice(1, 5, false);
    EXPECT_THAT(testOutput.str(), testing::HasSubstr(PRINT_INVALID_INPUT_TWO));
}

TEST_F(InputChoiceTestFixture, GivenOutOfRangeInput_WhenCalled_ThenRetriesUntilValid) {
    std::istringstream testInput("9\n2\n");
    std::cin.rdbuf(testInput.rdbuf());
    int result = inputChoice(1, 5, false);
    EXPECT_EQ(result, 2);
    EXPECT_THAT(testOutput.str(), testing::HasSubstr(PRINT_INVALID_INPUT_TWO));
}

TEST_F(InputChoiceTestFixture, GivenNonNumericInput_WhenCalled_ThenRetriesUntilValid) {
    std::istringstream testInput("abc\n3\n");
    std::cin.rdbuf(testInput.rdbuf());
    int result = inputChoice(1, 5, false);
    EXPECT_EQ(result, 3);
    EXPECT_THAT(testOutput.str(), testing::HasSubstr(PRINT_INVALID_INPUT_ONE));
}

TEST_F(InputChoiceTestFixture, GivenDecimalInput_WhenCalled_ThenRejectsUntilInteger) {
    std::istringstream testInput("2.5\n4\n");
    std::cin.rdbuf(testInput.rdbuf());
    int result = inputChoice(1, 5, false);
    EXPECT_THAT(testOutput.str(), testing::HasSubstr(PRINT_INVALID_INPUT_ONE));
    EXPECT_EQ(result, 4);
}

TEST_F(InputChoiceTestFixture, GivenLaneCapacity_WhenCalled_ThenCreatesCorrectNumberOfLanes) {
    std::vector<Lane*> lanes;
    lanes.reserve(3);  

    std::istringstream testInput("2\n4\n6\n");
    std::cin.rdbuf(testInput.rdbuf());

    inputNumberOfCarsPerLane(lanes, &mtx);

    ASSERT_EQ(lanes.size(), 3);
    EXPECT_EQ(lanes[0]->getId(), 1);
    EXPECT_EQ(lanes[1]->getId(), 2);
    EXPECT_EQ(lanes[2]->getId(), 3);
}

TEST_F(InputChoiceTestFixture, GivenLaneCapacity_WhenCalled_ThenPrintsPromptsForEachLane) {
    std::vector<Lane*> lanes;
    lanes.reserve(2);

    std::istringstream testInput("3\n5\n");
    std::cin.rdbuf(testInput.rdbuf());

    inputNumberOfCarsPerLane(lanes, &mtx);

    std::string output = testOutput.str();
    EXPECT_NE(output.find("Enter number of cars"), std::string::npos);
}

TEST_F(InputChoiceTestFixture, GivenInputs_WhenCalled_ThenStoresCorrectCarCounts) {
    std::vector<Lane*> lanes;
    lanes.reserve(2);

    std::istringstream testInput("5\n7\n");
    std::cin.rdbuf(testInput.rdbuf());

    inputNumberOfCarsPerLane(lanes, &mtx);

    EXPECT_EQ(lanes[0]->getCarCount(), 5);
    EXPECT_EQ(lanes[1]->getCarCount(), 7);
}

TEST_F(InputChoiceTestFixture, GivenValidLaneAndCars_WhenCalled_ThenAddCarsInvokedCorrectly) {
    MockLane lane1(1), lane2(2);
    std::vector<Lane*> lanes = { &lane1, &lane2 };

    std::istringstream testInput("2\n5\n-1\n");
    std::cin.rdbuf(testInput.rdbuf());

    EXPECT_CALL(lane2, addCars(5)).Times(1);
    EXPECT_CALL(lane1, addCars).Times(0);

    addMoreCars(lanes);
    EXPECT_TRUE(exitProgram);
}

TEST_F(InputChoiceTestFixture, GivenMinusOneLaneNumber_WhenCalled_ThenExitsAndSetsAllCarsPassed) {
    MockLane lane(1);
    std::vector<Lane*> lanes = { &lane };

    std::istringstream testInput("-1\n");
    std::cin.rdbuf(testInput.rdbuf());

    EXPECT_CALL(lane, addCars).Times(0);

    exitProgram = false;
    addMoreCars(lanes);
    EXPECT_THAT(testOutput.str(), testing::HasSubstr(PRINT_END_PROGRAM_AFTER_CROSSING));
    EXPECT_TRUE(exitProgram);
}

TEST_F(InputChoiceTestFixture, GivenMinusOneCarsInput_WhenCalled_ThenRetriesAndAddsCarsAfterValidInput) {
    MockLane lane(1);
    std::vector<Lane*> lanes = { &lane };
    std::istringstream testInput("1\n-1\n2\n-1\n");
    std::cin.rdbuf(testInput.rdbuf());

    EXPECT_CALL(lane, addCars(2)).Times(1);

    exitProgram = false;
    addMoreCars(lanes);

    EXPECT_THAT(testOutput.str(), testing::HasSubstr(PRINT_INVALID_INPUT_TWO));
}

TEST_F(InputChoiceTestFixture, GivenMultipleInputs_WhenCalled_ThenUpdatesMultipleLanes) {
    MockLane lane1(1), lane2(2);
    std::vector<Lane*> lanes = { &lane1, &lane2 };

    std::istringstream testInput("1\n3\n2\n5\n-1\n");
    std::cin.rdbuf(testInput.rdbuf());

    EXPECT_CALL(lane1, addCars(3)).Times(1);
    EXPECT_CALL(lane2, addCars(5)).Times(1);

    exitProgram = false;
    addMoreCars(lanes);

    EXPECT_TRUE(exitProgram);
}

TEST_F(InputChoiceTestFixture, GivenInputs_WhenCalled_ThenPrintsPrompts) {
    MockLane lane(1);
    std::vector<Lane*> lanes = { &lane };

    std::istringstream testInput("-1\n");
    std::cin.rdbuf(testInput.rdbuf());

    addMoreCars(lanes);

    std::string output = testOutput.str();
    EXPECT_THAT(testOutput.str(), testing::HasSubstr(PRINT_END_PROGRAM_AFTER_CROSSING));
}
