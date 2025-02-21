#include "main.h"

int intake_power = 0;
int climb_power_left = 0;
int climb_power_right = 0;
int intake_start;
bool intake_jammed = false;
bool climb_override = false;

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
void toggle_clamp(bool state) { clamp.set(state); }
void toggle_intake_lift(bool state) { intake_lift.set(state); }
void toggle_intake_in(bool state = false)
{
	intake_power = intake_power > 0 ? 0 : 12;
	intake.spin(forward, intake_power, volt);
}
void toggle_intake_out(bool state = false)
{
	intake_power = intake_power < 0 ? 0 : -12;
	intake.spin(forward, intake_power, volt);
}
void toggle_climb_up(bool state = false)
{
	climb_power_left = climb_power_left > 0 ? 0 : 12;
	climb_power_right = climb_power_left;
	climb.spin(forward, climb_power_left, volt);
	climb_override = false;
}
void toggle_climb_down(bool state = false)
{
	climb_power_left = climb_power_left < 0 ? 0 : -12;
	climb_power_right = climb_power_left;
	climb.spin(forward, climb_power_left, volt);
	climb_override = false;
}
void toggle_climb_hoist(bool state) { 
	climb_release.set(state); 
}
void toggle_hook_latch(bool state) {
	hook_latch_left.set(state);
	hook_latch_right.set(state);
}
void toggle_hook_latch_left(bool state) {
	hook_latch_left.set(state);
}
void toggle_hook_latch_right(bool state) {
	hook_latch_right.set(state);
}


bool c1bA() { return controller1.ButtonA.pressing(); }
bool c1bB() { return controller1.ButtonB.pressing(); }
bool c1bY() { return controller1.ButtonY.pressing(); }
bool c1bR1() { return controller1.ButtonR1.pressing(); }
bool c1bL1() { return controller1.ButtonL1.pressing(); }
bool c1bUp() { return controller1.ButtonUp.pressing(); }
bool c1bDown() { return controller1.ButtonDown.pressing(); }
bool c1bR2L2()
{
	return controller1.ButtonR2.pressing() & controller1.ButtonL2.pressing();
}
bool c2bR1() { return controller2.ButtonR1.pressing(); };
bool c2bL1() { return controller2.ButtonL1.pressing(); };
bool c2bLeft() { return controller2.ButtonLeft.pressing(); };
bool c2bRight() { return controller2.ButtonRight.pressing(); };
bool c2bR2L2()
{
	return controller2.ButtonR2.pressing() & controller2.ButtonL2.pressing();
}

Button But1A = Button(&toggle_clamp, &c1bA, TOGGLE, RISING);
Button But1B = Button(&toggle_intake_lift, &c1bB, TOGGLE, RISING);
Button But1R1 = Button(&toggle_intake_in, &c1bR1, PULSE, RISING);
Button But1L1 = Button(&toggle_intake_out, &c1bL1, PULSE, RISING);
Button But1Up = Button(&toggle_climb_up, &c1bUp, PULSE, RISING);
Button But1Down = Button(&toggle_climb_down, &c1bDown, PULSE, RISING);
Button But1R2L2 = Button(&toggle_climb_hoist, &c1bR2L2, TOGGLE, RISING);
Button But1Y = Button(&toggle_hook_latch, &c1bY, TOGGLE, RISING);

Button But2R1 = Button(&toggle_hook_latch_right, &c2bR1, PULSE, RISING);
Button But2L1 = Button(&toggle_hook_latch_left, &c2bR1, PULSE, RISING);
Button But2R2L2 = Button(&toggle_climb_hoist, &c2bR2L2, TOGGLE, RISING);

std::list<Button> c1_buttons = {But1A, But1B, But1R1, But1L1, But1Up, But1Down, But1R2L2, But1Y};
std::list<Button> c2_buttons = {But2R1, But2L1, But2R2L2};

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
	
	But1A.find_press();
	But1B.find_press();
	But1R1.find_press();
	But1L1.find_press();
	But1Up.find_press();
	But1Down.find_press();
	But1R2L2.find_press();
	But1Y.find_press();
	But2R1.find_press();
	But2L1.find_press();
	But2R2L2.find_press();
	
	/*
	for (Button B : c1_buttons) {
		B.find_press();
	}
	for (Button B : c2_buttons) {
		B.find_press();
	}*/

	// Second controller climb mapping
	if (abs(controller2.Axis3.position(percent)) > deadzone || abs(controller2.Axis2.position(percent)) > deadzone) {
		climb_override = true;
	}
	if (climb_override) {
		climb_power_left = controller2.Axis3.position(percent) / 100.0 * 12.0;
		climb_power_right = controller2.Axis2.position(percent) / 100.0 * 12.0;
		climb_left.spin(forward, climb_power_left, volt);
		climb_right.spin(forward, climb_power_right, volt);
	}

	// Reverse intake if past stall torque
	if (intake.torque() > 1.1 && fabs(intake.velocity(rpm)) < 1)
	{
		intake_jammed = true;
		toggle_intake_out();
		intake_start = millis();
	}
	if (intake_jammed && millis() - intake_start > intake_cooldown)
	{
		intake_jammed = false;
		toggle_intake_in();
	}
}
