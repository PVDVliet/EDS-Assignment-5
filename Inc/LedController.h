#ifndef LED_CONTROLLER_H
#define LED_CONTROLLER_H

#include "IEventGenerator.h"
#include "ILed.h"

class LedController
{
    public:
        LedController(IEventGenerator& eventGenerator,
            unsigned int capacity);
        ~LedController();

        unsigned int AddLed(ILed& led);
        bool RemoveLed(unsigned int handle);
        ILed& GetLed(unsigned int handle);

    private:
        unsigned int m_capacity;
        ILed* m_leds;
};

#endif //LED_CONTROLLER_H