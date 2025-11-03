#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>
#include <string>
#include "ElevatorLogger.h"
#include "constants.h"

class MockLogger : public ElevatorLogger {
public:
    MOCK_METHOD(void, filterAndInsertLogs, (std::string content), (override));
    MOCK_METHOD(void, convertToStructuredString, (), (override));
};

class ElevatorLoggerTest : public ::testing::Test {
protected:
    ElevatorLogger logger;
};

TEST_F(ElevatorLoggerTest, GivenLogger_WhenElevatorOneRuns_ThenAddToElevatorOneLogs) {
    std::string log = "[ELEVATOR 1]: Moving Up";
    logger.filterAndInsertLogs(log);

    ASSERT_EQ(logger.getElevatorOneLogs().size(), 1);
    EXPECT_EQ(logger.getElevatorOneLogs()[0], "Moving Up");
    EXPECT_EQ(logger.getElevatorTwoLogs().size(), 0);
}

TEST_F(ElevatorLoggerTest, GivenLogger_WhenElevatorTwoRuns_ThenAddToElevatorTwoLogs) {
    std::string log = "[ELEVATOR 2]: Opening Doors";
    logger.filterAndInsertLogs(log);

    ASSERT_EQ(logger.getElevatorTwoLogs().size(), 1);
    EXPECT_EQ(logger.getElevatorTwoLogs()[0], "Opening Doors");
    EXPECT_EQ(logger.getElevatorOneLogs().size(), 0);
}

TEST_F(ElevatorLoggerTest, GivenLogger_WhenRandomTextGiven_ThenIgnore) {
    std::string log = "Random text";
    logger.filterAndInsertLogs(log);

    EXPECT_EQ(logger.getElevatorOneLogs().size(), 0);
    EXPECT_EQ(logger.getElevatorTwoLogs().size(), 0);
}

TEST_F(ElevatorLoggerTest, GivenLogger_WhenLogTextGive_ThenExtractContentAfterElevatorTag) {
    std::string log = "[ELEVATOR 1]: Passing 2 floor";
    logger.filterAndInsertLogs(log);

    ASSERT_EQ(logger.getElevatorOneLogs().size(), 1);
    EXPECT_EQ(logger.getElevatorOneLogs()[0], "Passing 2 floor");
}

TEST_F(ElevatorLoggerTest, GivenLogger_WhenMultipleLogTextsGiven_ThenProcessThemInOrder) {
    logger.filterAndInsertLogs("[ELEVATOR 1]: Opening Doors");
    logger.filterAndInsertLogs("[ELEVATOR 2]: Moving Down");
    logger.filterAndInsertLogs("[ELEVATOR 1]: Closing Doors");

    EXPECT_EQ(logger.getElevatorOneLogs().size(), 2);
    EXPECT_EQ(logger.getElevatorTwoLogs().size(), 1);
    EXPECT_EQ(logger.getElevatorOneLogs()[0], "Opening Doors");
    EXPECT_EQ(logger.getElevatorTwoLogs()[0], "Moving Down");

    EXPECT_EQ(logger.getMaxLogSize(), 3);
}

TEST_F(ElevatorLoggerTest, FormatsLogsIntoAlignedString) {
    logger.getMaxLogSize() = 1;
    logger.getElevatorOneLogs() = {"Moving Up"};
    logger.getElevatorTwoLogs() = {"Opening Doors"};

    logger.convertToStructuredString();

    std::string expected = "Moving Up"
                           + std::string(45 - std::string("Moving Up").length(), ' ')
                           + " | Opening Doors\n";

    EXPECT_TRUE(logger.getPrettyString().find("Moving Up") != std::string::npos);
    EXPECT_TRUE(logger.getPrettyString().find("Opening Doors") != std::string::npos);
}

TEST_F(ElevatorLoggerTest, PadsMissingElevatorColumn) {
    logger.getMaxLogSize() = 1;
    logger.getElevatorOneLogs() = {"Closing Doors"};
    logger.getElevatorTwoLogs() = {}; // missing second

    logger.convertToStructuredString();

    EXPECT_TRUE(logger.getPrettyString().find("Closing Doors") != std::string::npos);
    EXPECT_TRUE(logger.getPrettyString().find("|") != std::string::npos);
}

TEST_F(ElevatorLoggerTest, ResizesLogsToMaxLogSize) {
    logger.getMaxLogSize() = 3;
    logger.getElevatorOneLogs() = {"A"};
    logger.getElevatorTwoLogs() = {"B", "C"};

    logger.convertToStructuredString();

    EXPECT_EQ(logger.getElevatorOneLogs().size(), 3);
    EXPECT_EQ(logger.getElevatorTwoLogs().size(), 3);
}

TEST_F(ElevatorLoggerTest, AppendsFormattedRowsSequentially) {
    logger.getMaxLogSize() = 1;
    logger.getElevatorOneLogs() = {"Log1"};
    logger.getElevatorTwoLogs() = {"Log2"};
    logger.convertToStructuredString();

    logger.getMaxLogSize() = 2;
    logger.getElevatorOneLogs().push_back("Log3");
    logger.getElevatorTwoLogs().push_back("Log4");
    logger.convertToStructuredString();

    EXPECT_TRUE(logger.getPrettyString().find("Log1") != std::string::npos);
    EXPECT_TRUE(logger.getPrettyString().find("Log4") != std::string::npos);
    EXPECT_GE(std::count(logger.getPrettyString().begin(), logger.getPrettyString().end(), '\n'), 2);
}

TEST_F(ElevatorLoggerTest, UpdatesElevatorOneFloorAndLogs) {
    ElevatorLogger logger;
    logger(1, 5, "[ELEVATOR 1]: Moving Up");

    EXPECT_EQ(logger.getElevatorOneCurrentFloor(), 5);
    EXPECT_TRUE(logger.getElevatorOneLogs().size() > 0);
    EXPECT_EQ(logger.getElevatorOneLogs()[0], "Moving Up");
}

TEST_F(ElevatorLoggerTest, UpdatesElevatorTwoFloorAndLogs) {
    ElevatorLogger logger;
    logger(2, 8, "[ELEVATOR 2]: Opening Doors");

    EXPECT_EQ(logger.getElevatorTwoCurrentFloor(), 8);
    EXPECT_TRUE(logger.getElevatorTwoLogs().size() > 0);
    EXPECT_EQ(logger.getElevatorTwoLogs()[0], "Opening Doors");
}


TEST_F(ElevatorLoggerTest, WritesFormattedOutputToFile) {
    ElevatorLogger logger;
    logger(1, 2, "[ELEVATOR 1]: Opening Doors");

    std::ifstream file("output.txt");
    ASSERT_TRUE(file.is_open());

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    EXPECT_TRUE(content.find("ELEVATOR 1") != std::string::npos);
    EXPECT_TRUE(content.find("FLOOR: 2") != std::string::npos);
    EXPECT_TRUE(content.find("Opening Doors") != std::string::npos);
}

TEST_F(ElevatorLoggerTest, InvokesHelperFunctions) {
    MockLogger logger;

    EXPECT_CALL(logger, filterAndInsertLogs("[ELEVATOR 1]: Test Log")).Times(1);
    EXPECT_CALL(logger, convertToStructuredString()).Times(1);

    logger(1, 3, "[ELEVATOR 1]: Test Log");
}