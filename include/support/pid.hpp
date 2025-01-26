#pragma once

class PIDController
{
private:
    double error, previous_error;
    double proportional, integral, derivative;
    double kP, kI, kD, dT;
    double target;
    bool is_running;
    void (*func)(double);
    double (*current)();
    double bound;
    std::list<double> past_error;
    double cum_error;
    double start_time = 0;
    double timeout;
    double i_start;
    double i_cap;
    bool cum_power;
    double previous_power = 0;

   /*
	* @brief Calculate power for next cycle
	* @param current Current position
	*/
    double calculate(double current);

public:

   /*
	* @brief Self-contained PID control system
	*
    * @param p_gain, i_gain, d_gain	Gain coefficients for proportional, integral, and derivative terms
    * @param loop_time 				Delay between cycles, in milliseconds
    * @param action_callback 		Action to be performed
    * @param position_callback 		Current position getter
    * @param error_bound 			Maxmimum cumulative error required to exit loop
    * @param max_time 				Maximum runtime before loop exit
    * @param integral_start 		Delay before integral accululation, in milliseconds
    * @param integral_cap 			Maximum allowed integral value
    * @param cumulative 			Whether or not power should add each cycle (used for velocity control)
	*/
    PIDController(double p_gain, double i_gain, double d_gain, double loop_time,
                  void (*action_callback)(double), double (*position_callback)(),
                  double error_bound = 1, double max_time = -1, 
                  double integral_start = -1, double integral_cap = -1,
                  bool cumulative = false);
	// Sets a new target value		  
    void set_target(double new_target);
	// Returns current error
    double get_error();
	// Returns whether or not the loop is settled
    bool running();
	// Begins loop
    void start();
	// Ends loop
    void stop();
	// Sets a new maximum error bound to exit loop
    void set_error_bound(double error_bound);
	// Sets a new maximum runtime
    void set_timeout(double max_time);
	// Calls action function with calculated power each cycle
    [[noreturn]] void run();
};
