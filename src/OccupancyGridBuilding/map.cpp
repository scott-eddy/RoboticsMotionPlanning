/**
 * Implementation of the Map class
 */
#include "map.h"
#include <random>
Map::Map() : spaceMatrix(30, std::vector<uint8_t>(30)){
	this->sizeX = 30; //Default map size
	this->sizeY = 30; //Default map size
	//Rooms should take up less than twenty percent of the maze
	this->maxRoomX = (0.2*this->sizeX); 
	this->maxRoomY = (0.2*this->sizeY);
}

Map::Map(int sizeX, int sizeY) : spaceMatrix(sizeY, std::vector<uint8_t>(sizeX)){
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->maxRoomX = (0.2*this->sizeX); 
	this->maxRoomY = (0.2*this->sizeY);
}

Map::~Map(){
}

void Map::generate(){

    const int smallestRoomFreeSpace = 4; // Want rooms to be at least 2 tiles deep
	int numberOfAttempts = 0;
	const int maxAttempts = 50; 
	std::random_device rd; 
	std::mt19937_64 randomNumGenerator(rd());
	std::uniform_int_distribution<> roomUniformX(smallestRoomFreeSpace,this->maxRoomX);
	std::uniform_int_distribution<> roomUniformY(smallestRoomFreeSpace,this->maxRoomY);	
	std::uniform_int_distribution<> mapUniformX(1,this->sizeX);
	std::uniform_int_distribution<> mapUniformY(1,this->sizeY);
	std::tuple<int,int> curRoomFreeSpace;
	mapTools::Point curRoomOrigin;
   
	//while(numberOfAttempts <= maxAttempts){
	//	int xFreeSpace = roomUniformX(randomNumGenerator);
	//	int yFreeSpace = roomUniformY(randomNumGenerator);
	//	curRoomFreeSpace = std::tuple<int,int>(xFreeSpace,yFreeSpace);
	//
	//	curRoomOrigin.x = mapUniformX(randomNumGenerator);
	//	curRoomOrigin.y = mapUniformY(randomNumGenerator);
    //    
	//	if(this->addRoom(curRoomFreeSpace,curRoomOrigin)){
    //        roomVector.back()->fill(mapTools::SPACE_TYPE::OCCUPIED);
    //    }	
    //    numberOfAttempts++;
    //}
    
    this->makeMaze();

}

void Map::makeMaze(){
    //for(int x = 0; x < this->sizeX; x++){
    //    for(int y = 0; y < this->sizeY; y++){
    //        if(this->spaceMatrix[y][x] != mapTools::SPACE_TYPE::OCCUPIED){
    //            this->growTree(x,y);
    //        }
    //    }
    //} 
    this->growTree(0,0);
}


void Map::growTree(int x, int y){
    mapTools::Point startLocation(x,y);
    std::vector<mapTools::Point> trackedSpace;
    trackedSpace.push_back(startLocation);
    std::vector<mapTools::DIRECTION> directionsCanTravel;
    mapTools::DIRECTION lastDirTrav = mapTools::DIRECTION::NORTH;
    const int growLength = 2;
    //Quick Check to see if we should fill the space we are at
    this->findAdjacentSpace(growLength,trackedSpace.back(),mapTools::SPACE_TYPE::EMPTY,directionsCanTravel);
    if(directionsCanTravel.size() != 0)
        this->fillSpace(trackedSpace.back());
    
    while(trackedSpace.size() != 0){ 
        //See which direction we can propigate this maze
        directionsCanTravel.clear();
        this->findAdjacentSpace(growLength,trackedSpace.back(),mapTools::SPACE_TYPE::EMPTY,directionsCanTravel);

        if(directionsCanTravel.size() != 0){
            //Prefer to travel in the same direction as before
            if(std::find(directionsCanTravel.begin(), directionsCanTravel.end(), lastDirTrav) != directionsCanTravel.end()) {
                //We can again travel in the same direction
                //Fill the adjacent space and then move the appropriate lengh
                this->fillAdjacentSpace(trackedSpace.back(),lastDirTrav);
                trackedSpace.push_back(this->moveConsecutiveSpace(growLength,trackedSpace.back(),lastDirTrav));
                this->fillSpace(trackedSpace.back());
            } else {
                this->fillAdjacentSpace(trackedSpace.back(),directionsCanTravel.front());
                trackedSpace.push_back(this->moveConsecutiveSpace(growLength,trackedSpace.back(),directionsCanTravel.front()));
                lastDirTrav = directionsCanTravel.front();
                this->fillSpace(trackedSpace.back());
            }
        }else{
            trackedSpace.pop_back();
            //TODO reset last direction traveled?
        }

    }
}

