#pragma once

class PIDController {
    private:
        double error, previous_error;
        double proportional, integral, derivative;
        double kP, kI, kD, dT;
        double target;
        void(*func)(double);
        double(*current)();

        double calculate(double current);

    public: 
        PIDController(double p_gain, double i_gain, double d_gain, double loop_time, void(*action_callback)(double), double(*position_callback)());
        void run();
        void set_target(double new_target);
};
