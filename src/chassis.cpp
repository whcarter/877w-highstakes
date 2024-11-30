#include "main.h"

double getHeading()
{
    double heading = imu.heading();
    while (heading > 180)
        heading -= 360;
    while (heading < -180)
        heading += 360;
    return heading;
}

void turn(double power)
{
    drive_left.spin(forward, power, volt);
    drive_right.spin(reverse, power, volt);
}

PIDController turn_pid(0.07, 0.00009, 0.000000005, 20.0, &turn, &getHeading, 2, -1, 500);

void turnRelative(double heading)
{
    while (heading > 180)
        heading -= 360;
    while (heading < -180)
        heading += 360;
    // imu.setHeading(0, degrees);
    std::cout << "start\n";
    wait(2000, msec);
    turn_pid.set_target(heading);
    turn_pid.start();
    turn_pid.run();
}

void startTask()
{
    turn_pid.run();
}