#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <iostream>
#include "ElevatorController.h"
#include "MockElevatorController.h"
#include "MockElevator.h"
#include "Elevator.h"
#include "constants.h"
#include "utility_functions.h"

class UtilityFunctionsTest : public ::testing::Test {
protected:
    std::streambuf* cinBackup;
    std::streambuf* coutBackup;
    std::istringstream inputBuffer;
    std::ostringstream outputBuffer;

    void SetUp() override {
        cinBackup = std::cin.rdbuf();
        coutBackup = std::cout.rdbuf();
    }

    void TearDown() override {
        std::cin.rdbuf(cinBackup);
        std::cout.rdbuf(coutBackup);
    }
};

TEST_F(UtilityFunctionsTest, GivenInputWithinRange_WhenInputChoiceCalled_ThenReturnValidInteger) {
    std::istringstream fakeInput("5\n");
    std::ostringstream fakeOutput;

    std::cin.rdbuf(fakeInput.rdbuf());
    std::cout.rdbuf(fakeOutput.rdbuf());

    int result = inputChoice(1, 10);

    EXPECT_EQ(result, 5);
    EXPECT_TRUE(fakeOutput.str().empty());
}

TEST_F(UtilityFunctionsTest, GivenInvalidInput_WhenInputChoiceCalled_ThenRepeatedlyAskForInputAgain) {
    std::istringstream fakeInput("abc\n3\n");
    std::ostringstream fakeOutput;

    std::cin.rdbuf(fakeInput.rdbuf());
    std::cout.rdbuf(fakeOutput.rdbuf());

    int result = inputChoice(1, 10);

    EXPECT_EQ(result, 3);
    std::string out = fakeOutput.str();
    EXPECT_TRUE(out.find(PRINT_INVALID_INPUT_ONE) != std::string::npos || out.find(PRINT_INVALID_INPUT_TWO) != std::string::npos);
}
