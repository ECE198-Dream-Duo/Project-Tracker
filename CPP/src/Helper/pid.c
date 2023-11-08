#include "Helper/pid.h"

double headingControl(double error, double totalError) {

    // constants for PID, set to 1 initially, will definitely need to change
    // when calibrating
    double kP = 1.0;
    double kI = 1.0;
    double kD = 1.0;

    double currentError = heading();
    // arbitrary maxIntegral value, will calibrate later, but this is so that error from
    // too far into the past doesn't get factored in to PID 
    int maxIntegral = 300;

    // this caps the maximum integral at any given time, this is so that if any sudden huge change occurs
    // it won't throw the integral portion out of pounds that the potential and derivative portions should
    // auto-correct, the integral is to smooth out small errors.
    int integralBound = 3;

    // heading will be a positive/negative angle, the 0 is the desired heading
    // as it represents going "straight"
    double potential = 0 - currentError;
    double derivative = currentError - error;
    if (abs(currentError) < abs(integralBound)) {
        totalError = totalError + currentError;
    }
    else {
        integralBound = 0;
    }
    error = kP*potential + kD*derivative + kI*totalError;
    return error;
}

int heading() {
    // gets heading of robot using the gyro and IIC
    int heading;
    return heading;
}

double velocity(double acceleration) {
    // still need to figure out the math needed to calculate the velocity of the robot given that the 
    // initial velocity is zero, the acceleration, and maybe also the voltage supply to the motors?
    double velocity; 
    return velocity;
}

double turn(double degree, double error, double totalError) {
    // essentially the same as heading control, but for turns for given degree
    // will need to be calibrated seperatly to headingControl
    // assume linear velocity of the robot is 0 during turn
    // i.e. it will only turn but not move and turn at the same time

    // constants for PID, set to 1 initially, will definitely need to change
    // when calibrating
    double kP = 1.0;
    double kI = 1.0;
    double kD = 1.0;

    double currentError = heading();
    // arbitrary maxIntegral value, will calibrate later, but this is so that error from
    // too far into the past doesn't get factored in to PID 
    int maxIntegral = 300;

    // this caps the maximum integral at any given time, this is so that if any sudden huge change occurs
    // it won't throw the integral portion out of pounds that the potential and derivative portions should
    // auto-correct, the integral is to smooth out small errors.
    int integralBound = 3;

    // heading will be a positive/negative angle, the 0 is the desired heading
    // as it represents going "straight"
    double potential = degree - currentError;
    double derivative = currentError - error;
    if (abs(currentError) < abs(integralBound)) {
        totalError = totalError + currentError;
    }
    else {
        integralBound = 0;
    }
    error = kP*potential + kD*derivative + kI*totalError;
    return error;
}