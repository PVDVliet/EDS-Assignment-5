#ifndef LED_H
#define LED_H

#include "Exceptions.h"
#include "ILed.h"

#include <stm32f051x8.h>

#define PORT_SIZE 16

class Led : public ILed
{
    public:
        Led(GPIO_TypeDef* port, uint8_t pin);
        ~Led();

        // ILed
        bool IsOn() const { return m_port->IDR & (1 << m_pin) >> m_pin; }
        void Set();
        void Reset();
        void Toggle();

    private:
        GPIO_TypeDef* m_port;
        uint8_t m_pin;
};

#endif //LED_H