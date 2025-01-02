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
void moveLeft(double power);
void moveRight(double power);
void setLeftPower(double power);
void setRightPower(double power);
void setTurnPower(double power);

// Calculated Control
void c_drive(int distance, int power);
void c_turn(int angle, int power);

// PID Control
// PIDController turn_pid(1.0, 0.0, 0.0, 10.0, &turn, &getHeading);
void turnRelative(double heading, bool blocking = true);
void setDriveVelocity(double velocity);
void driveRelative(double distance, bool blocking = true);

void startTurnTask();
void startLeftTask();
void startRightTask();
void startDriveTask();