#pragma once

class PIDController
{
private:
    double error, previous_error;
    double proportional, integral, derivative;
    double kP, kI, kD, dT;
    double target;
    bool isRunning;
    void (*func)(double);
    double (*current)();

    double calculate(double current);
    [[noreturn]] void run();

public:
    PIDController(double p_gain, double i_gain, double d_gain, double loop_time, void (*action_callback)(double), double (*position_callback)());
    void set_target(double new_target);
    double get_error();
    void start();
    void stop();
};
