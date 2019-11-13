#include "Button.h"

#include <stdio.h>

Button::Button(GPIO_TypeDef* port, uint8_t pin, IEventGenerator& eventGenerator, ITimer& timer, Event shortPress, Event longPress)
    : m_eventGenerator(eventGenerator)
    , m_timer(timer)
    , m_pressed(false)
    , m_shortPress(shortPress)
    , m_longPress(longPress)
{
    if (pin >= PORT_SIZE || port == nullptr)
    {
        throw EX_INVALID_ARGUMENT;
    }

    m_port = port;
    m_pin = pin;

    m_port->MODER &= ~(3U << (m_pin * 2));
	m_port->PUPDR = (m_port->PUPDR & ~(3U << (m_pin))) | (0b10 << (m_pin * 2));
}

Button::~Button()
{
	m_port->PUPDR = (m_port->PUPDR & ~(3U << (m_pin)));
}

void Button::Update()
{
    m_pressed = m_port->IDR & (1 << m_pin) >> m_pin;

    if (m_pressed)
    {
        m_timer.Reset();
    }
    else
    {
        uint64_t time = m_timer.GetTime();

        if (time > SHORT_PRESS && time < LONG_PRESS)
        {
            m_eventGenerator.PushEvent(m_shortPress);
        }
        else if (time > LONG_PRESS)
        {
            m_eventGenerator.PushEvent(m_longPress);
        }
    }
}