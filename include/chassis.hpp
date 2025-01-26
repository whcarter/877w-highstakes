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
void move_left(double power);
void move_right(double power);
void set_left_power(double power);
void set_right_power(double power);
void set_drive_power(double power);
void set_turn_power(double power);
void move_combined();

// Calculated Control
void c_drive(int distance, int power);
void c_turn(int angle, int power);

// PID Control
// PIDController turn_pid(1.0, 0.0, 0.0, 10.0, &turn, &getHeading);
void turn_relative(double heading, bool blocking = true, double error_bound = 2.0, double timeout = 5000);
void drive_relative(double distance, bool blocking = true);

void start_turn_task();
void start_drive_task();