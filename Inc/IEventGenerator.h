#ifndef IEVENT_GENERATOR_H
#define IEVENT_GENERATOR_H

#include "Event.h"

class IEventGenerator
{
    public:
        virtual ~IEventGenerator() { }

        virtual Event GetEvent() = 0;
        virtual void PushEvent(Event ev) = 0;
};

#endif //IEVENT_GENERATOR_H