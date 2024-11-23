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
    PRESSED
};

class Button
{
private:
    // bool previous_press;
    enum PressType type;
    enum Edge edge;
    controller::button button;

public:
    Button(controller::button b, void (*f)(bool), enum PressType t = TOGGLE, enum Edge e = RISING)
    {
        button = b;
        type = t;
        edge = e;
    }
    void find_press()
    {
    }
};