#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include "Exceptions.h"
#include "ITimer.h"
#include "ITimerManager.h"

#include <inttypes.h>

#define MAX_TIMERS 32

class TimerManager : public ITimerManager
{
    public:
        TimerManager(uint8_t max);
        ~TimerManager();

        void Update();

        // ITimerManager
        uint8_t GetMax() const { return m_max; }
        uint8_t GetUsed() const { return m_used; }
        void AddTimer(ITimer* timer);
        void RemoveTimer(ITimer* timer);

    private:
        uint8_t m_max;
        uint8_t m_used;
        ITimer** m_timers;
};

#endif //TIMER_MANAGER_H