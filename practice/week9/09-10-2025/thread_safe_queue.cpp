#include <iostream>
#include <queue>
#include <mutex>
#include <chrono>
#include <thread>
#include <condition_variable>

template<typename T>
class ThreadSafeQueue {

private:
    std::queue<T> kyu;
    std::mutex mtx;
    std::condition_variable cv;

public:
    ThreadSafeQueue() = default;

    void push(T value) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            kyu.push(value);
        }
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){ return !kyu.empty(); });
        T value = kyu.front();
        kyu.pop();
        return value;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mtx);
        return kyu.empty();
    }
};

ThreadSafeQueue<int> tsq;
std::mutex print_mutex;

void producer(int id) {
    for (int i = 1; i <= 5; i++) {
        tsq.push(i + id * 100);
        print_mutex.lock();
        std::cout << "Producer " << id << " pushed " << i + id * 100 << '\n';
        print_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

void consumer(int id) {
    for (int i = 1; i <= 5; i++) {
        int value = tsq.pop();
        print_mutex.lock();
        std::cout << "Consumer " << id << " popped " << value << '\n';
        print_mutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main() {
    std::thread p1(producer, 1);
    std::thread p2(producer, 2);
    std::thread c1(consumer, 1);
    std::thread c2(consumer, 2);

    p1.join();
    p2.join();
    c1.join();
    c2.join();

    return 0;
}