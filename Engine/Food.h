#pragma once
#include "Board.h"
#include <random>
#include "Snake.h"
#include "Obstacle.h"

class Food
{
public:
	Food(Board& brd, Snake& snake, Obstacle& ob, std::mt19937& rng, int tolerance);
	void Respawn(Snake& snake, Obstacle& ob, std::mt19937& rng, int tolerance);
	void Draw();
	Location GetLoc();
private:
	Location loc;
	Color c;
	Board& brd;
};
