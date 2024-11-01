#include "main.h"

PIDController::PIDController(double p_gain, double i_gain, double d_gain, double loop_time, void (*action_callback)(double), double (*position_callback)())
{
    kP = p_gain;
    kI = i_gain;
    kD = d_gain;
    dT = loop_time;
    func = action_callback;
    current = position_callback;
}

double PIDController::calculate(double current)
{
    error = target - current;
    proportional = error;
    integral = integral + error * dT;
    derivative = (error - previous_error) / dT;
    return (proportional * kP) + (integral * kI) + (derivative * kD);
}

void PIDController::set_target(double new_target)
{
    target = new_target;
}

double PIDController::get_error()
{
    return error;
}

void PIDController::start()
{
    isRunning = true;
}

void PIDController::stop()
{
    isRunning = false;
}

[[noreturn]] void PIDController::run()
{
    while (true)
    {
        while (isRunning)
        {
            double power = calculate(current());
            func(power);
            wait(dT, msec);
        }
        wait(100, msec);
    }
}
