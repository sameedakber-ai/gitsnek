#pragma once
#include "Board.h"
#include <assert.h>

class Snake
{
public:
	Snake(Board& brd);
	void Init(Location loc[]);
	void MoveBy(const Location& delta_loc);
	void Grow();
	void Draw();
	bool CheckCollision(Location deltaLoc);
	bool GetFoodLoc(Location& loc, int tolerance);
	Location getNextHeadLoc(Location deltaLoc);
	void SetColor();
private:
	class Segment
	{
	public:
		void InitHead(const Location& n_loc);
		void InitBody(const Location& n_loc);
		void MoveBy(const Location& delta_loc);
		void Draw(Board& brd);
		void Follow(const Segment& seg);
		void setColor(Color nc);
		Location getLoc();
	private:
		Location loc;
		Color c;
	};
private:
	Board& brd;
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 3;
	static constexpr Color colorHead = {167, 167, 10};
	static constexpr Color colorBody1 = {0, 98, 18};
	static constexpr Color colorBody2 = { 0, 133, 41 };
	static constexpr Color colorBody3 = { 4, 168, 36 };
	static constexpr Color colorBody4 = { 0, 133, 41 };
};
