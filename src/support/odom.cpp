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

double getDistance()
{
    double avg = (drive_left.position(rev) + drive_right.position(rev)) / 2.0;
    double distance = avg * WHEEL_DIAMETER * M_PI / DRIVE_RATIO;
    return distance;
}

double getLeftVelocity() {
    return drive_left.velocity(rpm) / DRIVE_RATIO;
}

double getRightVelocity() {
    return drive_right.velocity(rpm) / DRIVE_RATIO;
}

/*
const std::pair<double, double> left_offset = {-2.882, 0.718}; // Old: {-4.829, 1.4675}
const std::pair<double, double> rear_offset = {1.741, 1.539};  // Old: {1.1655, 0.825}
const double radian = 0.0174533;

double odom_x = 0;
double odom_y = 0;
double left_odom_dist = 0;
double rear_odom_dist = 0;
double imu_heading = 0;

double toRadians(double degrees)
{
    return degrees * M_PI / 180;
}

double left_position()
{
    return odom_left.get_position();
}

double right_position()
{
    return odom_right.get_position();
}

double rear_position()
{
    return odom_rear.get_position();
}

void set_left(double position) odom_left.set_position(position);

void set_right(double position) odom_right.set_position(position);

void set_rear(double position) odom_rear.set_position(position);

void odom::initialize()
{
    set_left(0);
    set_rear(0);
    // odom_left.set_reversed(true);
    // odom_rear.set_reversed(true);
    imu.calibrate();

    while (imu.isCalibrating())
    {
        wait(200, msec);
    }
}

[[noreturn]] void odom::track_position()
{
    auto left_dist = 0, rear_dist = 0;
    double y_radius, x_radius, local_x, local_y, total_dist;
    double prev_heading = (double)(imu.heading()), heading_change, robot_heading,
           local_true_heading, global_true_heading, left_odom, rear_odom;
    while (true)
    {
        left_odom = (double)(left_position() / 100.0);
        rear_odom = (double)(rear_position() / 100.0);
        robot_heading = (double)(imu.heading());
        left_dist = (radian * left_odom) * 2.75 / 2;
        rear_dist = (radian * rear_odom) * 2.75 / 2;
        heading_change = robot_heading - prev_heading;

        if (heading_change != 0)
        {
            int sign = (rear_offset.second > rear_offset.first) ? 1 : -1;
            x_radius = (rear_dist / heading_change) + rear_offset.second;
            // sign * sqrt(pow<2>(rear_offset.second) + pow<2>(rear_offset.first));
            sign = (left_offset.second > left_offset.first) ? 1 : -1;
            y_radius = (left_dist / heading_change) + left_offset.first;
            // sign * sqrt(pow<2>(left_offset.second) + pow<2>(left_offset.first));
            local_x = 2 * x_radius * sin(heading_change / 2);
            local_y = 2 * y_radius * sin(heading_change / 2);
        }
        else
        {
            local_x = rear_dist;
            local_y = left_dist;
        }

        local_true_heading = atan2(local_y, local_x);
        if (local_x == 0 && local_y == 0)
            local_true_heading = 0;
        global_true_heading = local_true_heading + (robot_heading + prev_heading) / 2;
        while (global_true_heading > 180)
            global_true_heading -= 360;
        while (global_true_heading < 180)
            global_true_heading += 360;

        total_dist = sqrt(pow(local_x, 2) + pow(local_y, 2));
        odom_x -= total_dist * cos(global_true_heading);
        odom_y += total_dist * sin(global_true_heading);

        set_left(0);
        set_rear(0);
        left_odom = 0;
        rear_odom = 0;
        prev_heading = robot_heading;

        wait(20, msec);
    }
}

void odom::calibrate(double heading)
{
    double x = gps_sensor.xPosition() * 39.37;
    double y = gps_sensor.yPosition() * 39.37;
    odom::calibrate(x, y, heading);
}

void odom::calibrate(double robot_x = 0, double robot_y = 0, double heading = 0)
{
    odom_x = robot_x;
    odom_y = robot_y;
    imu.setRotation(heading, degrees);

    while (heading < 0)
        heading += 360;
    while (heading > 360)
        heading -= 360;

    imu.setHeading(heading, degrees);

    while (imu.isCalibrating())
        wait(100, msec);
}

double odom::get_x() { return odom_x; }
double odom::get_y() { return odom_y; }
*/