void Map::findAdjacentSpace(const int numberOfTiles, const mapTools::Point &root, const mapTools::SPACE_TYPE &spaceType,std::vector<mapTools::DIRECTION> &directionToSpaceType){
   //TODO is clearing the vector here correct?
    if(numberOfTiles > 0){
        directionToSpaceType.clear(); 
        this->findAdjacentSpace(root, spaceType, directionToSpaceType);
        
        if(!directionToSpaceType.empty() && numberOfTiles > 1){
            std::vector<mapTools::DIRECTION> rootDirections = directionToSpaceType;
            directionToSpaceType.clear(); //Clear out vector again as we only can gaurantee one tile of motion here
            for(const auto &dir : rootDirections){
                std::vector<mapTools::DIRECTION> tempDirections;
                bool numberTilesValid = true;
                mapTools::Point nextTile = this->moveToAdjacentSpace(root,dir);
                for(int i = 2; i <= numberOfTiles; i++){
                    this->findAdjacentSpace(nextTile, spaceType, tempDirections);
                    if(std::find(tempDirections.begin(), tempDirections.end(), dir) != tempDirections.end()) {
                        //We can move in this direction, continue search
                        tempDirections.clear();
                        nextTile = this->moveToAdjacentSpace(nextTile,dir);
                    }else{
                        numberTilesValid = false;
                        break;
                    }
                }
                if(numberTilesValid){
                    directionToSpaceType.push_back(dir);
                }
            }
        }
    }
}

void Map::findAdjacentSpace(const mapTools::Point &root, const mapTools::SPACE_TYPE &spaceType, std::vector<mapTools::DIRECTION> &dirToSpaceType){
    
    for(int dir = mapTools::DIRECTION::NORTH; dir < mapTools::DIRECTION::LAST; dir++){
        switch(dir){
            case mapTools::DIRECTION::NORTH:
                //Qury the state of the space matrix in the row above this one, if it is in bounds
                if(root.x >= 0 && root.x < this->sizeX){
                    if(root.y-1 >=0 && root.y-1 < this->sizeY){
                        if(this->spaceMatrix[root.y-1][root.x] == spaceType){
                            dirToSpaceType.push_back(mapTools::DIRECTION::NORTH);
                        }
                    }
                }
                break;
            
            case mapTools::DIRECTION::EAST:
                //Qury the state of the space matrix in the row above this one, if it is in bounds
                if(root.x+1 >= 0 && root.x+1 < this->sizeX){
                    if(root.y >=0 && root.y < this->sizeY){
                        if(this->spaceMatrix[root.y][root.x+1] == spaceType){
                            dirToSpaceType.push_back(mapTools::DIRECTION::EAST);
                        }
                    }
                }
                break;
            
            case mapTools::DIRECTION::SOUTH:
                //Qury the state of the space matrix in the row above this one, if it is in bounds
                if(root.x >= 0 && root.x < this->sizeX){
                    if(root.y+1 >=0 && root.y+1 < this->sizeY){
                        if(this->spaceMatrix[root.y+1][root.x] == spaceType){
                            dirToSpaceType.push_back(mapTools::DIRECTION::SOUTH);
                        }
                    }
                }
                break;

            case mapTools::DIRECTION::WEST:
                //Qury the state of the space matrix in the row above this one, if it is in bounds
                if(root.x-1 >= 0 && root.x-1 < this->sizeX){
                    if(root.y >=0 && root.y < this->sizeY){
                        if(this->spaceMatrix[root.y][root.x-1] == spaceType){
                            dirToSpaceType.push_back(mapTools::DIRECTION::WEST);
                        }
                    }
                }
                break;
        }//switch
         
    }//direction loop
}

