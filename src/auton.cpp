#include "main.h"

void auton()
{
    clamp.set(false);
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

void masuk_auton_left() {
    clamp.set(true);
    driveRelative(-36);
    /*clamp.set(false);
    turnRelative(60);
    intake.spin(forward, 12, volt);
    driveRelative(30);
    wait(5000, msec);
    intake.stop();*/
}

void skills()
{
    clamp.set(true);
    c_drive(-6, 4);
    wait(1000, msec);
    turn(-90, 4);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    c_drive(50, 4);
    wait(10000, msec);
    intake.stop();
}

void masuk_skills() {
    clamp.set(true);
    c_drive(-8, 4);
    intake.spin(forward, 12, volt);
    wait(1000, msec);
    c_turn(-120, 4);
    wait(1000, msec);
    c_drive(36, 3);
    wait(5000, msec);
    intake.stop();
    wait(1000, msec);
    c_turn(-135, 4);
    //c_drive(-24, 4);
    clamp.set(false);
    c_drive(12, 4);
}