/**
 * 9/14/2016 - Currently a dummy file that allows compilation to test for syntax errors
 */
#include "map.h"
#include "rectangle_room.h"
#include <iostream>
int main(){
	int maxX = 5;
	int maxY = 5;
	Map myMap(maxX,maxY);
	myMap.generate();
	/*
	mapTools::Point roomOrigin;
	roomOrigin.x = 15;
	roomOrigin.y = 15;
	std::tuple<int,int> roomFreeSpace(10,10);
	myMap.addRoom(roomFreeSpace,roomOrigin);

	roomOrigin.x = roomOrigin.x+30;
	roomOrigin.y = roomOrigin.y;
	roomFreeSpace = std::tuple<int,int>(20,7);
	myMap.addRoom(roomFreeSpace,roomOrigin);

	myMap.addClutterToRoom(1);
	*/
	std::cout << myMap <<std::endl;

	return 0;
}