mapTools::Point Map::fillAdjacentSpace(const mapTools::Point &root, const mapTools::DIRECTION &dirToFill){    
    mapTools::Point toFill = this->moveToAdjacentSpace(root,dirToFill);
    this->fillSpace(toFill);
    return toFill;
}
    
mapTools::Point Map::moveConsecutiveSpace(const int numSpace,const mapTools::Point &root, const mapTools::DIRECTION &directionToMove){
    mapTools::Point returnPoint = root;
    if(numSpace > 0){
        for(int i = 0; i < numSpace; i++){
            returnPoint = moveToAdjacentSpace(returnPoint, directionToMove);
        }
    }
    return returnPoint;
}

mapTools::Point Map::moveToAdjacentSpace(const mapTools::Point &root, const mapTools::DIRECTION &dirToFill){    
    mapTools::Point toMove;
    switch(dirToFill){
        case mapTools::DIRECTION::NORTH:
                //Qury the state of the space matrix in the row above this one, if it is in bounds
            if(root.x >= 0 && root.x < this->sizeX){
                if(root.y-1 >=0 && root.y-1 < this->sizeY){
                    toMove.x = root.x;
                    toMove.y = root.y-1;
                }
            }
            break;
            
        case mapTools::DIRECTION::EAST:
            //Qury the state of the space matrix in the row above this one, if it is in bounds
            if(root.x+1 >= 0 && root.x+1 < this->sizeX){
                if(root.y >=0 && root.y < this->sizeY){
                    toMove.x = root.x+1;
                    toMove.y = root.y;
                }
            }
            break;
            
        case mapTools::DIRECTION::SOUTH:
            //Qury the state of the space matrix in the row above this one, if it is in bounds
            if(root.x >= 0 && root.x < this->sizeX){
                if(root.y+1 >=0 && root.y+1 < this->sizeY){
                    toMove.x = root.x;
                    toMove.y = root.y+1;
                }
            }
            break;

        case mapTools::DIRECTION::WEST:
            //Qury the state of the space matrix in the row above this one, if it is in bounds
            if(root.x-1 >= 0 && root.x-1 < this->sizeX){
                if(root.y >=0 && root.y < this->sizeY){
                    toMove.x = root.x-1;
                    toMove.y = root.y;
                }
            }
            break;
    }//switch
    return toMove;
}

bool Map::addRoom(std::tuple<int,int> freeSpace, mapTools::Point origin){
	mapTools::Rect boundingBox;
	boundingBox.topLeft.x = origin.x - std::floor(std::get<0>(freeSpace)/2);
	boundingBox.topLeft.y = origin.y - std::floor(std::get<1>(freeSpace)/2);

	boundingBox.bottomRight.x = origin.x + std::floor(std::get<0>(freeSpace)/2);
	boundingBox.bottomRight.y = origin.y + std::floor(std::get<1>(freeSpace)/2);
	
	if(!roomIntersection(boundingBox)){
		std::unique_ptr<RectangleRoom> pRect(new RectangleRoom(std::get<0>(freeSpace),std::get<1>(freeSpace),origin,*this));
		roomVector.push_back(std::move(pRect));
        return true;
    }else{
        return false;
		//std::cout << "ROOM OVERLAP" << std::endl;
	}
}

void Map::addClutterToRoom(int roomNum){
	if(roomNum >= 0 && roomNum < roomVector.size()){
		roomVector[roomNum]->addClutter();
	}

}

