#include "main.h"

Button::Button(void (*function)(bool), bool (*button_press)(), enum PressType press_type, enum Edge press_edge, bool initial_state)
{
    is_pressed = button_press;
    callback = function;
    type = press_type;
    edge = press_edge;
    state = initial_state;
}

void Button::find_press()
{
    switch (edge)
    {
    case RISING:
        if (is_pressed() && !previous_press)
        {
            action();
        }
        break;

    case FALLING:
        if (!is_pressed() && previous_press)
        {
            action();
        }
        break;

    case CONTINUOUS:
        if (is_pressed() && !previous_press)
        {
            action();
        }
        if (!is_pressed() && previous_press)
        {
            action();
        }
        break;
    }
    previous_press = is_pressed();
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