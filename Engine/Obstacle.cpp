#include "Obstacle.h"

Obstacle::Obstacle(Board& brd, std::mt19937& rng, Snake& snk, int tolerance)
	:
	brd ( brd )
{
	Spawn(rng, snk, tolerance);
}

void Obstacle::Spawn(std::mt19937& rng, Snake& snk, int tolerance)
{
	++nSegments;
	segments[nSegments-1].Spawn(rng, snk, brd, tolerance, segments, nSegments);
}

void Obstacle::Draw()
{
	for (int i = 0; i < nSegments; i++) {
		segments[i].Draw(brd);
	}
}

bool Obstacle::GetFoodLocation(Location& loc, int tolerance)
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLoc().GetDistance(loc) <= tolerance) {
			return false;
		}
	}

	return true;
}

bool Obstacle::CheckSnakeCollision(Snake& snk, Location& deltaLoc)
{
	for (int i = 0; i < nSegments; i++) {
		if (segments[i].GetLoc() == snk.getNextHeadLoc(deltaLoc)) {
			return true;
		}
	}
	return false;
}

bool Obstacle::CheckInterCollision(Location& nloc)
{
	for (int i = 0; i < nSegments - 1; i++) {
		if (segments[i].GetLoc() == nloc) {
			return false;
		}
	}

	return true;
}

void Obstacle::Segment::Spawn(std::mt19937& rng, Snake& snk, Board& brd, int tolerance, Segment seg[], int nSegments)
{
	std::uniform_int_distribution<int> locDistX(brd.GetBoundX1() + 1, brd.GetBoundX2() - 1);
	std::uniform_int_distribution<int> locDistY(brd.GetBoundY1() + 1, brd.GetBoundY2() - 1);

	bool notColliding = true;

	do {
		loc = { locDistX(rng), locDistY(rng) };
		for (int i = 0; i < nSegments - 1; i++) {
			if (seg[nSegments - 1].GetLoc().GetDistance(loc) <= tolerance) {
				notColliding = false;
			}
		}
	} while (!snk.GetFoodLoc(loc, tolerance) && !notColliding);

	c = Colors::Gray;
}

void Obstacle::Segment::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

Location Obstacle::Segment::GetLoc()
{
	return loc;
}
