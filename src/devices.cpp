#include "main.h"

// ========================== Device Declarations ========================== //

brain Brain;
controller controller1 = controller(primary);

// Motors
motor driveLf = motor(PORT19, ratio18_1, true);
motor driveLb = motor(PORT20, ratio18_1, true);
motor driveRf = motor(PORT17, ratio18_1, false);
motor driveRb = motor(PORT18, ratio18_1, false);
motor_group drive_left = motor_group(driveLf, driveLb);
motor_group drive_right = motor_group(driveRf, driveRb);
motor intake = motor(PORT11, ratio18_1, false);
motor climb_left = motor(PORT3, ratio18_1);
motor climb_right = motor(PORT4, ratio18_1);
motor_group climb = motor_group(climb_left, climb_right);

// Pneumatics
digital_out clamp = digital_out(Brain.ThreeWirePort.A);
digital_out intake_lift = digital_out(Brain.ThreeWirePort.B);
digital_out climb_release = digital_out(Brain.ThreeWirePort.C);

// Sensors
inertial imu = inertial(PORT1);
gps gps_sensor = gps(PORT2);
