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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	vx = 0;
	vy = 0;
	colliding = false;

	fixed_box = {200, 200, 5, 0, 255, 0};
	box = {400, 400, 5, 255, 0, 0};
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
	//logic
	vx *= 0;
	vy *= 0;
	if (wnd.kbd.KeyIsPressed(VK_RIGHT) && box.x < gfx.ScreenWidth - box.half_radius + 1) {
		vx += 1;
	}if (wnd.kbd.KeyIsPressed(VK_LEFT) && box.x > box.half_radius + 1) {
		vx -= 1;
	}if (wnd.kbd.KeyIsPressed(VK_UP) && box.y > box.half_radius + 1) {
		vy -= 1;
	}if (wnd.kbd.KeyIsPressed(VK_DOWN) && box.y < gfx.ScreenHeight - box.half_radius + 1) {
		vy += 1;
	}

	box.x += vx;
	box.y += vy;

	colliding = CheckOverlapping(box, fixed_box);
}

void Game::ComposeFrame()
{
	fixed_box.r = 0;
	fixed_box.g = 255;
	fixed_box.b = 0;

	DrawBox(box);

	int r, g, b;

	box.r = colliding ? 255 : 255;
	box.g = colliding ? 0 : 255;
	box.b = colliding ? 0 : 255;

	DrawBox(fixed_box);
}

void Game::DrawBox(Box& box)
{
	gfx.PutPixel(-box.half_radius + box.x, -box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + box.x, -box.half_radius + 1 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + box.x, -box.half_radius + 2 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + 1 + box.x, -box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + 2 + box.x, -box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + box.x, box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + box.x, box.half_radius - 1 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + box.x, box.half_radius - 2 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + 1 + box.x, box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(-box.half_radius + 2 + box.x, box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius + box.x, -box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius + box.x, -box.half_radius + 1 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius + box.x, -box.half_radius + 2 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius - 1 + box.x, -box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius- 2 + box.x, -box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius + box.x, box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius + box.x, box.half_radius - 1 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius + box.x, box.half_radius - 2 + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius - 1 + box.x, box.half_radius + box.y, box.r, box.g, box.b);
	gfx.PutPixel(box.half_radius -2 + box.x, box.half_radius + box.y, box.r, box.g, box.b);
}

bool Game::CheckOverlapping(Box& box, Box& other_box)
{
	const int left_x = box.x - 5;
	const int right_x = box.x + 5;
	const int top_x = box.y - 5;
	const int bottom_x = box.y + 5;

	const int left_box = other_box.x - 5;
	const int right_box = other_box.x + 5;
	const int top_box = other_box.y - 5;
	const int bottom_box = other_box.y + 5;

	if (left_x < right_box &&
		right_x > left_box &&
		bottom_x > top_box &&
		top_x < bottom_box) 
		return true;
	else 
		return false;
}
