//TODO this could be a useful class when building rooms

#pragma once
#include "map_tools_common.h"
class Wall{
public:
	Wall();
	~Wall();

	mapTools::Point startPoint;
	mapTools::Point endPoint;
};
