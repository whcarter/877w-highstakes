#include "main.h"

Button::Button(void (*function)(bool), bool (*buttonPress)(), enum PressType t, enum Edge e, bool initial)
{
    isPressed = buttonPress;
    callback = function;
    type = t;
    edge = e;
    state = initial;
}

void Button::find_press()
{
    switch (edge)
    {
    case RISING:
        if (isPressed() && !previous_press)
        {
            action();
        }
        break;

    case FALLING:
        if (!isPressed() && previous_press)
        {
            action();
        }
        break;

    case CONTINUOUS:
        if (isPressed() && !previous_press)
        {
            action();
        }
        if (!isPressed() && previous_press)
        {
            action();
        }
        break;
    }
    std::cout << "a: " << isPressed() << std::endl;
    previous_press = isPressed();
}

void Button::action()
{
    switch (type)
    {
    case PULSE:
        callback(state);
        break;
    case TOGGLE:
        state = !state;
        callback(state);
        break;
    }
}