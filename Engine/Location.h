#pragma once
#include <math.h>

struct Location
{
	void Add(Location nloc);
	Location AddLoc(Location nloc);
	bool IsSameLocation(Location& loc);
	int GetDistance(Location& loc);
	bool operator==(Location& nloc);
	int x;
	int y;
};
