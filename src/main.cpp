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
}

void autonomous(void)
{
  auton();
}

void usercontrol(void)
{
  while (1)
  {
    user();
    wait(10, msec);
  }
}

int main()
{
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true)
  {
    wait(100, msec);
  }
}
