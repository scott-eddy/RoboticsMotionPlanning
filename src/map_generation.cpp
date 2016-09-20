/**
 * 9/14/2016 - Currently a dummy file that allows compilation to test for syntax errors
 */
#include "map.h"
#include <iostream>
int main(){
	int maxX = 30;
	int maxY = 30;
	Map myMap(maxX,maxY);
	std::cout << myMap <<std::endl;
	return 0;
}