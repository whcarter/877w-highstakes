#pragma once
#include "main.h"

double getHeading();
double getDistance();

namespace odom
{

    /**
     * @brief Initialize odometry
     */
    void initialize();

    /**
     * @brief Position tracking function
     */
    [[noreturn]] void track_position();

    /**
     * @brief Calibrate odometry
     *
     * @param robot_x Start position x
     * @param robot_y Start position y
     * @param heading Starting heading
     */
    void calibrate(double robot_x, double robot_y, double heading);

    /**
     * @brief Calibrate with GPS
     *
     * @param heading Starting heading
     */
    void calibrate(double heading);

    /**
     * @brief Get the current x value
     *
     * @return double
     */
    double get_x();

    /**
     * @brief Get the current y value
     *
     * @return double
     */
    double get_y();

}; // namespace odom