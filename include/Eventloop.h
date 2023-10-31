#include "Constants.h"

class EventLoop {
public:
  /*
  * Constructor and Destructor
  */
protected:
  /*
  * Everytime state is changed, a group of functions is run on a real-time operating system if it needs multiple iterations
  */
  void HeadHome();
  void HeadDestination(int DestValue);
  void Stop();
  void OpenDrawer();
  void CloseDrawer();
  void PlaySound();
  void ActiveScreen();
  void DisableScreen();
private:

};