#include <vector>

struct PathMemorizer {
public:
  PathMemorizer();

protected:
  /*
  * Pushes a node back into the graph data structure whenever in the exploration phase of the robot
  */
  void AddNode(double value);
private:
  std::pair<int, int> last_point;
  std::pair<int, int> curr_location;
  std::vector<int> graph[4];
}