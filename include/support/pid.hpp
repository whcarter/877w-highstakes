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
    double bound;
    std::list<double> past_error;
    double cum_error;
    double start_time = 0;
    double timeout;
    double i_start;

    double calculate(double current);

public:
    PIDController(double p_gain, double i_gain, double d_gain, double loop_time,
                  void (*action_callback)(double), double (*position_callback)(),
                  double error_bound = 1, double max_time = -1, 
                  double integral_start = -1);
    void set_target(double new_target);
    double get_error();
    void start();
    void stop();
    [[noreturn]] void run();
};
