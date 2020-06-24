#include "Snake.h"

Snake::Snake(Board& brd)
	:
	brd( brd )
{
}

void Snake::Init(Location loc[])
{
	segments[0].InitHead(loc[0]);
	for (int i = 1; i < nSegments; i++) {
		segments[i].InitBody(loc[i]);
		segments[i].InitBody(loc[i]);
	}
	SetColor();
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
	if (nSegments < nSegmentsMax) {
		++nSegments;
	}

	segments[nSegments - 1].InitBody(segments[nSegments - 2].getLoc());
}

void Snake::Draw()
{
	for (int i = 0; i < nSegments; i++) {
		segments[i].Draw(brd);
	}
}

bool Snake::CheckCollision(Location deltaLoc)
{
	Location nextHeadloc = getNextHeadLoc(deltaLoc);

	for (int i = 1; i < nSegments; i++) {
		if (segments[i].getLoc().IsSameLocation(segments[0].getLoc())) {
			return true;
		}
	}

	if (nextHeadloc.x == brd.GetBoundX1() ||
		nextHeadloc.x == brd.GetBoundX2() ||
		nextHeadloc.y == brd.GetBoundY1() ||
		nextHeadloc.y == brd.GetBoundY2()) {
		return true;
	}

	return false;
}

bool Snake::GetFoodLoc(Location& loc, int tolerance)
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].getLoc().GetDistance(loc) <= tolerance) {
			return false;
		}
	}
	return true;
}

Location Snake::getNextHeadLoc(Location deltaLoc)
{
	return segments[0].getLoc().AddLoc(deltaLoc);
}

void Snake::SetColor()
{
	Color c;
	for (int i = 1; i < nSegments; i++) {
		if ((i-1) % 4 == 0) {
			c = colorBody1;
		}
		else if ((i-2) % 4 == 0) {
			c = colorBody2;
		}
		else if ((i-3) % 4 == 0) {
			c = colorBody3;
		}
		else if ((i-4) % 4 == 0) {
			c = colorBody4;
		}
		segments[i].setColor(c);
	}
}

void Snake::Segment::InitHead(const Location& n_loc)
{
	loc = n_loc;
	c = colorHead;
}

void Snake::Segment::InitBody(const Location& n_loc)
{
	loc = n_loc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::Follow(const Segment& seg)
{
	loc = seg.loc;
}

void Snake::Segment::setColor(Color nc)
{
	c = nc;
}

Location Snake::Segment::getLoc()
{
	return loc;
}
