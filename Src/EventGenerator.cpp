#include "EventGenerator.h"

EventGenerator::EventGenerator()
{
    for (int i = 0; i < Event::COUNT - 1; i++)
    {
        m_triggers[i] = false;
    }
}

EventGenerator::~EventGenerator()
{

}

Event EventGenerator::GetEvent()
{
    for (int i = 0; i < Event::COUNT - 1; i++)
    {
        if (m_triggers[i] == true)
        {
            m_triggers[i] = false;
            return (Event)(i + 1);
        }
    }

    return EV_NO_EVENT;
}

void EventGenerator::PushEvent(Event ev)
{
    m_triggers[ev - 1] = true;
}