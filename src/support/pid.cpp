#include "main.h"

PIDController::PIDController(double p_gain, double i_gain, double d_gain, double loop_time,
                             void (*action_callback)(double), double (*position_callback)(),
                             double error_bound, double max_time,
                             double integral_start, double integral_cap,
                             bool cumulative)
{
    kP = p_gain;
    kI = i_gain;
    kD = d_gain;
    dT = loop_time;
    func = action_callback;
    current = position_callback;
    bound = error_bound;
    timeout = max_time;
    i_start = integral_start;
    i_cap = integral_cap;
    cum_power = cumulative;
}

// Determines power for next cycle
double PIDController::calculate(double position)
{
    error = target - position;
    proportional = error;
    if (millis() - start_time > i_start)
        integral = integral + error * dT;
    if (fabs(integral) > i_cap && i_cap > 0)
        integral = (integral > 0) ? i_cap : -i_cap;

    derivative = (error - previous_error) / dT;
    return (proportional * kP) + (integral * kI) + (derivative * kD);
}

// Sets a new target value
void PIDController::set_target(double new_target)
{
    target = new_target;
    start_time = millis();
}

// Returns current error
double PIDController::get_error()
{
    return error;
}

// Returns whether or not the loop is settled
bool PIDController::running()
{
    return isRunning;
}

// Begins loop
void PIDController::start()
{
    isRunning = true;
    start_time = millis();
}

// Ends loop
void PIDController::stop()
{
    func(0);
    isRunning = false;
}

// Sets a new maximum error bound to exit loop
void PIDController::set_error_bound(double error_bound)
{
    bound = error_bound;
}

// Sets a new maximum runtime
void PIDController::set_timeout(double max_time)
{
    timeout = max_time;
}

// Calls action function with calculated power each cycle
[[noreturn]] void PIDController::run()
{
    while (true)
    {
        while (isRunning)
        {
            double position = current();
            double power = calculate(position);
            if (cum_power)
            {
                power += previous_power;
                previous_power = power;
            }
            func(power);
            past_error.push_front(error);
            if (past_error.size() > 5)
            {
                past_error.pop_back();
            }
            cum_error = 0;
            for (double e : past_error)
            {
                cum_error += fabs(e);
            }
            if (cum_error < bound)
            {
                if (!cum_power)
                {
                    stop();
                }
                isRunning = false;
                std::cout << "Settle time: " << millis() - start_time << std::endl;
            }
            if (timeout > 0 && (millis() - start_time) > timeout)
            {
                stop();
            }
            wait(dT, msec);
        }
        wait(100, msec);
    }
}
