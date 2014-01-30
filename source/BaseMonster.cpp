#include "header/BaseMonster.h"
#include "header/Map.h"
#include <math.h>
#include <iostream>


int width = 320;
int height = 240;

BaseMonster::BaseMonster(void)
{
}

BaseMonster::~BaseMonster(void)
{
}

void BaseMonster::Init()
{
	BaseCharacter::Init();
	live = true;
	show = true;
	killedByShot = false;


	timeToClear = 130;
	currentTimeToClear = 0;
	x = 1;
	x = 50;
	y = 0;
	velX = 0.5;
	velY = 0;
	dirX = -1;
	dirY = 1;

	startFrame = 1;
	maxFrame = 3;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 16;
	frameHeight = 16;
	animationColumns = 3;
	animationDirection = 1;
	score = 100;
	lives = 1;
	deathJumpY = 5;
	fallingSpeedFactor = 0.3;

//	image = al_load_bitmap("Sprites/flower_monster.png");
//	al_convert_mask_to_alpha(image, al_map_rgb(238, 243, 250));

	image = al_load_bitmap("Sprites/monster1.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
	death_sound = al_load_sample("Audio/death_monster1.ogg");


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

	if (!live && !killedByShot)
	{

		if (currentTimeToClear++ >= timeToClear)
			show = false;
		else
		{
			//if(timeToClear/(deathBlinks - currentdeathBlinks) <= currentTimeToClear  )
			if (currentTimeToClear % 10 == 0)
			{
				show = !show;
			}
		}

	}

	if (!live)	// trick do spadania 
		return;
	
	if ((x <= 0 && dirX == -1) || (x >= width - frameWidth && dirX == 1) || (Map::collided(this, 'x')))
	{
		dirX *= -1;
		//animationDirection *= 1;
	}
	else
	{
		x += velX * dirX;
	}

	if ((y >= height - frameHeight) || (Map::collided(this, 'y')))
	{
		velY = 0;
		//velX = 1;
		//animationDirection *= 1;
	}
	else
	{
		velY += 10.0 / 60.0;
		//velX = 0.5;
	}
	y += velY * dirY;


}


void BaseMonster::Draw(float xOff)
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
			frameHeight, (int)x - xOff, (int)y, flag);
	}
}

void BaseMonster::Hit()
{
	Kill();
}

void BaseMonster::KillByShot()
{
	Kill();
	killedByShot = true;
	lives = 0;

}

void BaseMonster::Kill()
{
	live = false;
	velX = 0;
	//velY = 3;
	//dirY = -1;
	startFrame = 0;
	maxFrame = 1;
	al_play_sample(death_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

}

