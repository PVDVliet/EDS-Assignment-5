#include "LedController.h"

LedController::LedController(IEventGenerator& eventGenerator, uint32_t capacity)
    : m_eventGenerator(eventGenerator)
    , m_currentState(STATE_IDLE)
    , m_run(true)
{
    if (capacity == 0)
    {
        throw EX_OUT_OF_RANGE;
    }
    m_capacity = capacity;
    m_leds = new ILed*[capacity];
    for (uint32_t i = 0; i < capacity; i++)
    {
        m_leds[i] = nullptr;
    }
}

LedController::~LedController()
{
    Stop();
    delete[] m_leds;
}

void LedController::Run()
{
    while (m_run)
    {
        HandleEvent(m_eventGenerator.GetEvent());
    }
}

void LedController::Stop()
{
    m_run = false;
}

uint32_t LedController::AddLed(ILed& led)
{
    for (uint32_t i = 0; i < m_capacity; i++)
    {
        if (m_leds[i] == nullptr)
        {
            m_leds[i] = &led;
            return i + 1;
        }
    }
    return 0;
}

void LedController::RemoveLed(uint32_t handle)
{
    if (handle == 0 || handle > m_capacity)
    {
        throw EX_INVALID_ARGUMENT;
    }

    m_leds[handle - 1] == nullptr;
}

ILed* LedController::GetLed(uint32_t handle)
{
    if (handle == 0 || handle > m_capacity)
    {
        throw EX_INVALID_ARGUMENT;
    }

    return m_leds[handle -1];
}

void LedController::HandleEvent(Event ev)
{
    switch (m_currentState)
    {
        case STATE_IDLE:
            HandleIdleState(ev);
            break;
    }
}

void LedController::HandleIdleState(Event ev)
{
    switch (ev)
    {
        case EV_BUTTON0_PRESSED:
            if (m_leds[0] != nullptr)
            {
                m_leds[0]->Set();
            }
            break;

        case EV_BUTTON0_PRESSED_LONG:
            if (m_leds[0] != nullptr)
            {
                m_leds[0]->Reset();
            }
            break;

        case EV_BUTTON1_PRESSED:
            if (m_leds[1] != nullptr)
            {
                m_leds[1]->Set();
            }
            break;

        case EV_BUTTON1_PRESSED_LONG:
            if (m_leds[1] != nullptr)
            {
                m_leds[1]->Reset();
            }
            break;
            
        default:
            break;
    }
}