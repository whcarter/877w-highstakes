#include "main.h"

void auton()
{
    c_drive(-30, 4);
    wait(1000, msec);
    clamp.set(false);
    wait(1000, msec);
    c_drive(6, 8);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    wait(5000, msec);
    intake.stop();
}

void skills() {
    clamp.set(true);
    drive(-6);
    wait(1000, msec);
    turn(-90, 4);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    drive(50, 4);
    wait(10000, msec);
    intake.stop();
}