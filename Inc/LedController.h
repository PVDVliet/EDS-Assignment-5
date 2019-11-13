#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "Event.h"
#include "Exceptions.h"
#include "IEventGenerator.h"
#include "ILed.h"

#include <stdint.h>

enum State
{
    STATE_IDLE,
};

class LedController
{
    public:
        LedController(IEventGenerator& eventGenerator,
            uint32_t capacity);
        ~LedController();

        void Run();
        void Stop();
        uint32_t AddLed(ILed& led);
        void RemoveLed(uint32_t handle);
        ILed* GetLed(uint32_t handle);

    private:
        uint32_t m_capacity;
        IEventGenerator& m_eventGenerator;
        ILed** m_leds;
        State m_currentState;
        bool m_run;

        void HandleEvent(Event ev);
        void HandleIdleState(Event ev);
};

#endif //LED_CONTROLLER_H