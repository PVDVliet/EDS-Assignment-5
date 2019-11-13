#include "Led.h"

Led::Led(GPIO_TypeDef* port, uint8_t pin)
{
    if (pin >= PORT_SIZE || port == nullptr)
    {
        throw EX_INVALID_ARGUMENT;
    }

    m_pin = pin;
    m_port = port;

    m_port->MODER = (m_port->MODER & ~(3U << (m_pin * 2))) | (0b01 << (m_pin * 2));
	m_port->OTYPER &= ~(1U << m_pin);
}

Led::~Led()
{
    m_port->MODER = (m_port->MODER & ~(3U << (m_pin * 2)));
}

void Led::Set()
{
    m_port->ODR |= (1 << m_pin);
}

void Led::Reset()
{
    m_port->ODR &= ~(1 << m_pin);
}

void Led::Toggle()
{
    m_port->ODR ^= (1 << m_pin);
}