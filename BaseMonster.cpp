#include "BaseMonster.h"


int width = 320;
int height = 240;

BaseMonster::BaseMonster(void)
{
}


void BaseMonster::Init()
{
	live = true;
	show = true;

	timeToClear = 130;
	currentTimeToClear = 0;
	x = 1;
	x = rand() % (width - 20) + 20;
	y = rand() % (height - 20) + 20;
	velX = 1;
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
	score = 100;
	lives = 1;

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

	x += velX * dirX;
	//y += velX * dirY;

	if((x <= 0 && dirX == -1) || 
		(x >= width - frameWidth && dirX == 1))
	{
		dirX *= -1;
		animationDirection *= 1;
	}
	if(!live)
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


void BaseMonster::Draw()
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;
	
	if(!live)
	{
		fy = fy - 8;
	}
	if(show)
	{
		al_draw_bitmap_region(image, fx, fy, frameWidth,
			frameHeight, x, y, 0);
	}
}

void BaseMonster::Hit()
{
	Kill();
}

void BaseMonster::Kill()
{
	live = false;
	velX = 0;
	startFrame = 0;
	maxFrame = 1;
	al_play_sample(death_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

}

BaseMonster::~BaseMonster(void)
{
}
