#include <gtest/gtest.h>
#include <future>
#include <chrono>
#include <thread>
#include "TrafficSignal.h"

class TrafficSignalTest : public testing::Test {

protected:

    TrafficSignal trafficSignal;

};

TEST_F(TrafficSignalTest, GivenTrafficSignal_WhenConstructed_ThenTrafficLightIsRed) {

    EXPECT_FALSE(trafficSignal.isGreenLight());
}

TEST_F(TrafficSignalTest, GivenRedLight_WhenGreenLightSet_ThenWaitingThreadUnblocks) {

    bool threadUnblocked = false;

    std::thread t([&]() {
        trafficSignal.waitForGreenLight();
        threadUnblocked = true; 
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_FALSE(threadUnblocked);

    trafficSignal.setGreenLight();

    t.join();

    EXPECT_TRUE(threadUnblocked);
    EXPECT_TRUE(trafficSignal.isGreenLight());
}

TEST_F(TrafficSignalTest, GivenRedLight_WhenNoGreenSignal_ThenThreadStaysBlocked) {
    bool threadUnblocked = false;

    std::thread t([&]() {
        trafficSignal.waitForGreenLight();
        threadUnblocked = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    EXPECT_FALSE(threadUnblocked);

    trafficSignal.setGreenLight();
    t.join();
}

TEST_F(TrafficSignalTest, GivenLightIsGreen_WhenWaitForGreenLightCalled_ThenReturnsImmediately) {
    trafficSignal.setGreenLight();
    bool threadFinished = false;

    std::thread t([&]() {
        trafficSignal.waitForGreenLight();
        threadFinished = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    EXPECT_TRUE(threadFinished);

    t.join();
    EXPECT_TRUE(trafficSignal.isGreenLight());
}

TEST_F(TrafficSignalTest, GivenGreenLight_WhenRedLightSet_ThenSignalTurnsAndThreadIsBlocked) {

    trafficSignal.setGreenLight();
    ASSERT_TRUE(trafficSignal.isGreenLight());

    trafficSignal.setRedLight();
    ASSERT_FALSE(trafficSignal.isGreenLight());

    bool threadUnblocked = false;

    std::thread t([&]() {
        trafficSignal.waitForGreenLight();
        threadUnblocked = true;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_FALSE(threadUnblocked);

    trafficSignal.setGreenLight();
    t.join();
}

TEST_F(TrafficSignalTest, GivenMultipleWaitingThreads_WhenGreenLightSet_ThenOnlyOneThreadUnblocks) {
    constexpr int numThreads = 3;
    std::atomic<int> unblockedCount = 0;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&]() {
            trafficSignal.waitForGreenLight();
            unblockedCount++;
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    trafficSignal.setGreenLight();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    EXPECT_EQ(unblockedCount.load(), 1);

    trafficSignal.setGreenLight();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    trafficSignal.setGreenLight();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }
}

TEST_F(TrafficSignalTest, GivenMultipleSignals_WhenGreenLightSetRepeatedly_ThenEachThreadUnblocksOnce) {
    constexpr int numThreads = 3;
    std::atomic<int> unblockedCount = 0;
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&, i]() {
            trafficSignal.waitForGreenLight();
            unblockedCount++;

            trafficSignal.setRedLight();
        });
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    for (int i = 0; i < numThreads; ++i) {
        trafficSignal.setGreenLight();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        EXPECT_EQ(unblockedCount.load(), i + 1)
            << "After " << i + 1 << " green signals, " << i + 1 << " threads should have unblocked";
    }

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    EXPECT_EQ(unblockedCount.load(), numThreads);
}