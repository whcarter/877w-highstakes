#pragma once
#include "main.h"

// ========================== Device Declarations ========================== //

extern brain Brain;
extern controller controller1;
extern controller controller2;

extern motor driveLf;
extern motor driveLb;
extern motor driveLt;
extern motor driveRf;
extern motor driveRb;
extern motor driveRt;
extern vex::motor_group drive_left;
extern vex::motor_group drive_right;
extern motor intake_top;
extern motor intake_bottom;
extern motor_group intake;
extern motor climb_left;
extern motor climb_right;
extern motor_group climb;

extern digital_out clamp;
extern digital_out intake_lift;
extern digital_out climb_release;
extern digital_out hook_latch_left;
extern digital_out hook_latch_right;

extern inertial imu;
extern gps gps_sensor;
extern optical intake_optical;
