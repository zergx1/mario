#include "header/Player.h"
#include "header/Keyboard.h"
#include <iostream>
#include <cmath>
Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::Init(Map* map)
{
	this->map = map;
	this->lives = 3;
	this->x = 0;
	this->y = 0;
	this->jump = false;

	image = al_load_bitmap("Sprites/monster1.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	velX = 1;
	velY = 0;
	dirX = 1;
	dirY = 1;

	show = true;

	startFrame = 1;
	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 16;
	frameHeight = 16;
	animationColumns = 3;
	animationDirection = 1;
	score = 0;
}

void Player::Update(bool *keys)
{
	int width = 320;
	int height = 240;
	if (++frameCount >= frameDelay)
	{

		curFrame += animationDirection;
		if (curFrame >= maxFrame && animationColumns > 0)
			curFrame = startFrame;
		else if (curFrame <= startFrame && animationColumns > 0)
			curFrame = maxFrame - 1;

		frameCount = 0;
	}

	if (keys[Keyboard::LEFT])
		dirX = -1;
	else if (keys[Keyboard::RIGHT])
		dirX = 1;

	if (keys[Keyboard::UP] && velY == 0 && !jump)
	{
		velY = 3.0;
		dirY = -1;
		jump = true;
	}
	
	if ((keys[Keyboard::LEFT] || keys[Keyboard::RIGHT]) && !(Map::collided(this, 'x')) && x + velX * dirX >= map->xOff)
	{
		velX = 1;
		x += velX * dirX;

		if (x - map->xOff > 16 * 8) // map moves
			map->update(keys);
	}
	else
		velX = 0;

	y += dirY * velY;
	
	if (velY <= 0) // start falling down
	{
			dirY = 1;
		if (y % 16 != 0)	// adjustment to title 
			y -= 16 - (y % 16);

	}
	
	if (Map::collided(this, 'y'))
	{
		velY = 0;
		jump = false;
		dirY = 1;
	}
	else
	{
		velY += dirY * 10.0 / 60.0;
		
	}

	if (y >= height - frameHeight)
		live = false;

}


void Player::Draw(float xOff)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;


	if (show)
	{
		al_draw_bitmap_region(image, fx, fy, frameWidth,
			frameHeight, x - xOff, y, 0);
	}
}