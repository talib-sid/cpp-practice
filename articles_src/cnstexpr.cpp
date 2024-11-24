#include <iostream>
#include <chrono>

void functionToBenchmark() {
    // Simulate a workload
    for (volatile int i = 0; i < 1000000; ++i);
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    functionToBenchmark();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> durationMicro = end - start;
    std::chrono::duration<double, std::milli> durationMilli = end - start;

    std::cout << "Execution time in microseconds: " << durationMicro.count() << " us" << std::endl;
    std::cout << "Execution time in milliseconds: " << durationMilli.count() << " ms" << std::endl;

    return 0;
}





