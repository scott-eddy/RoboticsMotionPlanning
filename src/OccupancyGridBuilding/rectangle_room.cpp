/**
 * @brief A room that is rectangular in shape
 * @details A class that fills the space matrix of its parent map
 *          with 4 walls and randomly generated clutter
 * 
 * @author Eddy Scott
 */

#include "rectangle_room.h"
#include <random> //Needed to add clutter to a room
RectangleRoom::RectangleRoom(int xFreeSpace, int yFreeSpace,const mapTools::Point& origin, const Map& parentMap):
Room(parentMap)
{
	this->xFreeSpace = xFreeSpace;
	this->yFreeSpace = yFreeSpace;
	this->origin = origin;

	upperLeft.x = (origin.x - std::floor(xFreeSpace/2)) - 1;
	upperLeft.y = (origin.y - std::floor(yFreeSpace/2)) - 1;

	lowerRight.x = (origin.x + std::floor(xFreeSpace/2)) - 1;
	lowerRight.y = (origin.y + std::floor(yFreeSpace/2)) - 1;

	populateMap();
}

RectangleRoom::~RectangleRoom()
{
}

void RectangleRoom::populateMap()
{
	//Generate the remaining points to define the entire border of the map
	mapTools::Point upperRight;
	upperRight.x = (origin.x + std::floor(xFreeSpace/2)) - 1;
	upperRight.y = (origin.y - std::floor(yFreeSpace/2)) - 1;

	mapTools::Point lowerLeft;
	lowerLeft.x = (origin.x - std::floor(xFreeSpace/2)) - 1;
	lowerLeft.y = (origin.y + std::floor(yFreeSpace/2)) - 1;
	

	std::vector<Line> roomBorder;

	Line topLine(std::vector<mapTools::Point>({upperLeft,upperRight}));
	Line bottomLine(std::vector<mapTools::Point>({lowerLeft,lowerRight}));
	Line leftLine(std::vector<mapTools::Point>({upperLeft,lowerLeft}));
	Line rightLine(std::vector<mapTools::Point>({upperRight,lowerRight}));

	roomBorder.push_back(topLine);
	roomBorder.push_back(bottomLine);
	roomBorder.push_back(leftLine);
	roomBorder.push_back(rightLine);

	for(auto const &currentLine : roomBorder){
		parentMap.fillSpace(currentLine.getPointsOnLine());
	}
}

mapTools::Rect RectangleRoom::getBoundingBox()
{
	mapTools::Rect boundingBox;
	boundingBox.topLeft.x = origin.x - std::floor(xFreeSpace/2);
	boundingBox.topLeft.y = origin.y - std::floor(yFreeSpace/2);

	boundingBox.bottomRight.x = origin.x + std::floor(xFreeSpace/2);
	boundingBox.bottomRight.y = origin.y + std::floor(yFreeSpace/2);

	return boundingBox;
}

void RectangleRoom::addClutter(){
	std::random_device rd; 
	std::mt19937_64 randomNumGenerator(rd());

	int mean = 0;
	int stdDev = 1;
	std::normal_distribution<> dis(mean, stdDev);
	auto twoSigma = mean - (2*stdDev);

	std::vector<mapTools::Point> points_to_fill;
	
	for(int i = upperLeft.x; i <= lowerRight.x; i++){
		for(int j = upperLeft.y; j <= lowerRight.y; j++){
			auto random_number = dis(randomNumGenerator);
			//std::cout << "Random Number: " << random_number << std::endl;
			
			if(random_number < (mean-stdDev)){
				mapTools::Point filledSpace;
				filledSpace.x = i;
				filledSpace.y = j;
				points_to_fill.push_back(filledSpace);
			}

		}
	}

	parentMap.fillSpace(points_to_fill);


}

void RectangleRoom::fill(mapTools::SPACE_TYPE typeToFill){
    std::vector<mapTools::Point> points_to_fill;
	for(int i = upperLeft.x; i <= lowerRight.x; i++){
    	for(int j = upperLeft.y; j <= lowerRight.y; j++){
			mapTools::Point filledSpace;
			filledSpace.x = i;
			filledSpace.y = j;
			points_to_fill.push_back(filledSpace);
		}

	}	
    
    switch(typeToFill){
        case(mapTools::SPACE_TYPE::OCCUPIED):{
           parentMap.fillSpace(points_to_fill);
           break;
       }
       case(mapTools::SPACE_TYPE::EMPTY):{
            parentMap.emptySpace(points_to_fill);
            break;
       }

    }
}

