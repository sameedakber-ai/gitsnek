/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "Location.h"
#include "Food.h"
#include "Obstacle.h"
#include <random>
#include "SpriteCodex.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	Location ChangeDirection(Location& loc1, Location& loc2);
	bool LimitSpeed(int MoveAfter, int& Counter);
	bool NextObstacle(int& Counter, int generateAfter);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	Board brd;
	Location loc[3];
	Snake snk;
	Location deltaLoc = { 0, -1 };
	int Counter = 0;
	int WaitTime = 10;
	bool grow = false;
	bool growConfirm = true;
	std::mt19937 rng;
	Food food;
	Obstacle ob;
	SpriteCodex sp;
	bool caution = false;

	bool gameStart = false;
	int gameStartX = 270;
	int gameStartY = 210;

	bool gameOver = false;
	int gameOverX = 335;
	int gameOverY = 270;
	/********************************/
	/*  User Variables              */
	/********************************/
};