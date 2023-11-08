// function definitions for any and all functions required for PID drive system to work

// takes current heading from gyroscope then course corrects voltage on motors.
// course corrects everytime its called
double headingControl(double error, double totalError);

int currentHeading();

// calculate current velocity based of accelerometer
double currentVelocity(double acceleration);

// turn left or right
double turn(double degree, double error, double totalError);