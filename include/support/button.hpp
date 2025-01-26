#pragma once
#include "main.h"

enum PressType
{
    PULSE,
    TOGGLE
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
    bool (*is_pressed)();

    void action();

public:
   /*
	* @brief Tracker for a single button corresponding to a single action
	* 
	* @param	function		Action to be taken upon button press
	* @param	button_press	Get whether or not button is pressed
	* @param	press_type		Type of action to be performed: PULSE or TOGGLE
	* @param	press_edge		When to register a button press: FALLING, RISING, or CONTINUOUS
	* @param	intitial_state	If the bool "state" passed to function should begin true or false
	*/
    Button(void (*function)(bool), bool (*button_press)(), enum PressType press_type = TOGGLE, enum Edge press_edge = RISING, bool initial_state = false);

   /*
	* @brief Performs action if press condition is met
	*/
    void find_press();
};