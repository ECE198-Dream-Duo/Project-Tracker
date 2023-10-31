/*
* The Following Enums describe Movement, Location, and Drawer Status that is maintained and changed by the Status Struct
*/
enum Movement {
  TravellingHome,
  TravellingDestination,
  Disabled
};

enum Location {
  AtHome,
  AtDestination,
  NA
};

enum Drawer {
  Open,
  Closed,
  Moving
};

/*
* A Struct holding Constantly checked values to identify next steps
* Only one instance should be held of this class, by the "Factory" Class
*/
struct Status {
public:
  /*
  * Constructors and Destructor
  */
  Status() = delete;
  ~Status() = delete;

  inline void ChangeMovementStatus(Movement Input) {MoveStatus = Input;}
  inline void ChangeLocationStatus(Location Input) {LocationStatus = Input;}
  inline void ChangeDrawerStatus(Drawer Input) {DrawerStatus = Input;}
private:
  static Movement MoveStatus;
  static Location LocationStatus;
  static Drawer DrawerStatus;
};