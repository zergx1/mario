#include "header/FlowerMonster.h"

FlowerMonster::FlowerMonster(void)
{
}

void FlowerMonster::Init(int x0, int y0)
{
	BaseMonster::Init(x0, y0);
	image = al_load_bitmap("Sprites/flower_monster.png");
	al_convert_mask_to_alpha(image, al_map_rgb(238, 243, 250));
	frameWidth = 32;
	frameHeight = 32;
	startFrame = 0;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	velX = 0;
	velY = 0.6;
	waitY = 200;
	y = 80;
	startY = y;
	currentWaitY = 0;


}

void FlowerMonster::Draw()
{

	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;
	int flag = 0;
	if(!live)
	{
		if(killedByShot )//&& y > deathJumpY)
		{
			y -= deathJumpY;
			flag = ALLEGRO_FLIP_VERTICAL;
			deathJumpY -= fallingSpeedFactor;
		}
		else
			fy = fy - 8;
	}
	if(show)
	{
		al_draw_bitmap_region(image, fx, fy, frameWidth,
			(startY - y), x, y, flag);
	}
}

void FlowerMonster::Kill()
{
	BaseMonster::Kill();
}

void FlowerMonster::Update()
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
	if(currentWaitY == 0 || currentWaitY > waitY)
	{
		currentWaitY = 0;
		y += velY * dirY;
	}

	//if((x <= 0 && dirX == -1) || 
	//	(x >= width - frameWidth && dirX == 1))
	//{
	//	dirX *= -1;
	//	animationDirection *= 1;
	//}
	if(currentWaitY > 0)
		currentWaitY++;
	else if((y <= startY-frameHeight && dirY == -1) || (y >= startY && dirY == 1))
	{
		currentWaitY = 1;
		dirY *= -1;
		animationDirection *= 1;
	}
	if(!live && !killedByShot)
	{

		if(currentTimeToClear++ >= timeToClear)
			show = false;
		else
		{
			//if(timeToClear/(deathBlinks - currentdeathBlinks) <= currentTimeToClear  )
		if(currentTimeToClear % 10 == 0 )
			{
				show = !show;
			}


		}

	}

}


void FlowerMonster::Hit()
{
	BaseMonster::Hit();
}

void FlowerMonster::KillByShot()
{
	BaseMonster::KillByShot();
}


FlowerMonster::~FlowerMonster(void)
{
}
