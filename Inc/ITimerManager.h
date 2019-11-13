#ifndef ITIMER_MANAGER_H
#define ITIMER_MANAGER_H

#include "ITimer.h"

#include <inttypes.h>

class ITimerManager
{
    public:
        virtual ~ITimerManager() { }
        
        virtual uint8_t GetMax() const = 0;
        virtual uint8_t GetUsed() const = 0;

        virtual void AddTimer(ITimer* timer) = 0;
        virtual void RemoveTimer(ITimer* timer) = 0;
};

#endif //ITIMER_MANAGER_H