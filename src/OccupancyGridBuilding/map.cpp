/**
 * Implementation of the Map class
 */

#include "map.h"
Map::Map(int sizeX, int sizeY) : spaceMatrix(sizeX, std::vector<uint8_t>(sizeY)){
	
	/*
	for(auto it = spaceMatrix.begin(); it != spaceMatrix.end(); ++it){
		spaceMatrix[it] = 0;
	}
	*/
	//TODO: use a proper modern range for this init loop
	for(int i = 0; i<sizeX; ++i){
		for(int j = 0; j<sizeY; ++j){
			spaceMatrix[i][j] = 0;
		}
	}

	debug_value = 42;

}

Map::~Map(){
}

/**
 * Note: need to inline the function as this function needs 
 * mapObj wich is defined in this .cpp file
 */
inline std::ostream& operator<<(std::ostream &os,Map const &mapObj){
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