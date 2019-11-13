#ifndef BUTTON_H
#define BUTTON_H

#include "Event.h"
#include "Exceptions.h"
#include "IButton.h"
#include "IEventGenerator.h"
#include "ITimer.h"

#include <stm32f051x8.h>

#define PORT_SIZE 16

#define SHORT_PRESS 20
#define LONG_PRESS 500

class Button : public IButton
{
    public:
        Button(GPIO_TypeDef* port, uint8_t pin, IEventGenerator& eventGenerator, ITimer& timer, Event shortPress, Event longPress);
        ~Button();

        void Update();

        // IButton
        bool IsPressed() { return m_pressed; }
    
    private:
        GPIO_TypeDef* m_port;
        uint8_t m_pin;
        IEventGenerator& m_eventGenerator;
        ITimer& m_timer;
        bool m_pressed;
        Event m_shortPress;
        Event m_longPress;
};

#endif //BUTTON_H