bool Map::roomIntersection(const mapTools::Rect &potentialRoom){
	bool anyIntersection = false;

	for(auto const& roomInVector : roomVector){
		bool leftOfCurrentRoom = (roomInVector->getBoundingBox().bottomRight.x < potentialRoom.topLeft.x);
		bool rightOfCurrentRoom = (roomInVector->getBoundingBox().topLeft.x > potentialRoom.bottomRight.x);
		bool aboveCurrentRoom = (roomInVector->getBoundingBox().bottomRight.y  < potentialRoom.topLeft.y);
		bool belowCurrentRoom = (roomInVector->getBoundingBox().topLeft.y > potentialRoom.bottomRight.y);

		// std::cout << "Vector to left of current room: " << leftOfCurrentRoom << std::endl;
		// std::cout << "Vector to right of current room: " << rightOfCurrentRoom << std::endl;
		// std::cout << "Vector above current room: " << aboveCurrentRoom << std::endl;
		// std::cout << "Vector below current room: " << belowCurrentRoom << std::endl;

		if (leftOfCurrentRoom || rightOfCurrentRoom || aboveCurrentRoom || belowCurrentRoom){
    		anyIntersection = false; // room in vector is below current room
    	}else{
    		return true; // boxes overlap
    	}
	}
	return anyIntersection;
}

void Map::fillSpace(std::vector<mapTools::Point> pointsToFill) const{
    //Fill the space matrix with the x,y points in pointsToFill, with
    //bounds checking
	for(auto &currentPoint : pointsToFill){
        if(currentPoint.y < 0){
            currentPoint.y = 0;
        }
        if(currentPoint.x < 0){
            currentPoint.x = 0;
        }
        if(currentPoint.y >= sizeY){
            currentPoint.y = sizeY-1; //offset by 1 for 0 index notation
        }
        if(currentPoint.x >= sizeX){
            currentPoint.x = sizeX-1; //offset by 1 for 0 index notation
        }
        
        //std::cout << "Filling X,Y :" << currentPoint.x << "," << currentPoint.y << std::endl;
        //std::cout << "Max X,Y     :" << sizeX << "," << sizeY << std::endl;

		//N.B. y represents the row you are in and x represents the column
	    spaceMatrix[currentPoint.y][currentPoint.x] = mapTools::SPACE_TYPE::OCCUPIED;
        
    }
}

void Map::fillSpace(mapTools::Point pointToFill) const{  
    if(pointToFill.y < 0){
        pointToFill.y = 0;
    }
    if(pointToFill.x < 0){
        pointToFill.x = 0;
    }
    if(pointToFill.y >= sizeY){
        pointToFill.y = sizeY-1; //offset by 1 for 0 index notation
    }
    if(pointToFill.x >= sizeX){
        pointToFill.x = sizeX-1; //offset by 1 for 0 index notation
    }
      
    //std::cout << "Filling X,Y :" << currentPoint.x << "," << currentPoint.y << std::endl;
    //std::cout << "Max X,Y     :" << sizeX << "," << sizeY << std::endl;
	//N.B. y represents the row you are in and x represents the column
    spaceMatrix[pointToFill.y][pointToFill.x] = mapTools::SPACE_TYPE::OCCUPIED;
}

void Map::emptySpace(std::vector<mapTools::Point> pointsToFill) const{
    //Fill the space matrix with the x,y points in pointsToFill, with
    //bounds checking
	for(auto &currentPoint : pointsToFill){
        if(currentPoint.y < 0){
            currentPoint.y = 0;
        }
        if(currentPoint.x < 0){
            currentPoint.x = 0;
        }
        if(currentPoint.y >= sizeY){
            currentPoint.y = sizeY-1; //offset by 1 for 0 index notation
        }
        if(currentPoint.x >= sizeX){
            currentPoint.x = sizeX-1; //offset by 1 for 0 index notation
        }
        
        //std::cout << "Filling X,Y :" << currentPoint.x << "," << currentPoint.y << std::endl;
        //std::cout << "Max X,Y     :" << sizeX << "," << sizeY << std::endl;

		//N.B. y represents the row you are in and x represents the column
	    spaceMatrix[currentPoint.y][currentPoint.x] = mapTools::SPACE_TYPE::EMPTY; 
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
