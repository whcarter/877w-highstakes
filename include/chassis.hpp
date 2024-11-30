#pragma once
#include "main.h"

double getHeading();
void turn(double power);

//PIDController turn_pid(1.0, 0.0, 0.0, 10.0, &turn, &getHeading);
void turnRelative(double heading);

void startTask();