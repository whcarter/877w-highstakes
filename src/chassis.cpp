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

void moveLeft(double power)
{
    drive_left.spin(forward, power, volt);
}
void moveRight(double power)
{
    drive_right.spin(forward, power, volt);
}

void moveCombined()
{
    moveLeft(drive_power + turn_power);
    moveRight(drive_power - turn_power);
}

void setLeftPower(double power)
{
    left_power = power;
    moveCombined();
}

void setRightPower(double power)
{
    right_power = power;
    moveCombined();
}

void setTurnPower(double power)
{
    turn_power = power;
    moveCombined();
}

void setDrivePower(double power)
{
    drive_power = power;
    moveCombined();
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
PIDController turn_pid(0.2, 0.0003, 0.01, 20.0, &setTurnPower, &getHeading, 2, -1, 500, 20000);
//PIDController turn_pid(0.2, 0.0008, 0.1, 20.0, &setTurnPower, &getHeading, 2, -1, 500, 5000);
// PIDController turn_pid(0.001, 0, 0.00000000, 20.0, &turn, &getHeading, 2, -1, 500, false);
PIDController drive_pid(0.6, 0.00001, 0.000000015, 20.0, &setDrivePower, &getDistance, 1, -1, 500);
//PIDController left_pid(0.07, 0.00009, 0.000000015, 20.0, &setLeftPower, &getLeftDistance, 1, -1, 500);
//PIDController right_pid(0.07, 0.00009, 0.000000015, 20.0, &setRightPower, &getRightDistance, 1, -1, 500);

// PID turn "heading" degrees clockwise
void turnRelative(double heading, bool blocking, double error_bound, double timeout)
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

// Sets each PID for each drive half to given velocity, in rpm
/*void setDriveVelocity(double velocity)
{
    left_pid.set_target(velocity);
    right_pid.set_target(velocity);
    left_pid.start();
    right_pid.start();
}*/

// PID drive "distance" inches straight
void driveRelative(double distance, bool blocking)
{
    turn_pid.set_error_bound(0);
    turn_pid.set_timeout(-1);
    turn_pid.set_target(getHeading());
    turn_pid.start();
    drive_left.setPosition(0, rev);
    drive_right.setPosition(0, rev);
    //left_pid.set_target(distance);
    //right_pid.set_target(distance);
    drive_pid.set_target(distance);
    drive_pid.start();
    //left_pid.start();
    //right_pid.start();
    while (blocking && drive_pid.running())//(left_pid.running() || right_pid.running()))
    {
        wait(100, msec);
    }
}

void startTurnTask()
{
    turn_pid.run();
}

void startDriveTask()
{
    drive_pid.run();
}

/*void startLeftTask()
{
    left_pid.run();
}

void startRightTask()
{
    right_pid.run();
}
*/