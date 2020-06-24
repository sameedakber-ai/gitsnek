#include "Location.h"

void Location::Add(Location nloc)
{
	x += nloc.x;
	y += nloc.y;
}

Location Location::AddLoc(Location nloc)
{
	Location nextLoc = { x, y };
	nextLoc.x += nloc.x;
	nextLoc.y += nloc.y;
	return nextLoc;
}

bool Location::IsSameLocation(Location& loc)
{
	return (x == loc.x && y == loc.y);
}

int Location::GetDistance(Location& loc)
{
	return floor((sqrt(pow((loc.x - x), 2) + pow((loc.y - y), 2))));
}

bool Location::operator==(Location& nloc)
{
	return x==nloc.x && y==nloc.y;
}
