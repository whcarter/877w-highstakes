/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       877W High Stakes                                          */
/*    Author:       Will Carter                                               */
/*    Created:      6/24/2024, 3:56:37 PM                                     */
/*    Description:  Full competition code for Ridgefield High School's team   */
/*                  877W in the 2024-2025 Vex Robotics Competition.           */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "main.h"

using namespace vex;

competition Competition;

void pre_auton(void)
{
  imu.calibrate();
  drive_left.resetPosition();
  drive_right.resetPosition();
  while (imu.isCalibrating())
  {
    wait(10, msec);
  }

  thread tracking = thread(track_position);
  thread turn_control = thread(start_turn_task);
  thread drive_control = thread(start_drive_task);
}

void autonomous(void)
{
  auton();
  // just_move();
  //masuk_skills();
}

void usercontrol(void)
{
  while (1)
  {
    user();
    wait(20, msec);
  }
}

int main()
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();

  while (true)
    wait(100, msec);
}
