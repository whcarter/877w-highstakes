#pragma once
#include "main.h"

enum PressType
{
    PULSE,
    TOGGLE,
    HOLD
};

enum Edge
{
    RISING,
    FALLING,
    CONTINUOUS
};

class Button
{
private:
    enum PressType type;
    enum Edge edge;
    bool state;
    bool previous_press;
    void (*callback)(bool);
    bool (*isPressed)();

    void action();

public:
    Button(void (*function)(bool), bool (*buttonPress)(), enum PressType t = TOGGLE, enum Edge e = RISING, bool initial = false);
    void find_press();
};