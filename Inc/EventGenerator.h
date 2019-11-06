#ifndef EVENT_GENERATOR_H
#define EVENT_GENERATOR_H

#include "IEventGenerator.h"

class EventGenerator
{
    public:
        EventGenerator();
        ~EventGenerator();

        // IEventGenerator
        Event GetEvent();
        void PushEvent(Event ev);
};

#endif //EVENT_GENERATOR_H