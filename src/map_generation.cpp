/**
 * 9/14/2016 - Currently a dummy file that allows compilation to test for syntax errors
 */
#include "map.h"
#include "rectangle_room.h"
#include <iostream>
int main() {
  int maxX = 100;
  int maxY = 30;
  Map myMap(maxX, maxY);
  myMap.GenerateMap();
  /*
  map_tools::geometry::Point2D roomOrigin;
  roomOrigin.x = 15;
  roomOrigin.y = 15;
  std::tuple<int,int> roomFreeSpace(10,10);
  myMap.addRoom(roomFreeSpace,roomOrigin);

  roomOrigin.x = roomOrigin.x+30;
  roomOrigin.y = roomOrigin.y;
  roomFreeSpace = std::tuple<int,int>(20,7);
  myMap.AddRoom(roomFreeSpace,roomOrigin);

  myMap.AddClutterToRoom(1);
  */
  std::cout << myMap << std::endl;

  return 0;
}
