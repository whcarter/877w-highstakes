#include "main.h"

double millis()
{
    using namespace std::chrono;
    auto epoch = high_resolution_clock::from_time_t(0);
    auto now = high_resolution_clock::now();
    auto mseconds = duration_cast<milliseconds>(now - epoch).count();
    return (double)mseconds;
}