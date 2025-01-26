#include "main.h"

// ============================ Primative Control =========================== //
double left_power = 0;
double right_power = 0;
double turn_power = 0;
double drive_power = 0;

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

void move_left(double power)
{
    drive_left.spin(forward, power, volt);
}
void move_right(double power)
{
    drive_right.spin(forward, power, volt);
}

void move_combined()
{
    move_left(drive_power + turn_power);
    move_right(drive_power - turn_power);
}

void set_left_power(double power)
{
    left_power = power;
    move_combined();
}

void set_right_power(double power)
{
    right_power = power;
    move_combined();
}

void set_turn_power(double power)
{
    turn_power = power;
    move_combined();
}

void set_drive_power(double power)
{
    drive_power = power;
    move_combined();
}

// =========================== Calculated Control =========================== //
void c_drive(int distance, int power = 12)
{
    double revs = distance / (3.14 * 4) / (2.333);
    double startPos = drive_left.position(turns);
    if (revs > 0)
    {
        while (drive_left.position(turns) - startPos < revs)
        {
            move(power);
        }
    }
    else
    {
        while (drive_left.position(turns) - startPos > revs)
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
    double startPos = drive_left.position(turns);
    if (revs > 0)
    {
        while (drive_left.position(turns) - startPos < revs)
        {
            drive_left.spin(forward, power, volt);
            drive_right.spin(reverse, power, volt);
        }
    }
    else
    {
        while (drive_left.position(turns) - startPos > revs)
        {
            drive_left.spin(reverse, power, volt);
            drive_right.spin(forward, power, volt);
        }
    }
    drive_left.stop();
    drive_right.stop();
}

// =============================== PID Control ============================== //
PIDController turn_pid(0.2, 0.0003, 0.01, 20.0, &set_turn_power, &getHeading, 2, -1, 500, 20000);
// PIDController turn_pid(0.2, 0.0008, 0.1, 20.0, &set_turn_power, &getHeading, 2, -1, 500, 5000);
//  PIDController turn_pid(0.001, 0, 0.00000000, 20.0, &turn, &getHeading, 2, -1, 500, false);
PIDController drive_pid(0.6, 0.00001, 0.000000015, 20.0, &set_drive_power, &getDistance, 1, -1, 500);
// PIDController left_pid(0.07, 0.00009, 0.000000015, 20.0, &set_left_power, &getLeftDistance, 1, -1, 500);
// PIDController right_pid(0.07, 0.00009, 0.000000015, 20.0, &set_right_power, &getRightDistance, 1, -1, 500);

// PID turn "heading" degrees clockwise
void turn_relative(double heading, bool blocking, double error_bound, double timeout)
{
    turn_pid.set_error_bound(error_bound);
    turn_pid.set_timeout(timeout);
    turn_pid.set_target(getHeading() + heading);
    turn_pid.start();
    while (blocking && turn_pid.running())
    {
        wait(100, msec);
    }
}

// PID drive "distance" inches straight
void drive_relative(double distance, bool blocking)
{
    turn_pid.set_error_bound(0);
    turn_pid.set_timeout(-1);
    turn_pid.set_target(getHeading());
    turn_pid.start();
    drive_left.setPosition(0, rev);
    drive_right.setPosition(0, rev);
    drive_pid.set_target(distance);
    drive_pid.start();
    while (blocking && drive_pid.running())
    {
        wait(100, msec);
    }
}

void start_turn_task()
{
    turn_pid.run();
}

void start_drive_task()
{
    drive_pid.run();
}
