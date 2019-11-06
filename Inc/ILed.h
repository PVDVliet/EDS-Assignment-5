#ifndef ILED_H
#define ILED_H

class ILed
{
    public:
        virtual ~ILed() {}

        virtual bool IsOn() const = 0;

        virtual void Set() = 0;
        virtual void Reset() = 0;
        virtual void Toggle() = 0;
};

#endif //ILED_H