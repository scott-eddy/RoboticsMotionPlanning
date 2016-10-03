#pragma once
#include <vector>
#include "common.h"
#include <cmath>

class Line{
public:
	Line(std::vector<mapTools::Point> pointsToConnect);
	~Line();
	std::vector<mapTools::Point> getPointsOnLine();

private:
	std::vector<mapTools::Point> pointsOnLine;
	void findPointsOnLine(std::vector<mapTools::Point> pointsToConnect);
};