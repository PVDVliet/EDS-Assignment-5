#ifndef LED_H
#define LED_H

#include "ILed.h"

#include <stm32f051x8.h>

class Led : public ILed
{
    public:
        Led(GPIO_TypeDef* port);
        ~Led();

        // ILed
        bool IsOn() const;
        void Set();
        void Reset();
        void Toggle();

    private:
        GPIO_TypeDef* m_port;
};

#endif //LED_H