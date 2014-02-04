#include "header\SimpleAnimation.h"

SimpleAnimation::SimpleAnimation(void)
{
}

void SimpleAnimation::Init(int x, int y, int type)
{
	this->active = true;
	this->x = x;
	this->y = y;
	this->yOffset = y - 8;
	this->dirY = -1;
	this->animationDuration = 1;
	this->type = type;
	if (type == BRICK_ID)
		this->image = al_load_bitmap("Sprites/brick.png");
	else if (type == QUESTION_ID)
		this->image = al_load_bitmap("Sprites/solid.png");
	MapSetBlockInPixels(x, y, EMPTY_ID);
}

void SimpleAnimation::Update()
{
	if (active)
	{
		y += dirY;
		if (dirY == 1 && y == yOffset + 8)
		{
			active = false;
			if (type == BRICK_ID)
				MapSetBlockInPixels(x, y, BRICK_ID);
			else if (type == QUESTION_ID)
				MapSetBlockInPixels(x, y, SOLID_ID);
		}
		else if (dirY == -1 && y == yOffset)
			dirY = 1;
	}
}

void SimpleAnimation::Draw()
{
	if (active)
	{
		al_draw_bitmap_region(image, 0, 0, 16, 16, x - xOff, y, 0);
	}
	
}

SimpleAnimation::~SimpleAnimation(void)
{
}

void SimpleAnimation::collisionWithOther(BaseCharacter* character)
{
	if (active)
	{
		float myXLEFT = x;
		float myYTOP = y;
		float myXRIGHT = x + 16;
		float myYBOTTOM = y + 16;

		float xLEFT = character->x;
		float yTOP = character->y;
		float xRIGHT = character->x + character->frameWidth;
		float yBOTTOM = character->y + character->frameHeight;

		bool horizontal = (xLEFT >= myXLEFT && xLEFT <= myXRIGHT) || (xRIGHT >= myXLEFT && xRIGHT <= myXRIGHT);
		bool vertical = (yTOP >= myYTOP && yTOP <= myYBOTTOM) || (yBOTTOM >= myYTOP && yBOTTOM <= myYBOTTOM);
		if (horizontal && vertical && character->live)
		{
			character->KillByShot();
		}
	}


}