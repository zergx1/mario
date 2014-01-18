#include "BaseMonster.h"


int width = 320;
int height = 240;

BaseMonster::BaseMonster(void)
{
}


void BaseMonster::Init(ALLEGRO_BITMAP *img)
{
	x = 1;
	x = rand() % (width - 20) + 20;
	y = rand() % (height - 20) + 20;
	velX = 2;
	velY = rand() % 7 + 2;
	dirX = -1;
	dirY = -1;

	startFrame = 1;
	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 16;
	frameHeight = 16;
	animationColumns = 3;
	animationDirection = 1;

	image = img;
}

void BaseMonster::Update()
{
	if(++frameCount >= frameDelay)
	{

			curFrame += animationDirection;
			if(curFrame >= maxFrame && animationColumns > 0)
				curFrame = startFrame;
			else if(curFrame <= startFrame && animationColumns > 0)
				curFrame = maxFrame - 1;


		frameCount = 0;
	}

	x += velX * dirX;
	//y += velX * dirY;

	if((x <= 0 && dirX == -1) || 
		(x >= width - frameWidth && dirX == 1))
	{
		dirX *= -1;
		animationDirection *= 1;
	}

}


void BaseMonster::Draw()
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;

	al_draw_bitmap_region(image, fx, fy, frameWidth,
		frameHeight, x, y, 0);
}

BaseMonster::~BaseMonster(void)
{
}
