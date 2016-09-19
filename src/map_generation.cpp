/**
 * 9/14/2016 - Currently a dummy file that allows compilation to test for syntax errors
 */
#include "map.h"
#include <iostream>

/**
 * TODO: Encapsulate this in map header/cpp file when have access to 
 *       stack exchange
 * Print out the map in ascii
 */
std::ostream &operator<<(std::ostream &os,Map const &mapObj){
	/**
	 * Print a row of -- at the top of the map
	 */
	for(int col = 0; col<mapObj.spaceMatrix[0].size(); ++col){
		os << "-";
	}
	os << std::endl;

	for(int i = 0; i<mapObj.spaceMatrix.size(); ++i){
		for(int j = 0; j<mapObj.spaceMatrix[i].size(); ++j){
			os << "*";
		}
		os << std::endl;
	}

	/**
	 * Print a row of -- at the bottom of the map
	 */
	for(int col = 0; col<mapObj.spaceMatrix[0].size(); ++col){
		os << "-";
	}
	return os;
}

int main(){
	int maxX = 10;
	int maxY = 10;
	Map myMap(maxX,maxY);

	std::cout << myMap <<std::endl;
	return 0;
}