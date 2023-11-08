// function definitions for any and all functions required for PID drive system to work

// takes current heading from gyroscope then course corrects voltage on motors.
void headingControl(int* heading);

// read input from gyroscope and return a pointer to a gloabl heading variable that stores the current heading
int* currentHeading();

// calculate current velocity based of accelerometer
int currentVelocity(int acceleration);

// turn left or right, 0 for left, 1 for right
void turn(int direciton, int* heading);