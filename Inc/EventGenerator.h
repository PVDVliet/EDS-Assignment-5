#ifndef EVENT_GENERATOR_H
#define EVENT_GENERATOR_H

#include "Event.h"
#include "IEventGenerator.h"

class EventGenerator
{
    public:
        EventGenerator();
        ~EventGenerator();

        // IEventGenerator
        Event GetEvent();
        void PushEvent(Event ev);

    private:
        bool m_triggers[Event::COUNT - 1];
};

#endif //EVENT_GENERATOR_H