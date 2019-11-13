#ifndef ITIMER_H
#define ITIMER_H

#include <inttypes.h>

class ITimer
{
    public:
        virtual ~ITimer() { }

        virtual uint64_t GetTime() const = 0;
        virtual void SetTime(const uint64_t time) = 0;
        virtual void Increment(const uint64_t time) = 0;
        virtual void Reset() = 0;
};

#endif // ITIMER_H