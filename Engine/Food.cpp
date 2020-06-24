#include "Food.h"

Food::Food(Board& brd, Snake& snake, Obstacle& ob, std::mt19937& rng, int tolerance)
	:
	brd(brd)
{
	Respawn(snake, ob, rng, tolerance);
}

void Food::Respawn(Snake& snake, Obstacle& ob, std::mt19937& rng, int tolerance)
{
	std::uniform_int_distribution<int> colorDist(0, 255);
	std::uniform_int_distribution<int> locDistX(brd.GetBoundX1() + 1, brd.GetBoundX2() - 1);
	std::uniform_int_distribution<int> locDistY(brd.GetBoundY1() + 1, brd.GetBoundY2() - 1);

	do {
		loc = { locDistX(rng), locDistY(rng) };
	} while (!snake.GetFoodLoc(loc, tolerance) && !ob.GetFoodLocation(loc, tolerance));

	c.SetR(colorDist(rng));
	c.SetG(colorDist(rng));
	c.SetB(colorDist(rng));


}

void Food::Draw()
{
	brd.DrawCell(loc, c);
}

Location Food::GetLoc()
{
	return loc;
}
