#include "main.h"

// ========================== Device Declarations ========================== //

brain Brain;
controller controller1 = controller(primary);

// Motors
motor driveLf = motor(PORT1, ratio18_1, true);
motor driveLb = motor(PORT8, ratio18_1, true);
motor driveRf = motor(PORT2, ratio18_1, false);
motor driveRb = motor(PORT10, ratio18_1, false);
motor_group drive_left = motor_group(driveLf, driveLb);
motor_group drive_right = motor_group(driveRf, driveRb);

// Pneumatics
digital_out clamp_left = digital_out(Brain.ThreeWirePort.A);
digital_out clamp_right = digital_out(Brain.ThreeWirePort.B);
