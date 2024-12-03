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

// =============================== PID Control ============================== //
PIDController turn_pid(0.07, 0.00009, 0.000000005, 20.0, &turn, &getHeading, 2, -1, 500);
PIDController drive_pid(0.07, 0.00009, 0.000000015, 20.0, &move, &getDistance, 1, -1, 500);

// PID turn "heading" degrees clockwise
void turnRelative(double heading)
{
    while (heading > 180)
        heading -= 360;
    while (heading < -180)
        heading += 360;
    // imu.setHeading(0, degrees);
    wait(2000, msec);
    turn_pid.set_target(heading);
    turn_pid.start();
}

// PID drive "distance" inches straight
void driveRelative(double distance)
{
    drive_pid.set_target(distance);
    drive_pid.start();
}

void startTurnTask()
{
    turn_pid.run();
}

void startDriveTask()
{
    drive_pid.run();
}