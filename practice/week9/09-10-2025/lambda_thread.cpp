#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back([i]() {
            std::cout << "Lambda Thread " << i << " is running...\n";
        });
    }

    for (auto& t : threads)
        t.join();

    std::cout << "All lambda threads finished!\n";
    return 0;
}
