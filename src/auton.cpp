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

void just_move()
{
    clamp.set(false);
    c_drive(-6, 4);
}

void right_auton()
{
    clamp.set(false);
    c_drive(-30, 4);
    wait(1000, msec);
    clamp.set(true);
    wait(1000, msec);
    c_drive(6, 8);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    turn_relative(-30);
    drive_relative(24);
    drive_relative(-48);
    wait(1000, msec);
    intake.stop();
}

void skills()
{
    clamp.set(true);
    c_drive(-6, 4);
    wait(1000, msec);
    c_turn(-90, 4);
    wait(1000, msec);
    intake.spin(forward, 12, volt);
    c_drive(50, 4);
    wait(10000, msec);
    intake.stop();
}

void masuk_skills()
{
    clamp.set(true);
    c_drive(-8, 4);
    intake.spin(forward, 12, volt);
    wait(1000, msec);
    c_turn(-140, 5);
    wait(1000, msec);
    c_drive(36, 4);
    wait(5000, msec);
    intake.stop();
    wait(1000, msec);
    c_turn(-135, 7);
    // c_drive(-24, 4);
    clamp.set(false);
    c_drive(12, 4);
}

void test_routine()
{
    // Right 90, 90, 180, Left 90, 270, 360
    std::cout << "------------------------------" << std::endl;
    /*
    turn_relative(90);
    wait(3000, msec);
    turn_relative(90);
    wait(3000, msec);
    turn_relative(180);
    wait(3000, msec);
    turn_relative(-90);
    wait(3000, msec);
    turn_relative(-270);
    wait(3000, msec);
    turn_relative(-360);
    */

    // Forward 24, Back 12, 12, Forward 48
    drive_relative(24);
    wait(3000, msec);
    drive_relative(-12);
    wait(3000, msec);
    drive_relative(-12);
    wait(3000, msec);
    drive_relative(48);

    std::cout << "------------------------------" << std::endl;
}