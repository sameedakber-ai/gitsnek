/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx, 2, 2, 2, 2),
	rng(std::random_device()()),
	ob(brd, rng, snk, 4),
	food(brd, snk, ob, rng, 10),
	snk(brd)
{
	loc[0] = { 7,3 };
	loc[1] = { 7,4 };
	loc[2] = { 7,5 };
	snk.Init(loc);
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameOver) {

		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			gameStart = true;
		}

		if (gameStart) {

			if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
				grow = true;
			}

			Location deltaLocNew = deltaLoc;

			if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				deltaLocNew = { -1, 0 };
			}

			if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
				deltaLocNew = { 0, 1 };
			}

			if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
				deltaLocNew = { 1, 0 };
			}

			if (wnd.kbd.KeyIsPressed(VK_UP)) {
				deltaLocNew = { 0, -1 };
			}


			if (growConfirm) {
				if (!(deltaLoc == deltaLocNew)) {
					growConfirm = false;
				}
				deltaLoc = ChangeDirection(deltaLoc, deltaLocNew);
			}


			bool move = LimitSpeed(WaitTime, Counter);
			bool snakeCollided = (snk.CheckCollision(deltaLoc) ||
				ob.CheckSnakeCollision(snk, deltaLoc));

			if (!grow) {
				grow = snk.getNextHeadLoc(deltaLoc) == food.GetLoc();
			}

			if (move) {
				if (!snakeCollided) {
					snk.MoveBy(deltaLoc);
					growConfirm = true;
					if (grow) {
						snk.Grow();
						snk.SetColor();
						food.Respawn(snk, ob, rng, 20);
						grow = false;
						if (WaitTime >= 3) {
							WaitTime--;
						}
					}
					bool generateObstacle = NextObstacle(Counter, 240);
					if (generateObstacle) {
						ob.Spawn(rng, snk, 3);
					}
				}
				else {
					gameOver = true;
				}
			}

		}
	}

}

Location Game::ChangeDirection(Location& loc1, Location& loc2)
{
	Location loc = loc1;
	
	if (abs(loc1.x + loc2.x) == 1 || abs(loc2.y + loc2.y) == 1) {
		loc = loc2;
	}

	return loc;
}

bool Game::LimitSpeed(int MoveAfter, int& Counter)
{
	Counter++;
	if (Counter % MoveAfter == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Game::NextObstacle(int& Counter, int generateAfter)
{
	if (Counter % generateAfter == 0) {
		return true;
	}
	else {
		return false;
	}
}

void Game::ComposeFrame()
{
	if (!gameStart) {
		sp.DrawTitle(gameStartX, gameStartY, gfx);
	}
	else {
		brd.Draw();
		snk.Draw();
		food.Draw();
		ob.Draw();

		if (gameOver) {
			sp.DrawGameOver(gameOverX, gameOverY, gfx);
		}
	}
}
