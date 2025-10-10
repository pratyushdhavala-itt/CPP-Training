#include <iostream>
#include <thread>
#include "Lane.h"
#include "Semaphore.h"

Lane::Lane(int id, int numberOfCars, Semaphore* signal, std::mutex& ioLock) : id{id}, numberOfCars{numberOfCars}, signal{*signal}, ioLock{ioLock} {}

int Lane::getCarCount() const {
    return numberOfCars;
}

int Lane::getId() const {
    return id;
}

void Lane::simulate() {
    signal.wait();
    {
        std::lock_guard<std::mutex> lock(ioLock);
        std::cout << "Lane " << id << " is green" << std::endl;
    }

    for (int i = 0; i < numberOfCars; i++) {
        {
            std::lock_guard<std::mutex> lock(ioLock);
            std::cout << "Car " << (i + 1) << " from Lane " << id << " passing..." << std::endl;   
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    {
        std::lock_guard<std::mutex> lock(ioLock);
        std::cout << "Lane " << id << " is red now" << std::endl;
    }

}