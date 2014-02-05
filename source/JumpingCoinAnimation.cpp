#include "header\JumpingCoinAnimation.h"
#include <iostream>

JumpingCoinAnimation::JumpingCoinAnimation(void)
{
}

void JumpingCoinAnimation::Init(int x, int y, BLKSTR *blockdata)
{
	active = true;
	this->x = x;
	this->y = y - 16;
	velY = 2;
	yOffset = y - 40;
	image = al_load_bitmap("Sprites/coin.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	dirY = -1;
	startFrame = 0;
	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 2;
}

void JumpingCoinAnimation::Update()
{
	if (active)
	{
		y += velY*dirY;
		if (dirY == 1 && y == yOffset + 30)
		{
			active = false;
			globalText.floatingScore(x, y, 200);
		}
		else if (dirY == -1 && y == yOffset)
			dirY = 1;

		if (++frameCount >= frameDelay)
		{
			curFrame++;
			if (curFrame >= maxFrame)
				curFrame = startFrame;
			else if (curFrame <= startFrame)
				curFrame = maxFrame - 1;

			frameCount = 0;
		}
	}
}

void JumpingCoinAnimation::Draw()
{
	if (active)
	{
		int fx = curFrame * 16;
		int fy = 0;
		al_draw_bitmap_region(image, fx, fy, 16, 16, x - xOff, y, 0);
	}
}

JumpingCoinAnimation::~JumpingCoinAnimation(void)
{
}
