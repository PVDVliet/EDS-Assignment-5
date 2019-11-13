#ifndef IBUTTON_H
#define IBUTTON_H

class IButton
{
    public:
        virtual ~IButton() { }

        virtual bool IsPressed() = 0;
};

#endif // IBUTTON_H