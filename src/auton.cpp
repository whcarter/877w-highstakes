#include "main.h"

void auton()
{
    c_drive(-30, 4);
    wait(1000, msec);
    clamp.set(true);
    wait(1000, msec);
    c_drive(6, 8);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    wait(5000, msec);
    intake.stop();
}