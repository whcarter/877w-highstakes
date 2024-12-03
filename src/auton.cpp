#include "main.h"

// PIDController drive_pid(1.0, 0.0, 0.0, 10.0, &move, &get_position);

void move(double power)
{
    drive_left.spin(forward, power, volt);
    drive_right.spin(forward, power, volt);
}

double get_position()
{
    return 0.0;
}

void drive(int distance, int power = 12)
{
    double revs = distance / (3.14 * 4) / (2.333);
    drive_left.setPosition(0, turns);
    if (revs > 0)
    {
        while (drive_left.position(turns) < revs)
        {
            drive_left.spin(forward, power, volt);
            drive_right.spin(forward, power, volt);
        }
    }
    else
    {
        while (drive_left.position(turns) > revs)
        {
            drive_left.spin(reverse, power, volt);
            drive_right.spin(reverse, power, volt);
        }
    }
    drive_left.stop();
    drive_right.stop();
}

void turn(int angle, int power)
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

void pid_drive(int distance)
{
}

void auton()
{
    clamp.set(true);
    drive(-30, 4);
    wait(1000, msec);
    clamp.set(false);
    wait(1000, msec);
    drive(6, 8);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    wait(5000, msec);
    intake.stop();
}

void skills() {
    clamp.set(true);
    drive(-6);
    wait(1000, msec);
    turn(-90, 4);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    drive(50, 4);
    wait(10000, msec);
    intake.stop();
}