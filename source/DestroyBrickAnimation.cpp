#include "header\DestroyBrickAnimation.h"
#include <iostream>

DestroyBrickAnimation::DestroyBrickAnimation(void)
{
}

void DestroyBrickAnimation::Init(int x, int y, BLKSTR *blockdata)
{
	this->active = true;
	this->x = x + 8;
	this->y = y + 8;
	this->x2 = x;
	this->y2 = y;
	this->yOffset = y - 20;
	this->velY = 2;
	this->velY2 = 4;
	this->dirY = -1;
	this->angle = 0;
	this->type = blockdata->user1;
	this->background = blockdata->user2;
	if (type == BRICK_ID)
		this->image = al_load_bitmap("Sprites/brickPart.png");
	else if (type == BRICK_DARK_ID)
		this->image = al_load_bitmap("Sprites/brick_darkPart.png");
	
	MapSetBlockInPixels(x, y, background);
}

void DestroyBrickAnimation::Update()
{
	if (active)
	{
		velY += dirY * 10.0 / 60.0;
		velY2 += dirY * 10.0 / 60.0;
		y += velY * dirY;
		y2 += velY2 * dirY;
		angle += 20;

			x += 1;
			x2 -= 1;

		if (dirY == 1 && y > 400)
		{
			active = false;
		}
		if (dirY == -1 && (velY <= 0 || velY2 <= 0))
		{
			dirY = 1;
			velY = velY2 = 0;
		}
	}
}

void DestroyBrickAnimation::Draw()
{
	if (active)
	{
		al_draw_rotated_bitmap(image, 4, 4, x2 - xOff, y2, angle * 0.01745329, 0);	// LT
		al_draw_rotated_bitmap(image, 4, 4, x - xOff, y2, angle * 0.01745329, 0);	// RT

		al_draw_rotated_bitmap(image, 4, 4, x2 - xOff, y, angle * 0.01745329, 0);	//LB
		al_draw_rotated_bitmap(image, 4, 4, x - xOff, y, angle * 0.01745329, 0);	//RB
	}
	
}

DestroyBrickAnimation::~DestroyBrickAnimation(void)
{
}
