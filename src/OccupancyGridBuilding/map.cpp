/**
 * Implementation of the Map class
 */

#include "map.h"
Map::Map(int sizeX, int sizeY) : spaceMatrix(sizeX, std::vector<uint8_t>(sizeY)){
	
	//TODO: use a proper modern range for this init loop
	for(int i = 0; i<sizeX; ++i){
		for(int j = 0; j<sizeY; ++j){
			spaceMatrix[i][j] = 0;
			if(j == 3){
				spaceMatrix[i][j] = 1;
			}
		}
	}

}

Map::~Map(){
}


std::ostream& operator<<(std::ostream &os,Map const &mapObj){
/**
	 * Print a row of "-"" at the top of the map
	 */
	for(auto const& i : mapObj.spaceMatrix[0]){
		os << "-";
	}
	// Add an additional 2 "-" for the borders of the map
	os << "-" << "-" << std::endl;
	
	
	for(auto const& i : mapObj.spaceMatrix){
		//i is a reference to the spaceMatrix vector
		os << "|";
		for(auto const& j : i){
			//j is the value in the
			if(j == 0){
				os << " ";
			}else if (j==1){
				os << "*";
			}

			//! check if j is at the end of the current vector.
			if(&j == &i.back()){
				os << "|";
			}
		}
		os << std::endl;
	}
	
	
	/**
	 * Print a row of -- at the bottom of the map
	 */
	for(auto col : mapObj.spaceMatrix[0]){
		os << "-";
	}
	// Add an additional 2 "-" for the borders of the map
	os << "-" << "-" << std::endl;
	return os;
}
