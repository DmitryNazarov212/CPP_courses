#pragma once
#include <chrono>

typedef std::chrono::steady_clock::time_point time_mark;

class TimeCounter
{
private:
    time_mark begin;
    time_mark end;
public:
    TimeCounter(){}
    ~TimeCounter(){}
    void start()
    {
        begin = std::chrono::steady_clock::now();
    }
    void stop()
    {
        end = std::chrono::steady_clock::now();
    }
    double result()
    {
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        double res = static_cast<double>(ms.count());
        return res / 1000;
    }
};
