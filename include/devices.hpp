#pragma once
#include "main.h"

// ========================== Device Declarations ========================== //

extern brain Brain;
extern controller controller1;

extern motor driveLf;
extern motor driveLb;
extern motor driveRf;
extern motor driveRb;
extern vex::motor_group drive_left;
extern vex::motor_group drive_right;
extern motor intake;
extern motor climb_left;
extern motor climb_right;
extern motor_group climb;

extern digital_out clamp;
extern digital_out intake_lift;
extern digital_out climb_release;

extern inertial imu;
extern gps gps_sensor;
