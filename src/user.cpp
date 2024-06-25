#include "main.h"

// ========================= User Control Functions ========================= //

void arcade_drive(int left_x, int left_y, int right_x, int right_y) {
    int left = left_y + right_x;
    int right = left_y - right_x;
    drive_left.spin(forward, left, percent);
    drive_right.spin(forward, right, percent);
}

// ========================= Input Processor & Task ========================= //

void user() {
    int left_x = controller1.Axis4.position(percent);
    int left_y = controller1.Axis3.position(percent);
    int right_x = controller1.Axis1.position(percent);
    int right_y = controller1.Axis2.position(percent);
    arcade_drive(left_x, left_y, right_x, right_y);
}
