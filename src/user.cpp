#include "main.h"

int intake_power = 0;
int climb_power = 0;
int intake_start;
bool intake_jammed = false;

const int deadzone = 0;
const float input_exp = 2;
const int intake_cooldown = 500;

// ========================= User Control Functions ========================= //
void arcade_drive(int left_x, int left_y, int right_x, int right_y)
{
	int left = left_y + right_x;
	int right = left_y - right_x;
	drive_left.spin(forward, left, volt);
	drive_right.spin(forward, right, volt);
}

// ============================= Input Processor ============================ //
double process_input(int value)
{
	double adjusted = (double)(value - deadzone) / (100 - deadzone);
	double scaled = pow(adjusted, input_exp);
	return (value > 0 ? scaled : -scaled) * 12;
}

// ============================= Button Mapping ============================= //
void pressA(bool state) { clamp.set(state); }
void pressB(bool state) { intake_lift.set(state); }
void pressR1(bool state = false)
{
	intake_power = intake_power > 0 ? 0 : 12;
	intake.spin(forward, intake_power, volt);
}
void pressL1(bool state = false)
{
	intake_power = intake_power < 0 ? 0 : -12;
	intake.spin(forward, intake_power, volt);
}
void pressUp(bool state = false)
{
	climb_power = climb_power > 0 ? 0 : 12;
	climb.spin(forward, climb_power, volt);
}
void pressDown(bool state = false)
{
	climb_power = climb_power < 0 ? 0 : -12;
	climb.spin(forward, climb_power, volt);
}
void pressR2L2(bool state) { 
	climb_release.set(state); 
}
void pressY(bool state) {
	hook_latch_left.set(state);
	hook_latch_right.set(state);
}

bool bA() { return controller1.ButtonA.pressing(); }
bool bB() { return controller1.ButtonB.pressing(); }
bool bY() { return controller1.ButtonY.pressing(); }
bool bR1() { return controller1.ButtonR1.pressing(); }
bool bL1() { return controller1.ButtonL1.pressing(); }
bool bUp() { return controller1.ButtonUp.pressing(); }
bool bDown() { return controller1.ButtonDown.pressing(); }
bool bR2L2()
{
	return controller1.ButtonR2.pressing() & controller1.ButtonL2.pressing();
}

Button butA = Button(&pressA, &bA, TOGGLE, RISING);
Button butB = Button(&pressB, &bB, TOGGLE, RISING);
Button butR1 = Button(&pressR1, &bR1, PULSE, RISING);
Button butL1 = Button(&pressL1, &bL1, PULSE, RISING);
Button butUp = Button(&pressUp, &bUp, PULSE, RISING);
Button butDown = Button(&pressDown, &bDown, PULSE, RISING);
Button butR2L2 = Button(&pressR2L2, &bR2L2, TOGGLE, RISING);
Button butY = Button(&pressY, &bY, TOGGLE, RISING);

// ================================== Task ================================== //
void user()
{
	// Pass joystick values into drive function
	int left_x = process_input(controller1.Axis4.position(percent));
	int left_y = process_input(controller1.Axis3.position(percent));
	int right_x = process_input(controller1.Axis1.position(percent));
	int right_y = process_input(controller1.Axis2.position(percent));
	arcade_drive(left_x, left_y, right_x, right_y);

	// Detect button presses
	butA.find_press();
	butB.find_press();
	butR1.find_press();
	butL1.find_press();
	butUp.find_press();
	butDown.find_press();
	butR2L2.find_press();
	butY.find_press();

	// Reverse intake if past stall torque
	if (intake.torque() > 1.1 && fabs(intake.velocity(rpm)) < 1)
	{
		intake_jammed = true;
		pressL1();
		intake_start = millis();
	}
	if (intake_jammed && millis() - intake_start > intake_cooldown)
	{
		intake_jammed = false;
		pressR1();
	}
}
