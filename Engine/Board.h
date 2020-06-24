#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& gfx, int paddingLeft, int paddingTop, int paddingRight, int paddingBottom);
	void DrawCell(Location& loc, Color c);
	int GetBoundX1();
	int GetBoundY1();
	int GetBoundX2();
	int GetBoundY2();
	void Draw();
private:
	int paddingLeft;
	int paddingTop;
	int paddingRight;
	int paddingBottom;
	static constexpr int dimension = 18;
	Graphics& gfx;
	int posX[2] = {};
};
