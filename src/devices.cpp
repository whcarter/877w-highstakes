#include "main.h"

// ========================== Device Declarations ========================== //

controller controller1 = controller(primary);

// Motors
motor driveLf = motor(PORT1, ratio18_1, true);
motor driveLb = motor(PORT8, ratio18_1, true);
motor driveRf = motor(PORT2, ratio18_1, false);
motor driveRb = motor(PORT10, ratio18_1, false);
motor_group drive_left = motor_group(driveLf, driveLb);
motor_group drive_right = motor_group(driveRf, driveRb);
