#include "main.h"

// ============================ Primative Control =========================== //
void turn(double power)
{
    drive_left.spin(forward, power, volt);
    drive_right.spin(reverse, power, volt);
}

void move(double power)
{
    drive_left.spin(forward, power, volt);
    drive_right.spin(forward, power, volt);
}

void moveLeft(double power)
{
    drive_left.spin(forward, power, volt);
}
void moveRight(double power)
{
    drive_right.spin(forward, power, volt);
}

// =========================== Calculated Control =========================== //
void c_drive(int distance, int power = 12)
{
    double revs = distance / (3.14 * 4) / (2.333);
    drive_left.setPosition(0, turns);
    if (revs > 0)
    {
        while (drive_left.position(turns) < revs)
        {
            move(power);
        }
    }
    else
    {
        while (drive_left.position(turns) > revs)
        {
            move(-power);
        }
    }
    drive_left.stop();
    drive_right.stop();
}

void c_turn(int angle, int power)
{
    double distance = (angle / 360.0) * 15.5 * 3.14;
    double revs = distance / (3.14 * 4) / (2.333);
    drive_left.setPosition(0, turns);
    if (revs > 0)
    {
        while (drive_left.position(turns) < revs)
        {
            drive_left.spin(forward, power, volt);
            drive_right.spin(reverse, power, volt);
        }
    }
    else
    {
        while (drive_left.position(turns) > revs)
        {
            drive_left.spin(reverse, power, volt);
            drive_right.spin(forward, power, volt);
        }
    }
    drive_left.stop();
    drive_right.stop();
}

// =============================== PID Control ============================== //
PIDController turn_pid(0.4, 0.0008, 0.1, 20.0, &turn, &getHeading, 2, -1, 500, 5000);
// PIDController turn_pid(0.001, 0, 0.00000000, 20.0, &turn, &getHeading, 2, -1, 500, false);
//  PIDController drive_pid(0.07, 0.00009, 0.000000015, 20.0, &move, &getDistance, 1, -1, 500);
PIDController left_pid(0.01, 0, 0, 10, &moveLeft, &getLeftVelocity, 2, -1, -1, -1, true);
PIDController right_pid(0.01, 0, 0, 10, &moveRight, &getRightVelocity, 2, -1, -1, -1, true);
PIDController drive_pid(0.03, 0 * 0.00009, 0 * 0.000000015, 20.0, &setDriveVelocity, &getDistance, 1, 5000, 500);

// PID turn "heading" degrees clockwise
void turnRelative(double heading, bool blocking)
{
    /*while (heading > 180)
        heading -= 360;
    while (heading < -180)
        heading += 360;
    imu.setHeading(0, degrees);
    wait(2000, msec);*/
    turn_pid.set_target(getHeading() + heading);
    turn_pid.start();
    while (blocking && turn_pid.running())
    {
        wait(100, msec);
    }
}

// Sets each PID for each drive half to given velocity, in rpm
void setDriveVelocity(double velocity)
{
    left_pid.set_target(velocity);
    right_pid.set_target(velocity);
    left_pid.start();
    right_pid.start();
}

// PID drive "distance" inches straight
void driveRelative(double distance, bool blocking)
{
    drive_left.setPosition(0, rev);
    drive_right.setPosition(0, rev);
    drive_pid.set_target(distance);
    drive_pid.start();
    while (blocking && turn_pid.running())
    {
        wait(100, msec);
    }
}

void startTurnTask()
{
    turn_pid.run();
}

void startLeftTask()
{
    left_pid.run();
}

void startRightTask()
{
    right_pid.run();
}

void startDriveTask()
{
    drive_pid.run();
}