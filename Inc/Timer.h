#ifndef TIMER_H
#define TIMER_H

#include "ITimer.h"

#include <inttypes.h>

class Timer : public ITimer
{
    public:
        Timer() : Timer(0) { }
        Timer(uint64_t time) : m_time(time) { }
        ~Timer();

        // ITimer
        uint64_t GetTime() const { return m_time; }
        void SetTime(const uint64_t time) { m_time = time; }
        void Increment(const uint64_t time) { m_time += time; }
        void Reset() { m_time = 0; }

    private:
        uint64_t m_time;
};

#endif //TIMER_H