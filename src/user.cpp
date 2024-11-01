#include "main.h"

bool a_previous_press = false;
bool x_previous_press = false;
bool b_previous_press = false;
bool y_previous_press = false;
bool r1_previous_press = false;
bool l1_previous_press = false;
bool clamp_on = false;
bool lift_on = false;
bool push_on = false;
int intake_power = 0;

const int deadzone = 0;
const float input_exp = 2;

// ========================= User Control Functions ========================= //

double process_input(int value)
{
    double adjusted = (double)(value - deadzone) / (100 - deadzone);
    double scaled = pow(adjusted, input_exp);
    return (value > 0 ? scaled : -scaled) * 12;
}

void arcade_drive(int left_x, int left_y, int right_x, int right_y)
{
    int left = left_y + right_x;
    int right = left_y - right_x;
    drive_left.spin(forward, left, volt);
    drive_right.spin(forward, right, volt);
}

// ========================= Input Processor & Task ========================= //

void user()
{
    int left_x = process_input(controller1.Axis4.position(percent));
    int left_y = process_input(controller1.Axis3.position(percent));
    int right_x = process_input(controller1.Axis1.position(percent));
    int right_y = process_input(controller1.Axis2.position(percent));
    arcade_drive(left_x, left_y, right_x, right_y);

    if (controller1.ButtonA.pressing())
    {
        if (!a_previous_press)
        {
            clamp_on = !clamp_on;
        }
        clamp.set(clamp_on);
    }
    a_previous_press = controller1.ButtonA.pressing();

    if (controller1.ButtonB.pressing() && !b_previous_press)
    {
        lift_on = !lift_on;
        intake_lift.set(lift_on);
    }
    b_previous_press = controller1.ButtonB.pressing();

    if (controller1.ButtonY.pressing() && !y_previous_press)
    {
        push_on = !push_on;
        pulldown_bar.set(push_on);
    }
    y_previous_press = controller1.ButtonY.pressing();

    if (controller1.ButtonR1.pressing() && !r1_previous_press)
    {
        intake_power = intake_power > 0 ? 0 : 12;
    }
    r1_previous_press = controller1.ButtonR1.pressing();
    if (controller1.ButtonL1.pressing() && !l1_previous_press)
    {
        intake_power = intake_power < 0 ? 0 : -12;
    }
    l1_previous_press = controller1.ButtonL1.pressing();
    intake.spin(forward, intake_power, volt);
}
