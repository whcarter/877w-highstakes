#pragma once
#include "main.h"

// Build Constants
const double WHEELBASE = 16.0;
const double TRACK = 16.0;
const double WHEEL_DIAMETER = 4.125;
const double DRIVE_RATIO = 36.0 / 84.0;

// Primative Control
void turn(double power);
void move(double power);

// Calculated Control
void c_drive(int distance, int power);

// PID Control
// PIDController turn_pid(1.0, 0.0, 0.0, 10.0, &turn, &getHeading);
void turnRelative(double heading);
void driveRelative(double distance);

void startTurnTask();
void startDriveTask();