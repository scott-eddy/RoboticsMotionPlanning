/**
 * 9/14/2016 - Currently a dummy file that allows compilation to test for syntax errors
 */
#include "map.h"
#include "rectangle_room.h"
#include <iostream>
int main(){
	int maxX = 30;
	int maxY = 30;
	Map myMap;
	mapTools::Point roomOrigin;
	roomOrigin.x = 15;
	roomOrigin.y = 15;
	std::tuple<int,int> roomFreeSpace(10,10);

	myMap.addRoom(roomFreeSpace,roomOrigin);
	std::cout << myMap <<std::endl;
	return 0;
}