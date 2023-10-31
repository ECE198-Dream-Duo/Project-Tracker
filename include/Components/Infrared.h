#include "Constants.h"

struct Infrared {
public:
/*
* Construct Transmitter, Reciever, and Setup Digital Potentiometer
*/

protected:
  void ChangeVoltage(double value);
  bool ObjectDetected(); // Checks infrared reciever info by sending a ray from the mitter
private:
  double VoltageInput = 1.0;
};

/*
* Two of them are stored on the left and right side of the robot
* If one detects an object we pass it into the eventloop for action
* Either we turn the robot using a gyro, or we stop at turn if we are at an injuction
*/