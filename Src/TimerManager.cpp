#include "TimerManager.h"

TimerManager::TimerManager(uint8_t max)
    : m_used(0)
{
    if (max > MAX_TIMERS)
    {
        throw EX_INVALID_ARGUMENT;
    }

    m_max = max;
    m_timers = new ITimer*[max];

    for (uint8_t i = 0; i < max; i++)
    {
        m_timers[i] = nullptr;
    }
}

TimerManager::~TimerManager()
{
    delete[] m_timers;
}

void TimerManager::Update()
{
    for (uint8_t i = 0; i < m_max; i++)
    {
        if (m_timers[i] != nullptr)
        {
            m_timers[i]->Increment(1);
        }
    }
}

void TimerManager::AddTimer(ITimer* timer)
{
    if (timer == nullptr)
    {
        throw EX_INVALID_ARGUMENT;
    }

    if (m_used == m_max)
    {
        throw EX_LIMIT_REACHED;
    }

    uint8_t freeIndex = 0xFF;
    for (uint8_t i = 0; i < m_max; i++)
    {
        if (m_timers[i] == timer)
        {
            throw EX_INVALID_ARGUMENT;
        }

        if (m_timers[i] == nullptr && freeIndex == 0xFF)
        {
            freeIndex = i;
        }
    }

    m_timers[freeIndex] = timer;
    m_used++;
}

void TimerManager::RemoveTimer(ITimer* timer)
{
    if (timer == nullptr)
    {
        throw EX_INVALID_ARGUMENT;
    }

    for (uint8_t i = 0; i < m_max; i++)
    {
        if (m_timers[i] == timer)
        {
            m_timers[i] = nullptr;
            m_used--;
            
            break;
        }
    }
}