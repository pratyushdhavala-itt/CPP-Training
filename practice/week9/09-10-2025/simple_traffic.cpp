#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

class Semaphore {

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;

public:
    Semaphore(int initCount = 0) : count{initCount} {}

    void wait() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){ return count > 0;});
        count--;
    }

    void signal() {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
};

Semaphore north_south(1);
Semaphore east_west(0);

void car(const std::string& direction, int id, Semaphore* sem) {
    sem->wait();
    std::cout << "Car " << id << " (" << direction << ") is crossing ..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Car " << id << " (" << direction << ") has passed..." << std::endl;
    sem->signal();
}

int main() {

    std::vector<std::thread> cars_north_south;
    std::vector<std::thread> cars_east_west;

    for (int i = 1; i <= 5; i++) {
        cars_north_south.emplace_back(car, "north-south", i, &north_south);
    }

    for (int i = 1; i <= 5; i++) {
        cars_east_west.emplace_back(car, "east-west", i, &east_west);
    }
    
    std::string input;

    bool north_south_green = true;

    while (true) {
        std::cout << "\nPress enter to switch lights\n";
        std::getline(std::cin, input);
        
        if (north_south_green) {
            std::cout << "Switch to East-West Green Light" << std::endl;
            north_south.wait();
            east_west.signal();
        } else {
             std::cout << "Switch to North-South Green Light" << std::endl;
            east_west.wait();
            north_south.signal();
        }

        north_south_green = !north_south_green;
    }

    for (auto& t : cars_north_south) {
        t.join();
    }

    for (auto& t : cars_east_west) {
        t.join();
    }
    return 0;
}