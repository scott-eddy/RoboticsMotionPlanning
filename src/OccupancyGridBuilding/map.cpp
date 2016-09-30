/**
 * Implementation of the Map class
 */
#include "map.h"

Map::Map() : spaceMatrix(30, std::vector<uint8_t>(30)){
	this->sizeX = 30; //Default map size
	this->sizeY = 30; //Default map size
}

Map::Map(int sizeX, int sizeY) : spaceMatrix(sizeX, std::vector<uint8_t>(sizeY)){
	this->sizeX = sizeX;
	this->sizeY = sizeY;
}

Map::~Map(){
}

void Map::addRoom(std::tuple<int,int> freeSpace, mapTools::Point origin){
	std::unique_ptr<RectangleRoom> pRect(new RectangleRoom(std::get<0>(freeSpace),std::get<1>(freeSpace),origin,*this));
	roomVector.push_back(std::move(pRect));
}

void Map::fillSpace(std::vector<mapTools::Point> pointsToFill) const{
	for(auto const& currentPoint : pointsToFill){
		spaceMatrix[currentPoint.x][currentPoint.y] = 1;
	}
}

void Map::printMatrix(){
for(auto const& rowVect : spaceMatrix){
		//rowVect is a reference to the spaceMatrix vector
		for(auto const& matrixValue : rowVect){
			std::cout << static_cast<int>(matrixValue) << ",";
		}
		std::cout << std::endl;
	}
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
