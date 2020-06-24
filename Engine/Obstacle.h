#pragma once
#include "Board.h"
#include <random>
#include "Snake.h"

class Obstacle
{
public:
	Obstacle(Board& brd, std::mt19937& rng, Snake& snk, int tolerance);
	void Spawn(std::mt19937& rng, Snake& snk, int tolerance);
	void Draw();
	bool GetFoodLocation(Location& loc, int tolerance);
	bool CheckInterCollision(Location& nloc);
	bool CheckSnakeCollision(Snake& snk, Location& deltaLoc);
private:
	class Segment
	{
	public:
		void Spawn(std::mt19937& rng, Snake& snk, Board& brd, int tolerance, Segment seg[], int nSegments);
		void Draw(Board& brd);
		Location GetLoc();
	private:
		Location loc;
		Color c;
	};
private:
	int nSegments = 0;
	static constexpr int nSegmentsMax = 30;
	Segment segments[nSegmentsMax];
	Board& brd;
};