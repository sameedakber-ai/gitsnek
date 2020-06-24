#include "Board.h"

Board::Board(Graphics& gfx, int npaddingLeft, int npaddingTop, int npaddingRight, int npaddingBottom)
	:
	gfx( gfx )
{
	paddingLeft = npaddingLeft;
	paddingRight = npaddingRight;
	paddingTop = npaddingTop;
	paddingBottom = npaddingBottom;
}

void Board::DrawCell(Location& loc, Color c)
{
	gfx.DrawFromDim(loc.x, loc.y, dimension, 3, c);
}

int Board::GetBoundX1()
{
	return paddingLeft-1;
}

int Board::GetBoundY1()
{
	return paddingTop - 1;
}

int Board::GetBoundX2()
{
	return gfx.ScreenWidth/dimension - paddingRight;
}

int Board::GetBoundY2()
{
	return gfx.ScreenHeight / dimension - paddingBottom;
}

void Board::Draw()
{
	int x1 = paddingLeft*dimension;
	int y1 = paddingTop*dimension;
	int x2 = gfx.ScreenWidth - (paddingRight*dimension);
	int y2 = gfx.ScreenHeight - (paddingBottom * dimension);
	Color c = { 91, 87, 155 };
	gfx.DrawBoard(x1, y1, x2, y2, 5, c);
}
