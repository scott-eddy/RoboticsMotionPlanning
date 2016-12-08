//TODO this could be a generally useful class

#pragma once
#include <vector>
#include "map_tools_common.h"
#include <cmath>

class Line{
public:
	Line(std::vector<mapTools::Point> pointsToConnect);
	~Line();
	std::vector<mapTools::Point> getPointsOnLine() const;

private:
	std::vector<mapTools::Point> pointsOnLine;
	void findPointsOnLine(std::vector<mapTools::Point> pointsToConnect);
};
