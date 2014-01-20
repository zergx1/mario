#include "header/TurtleMonster.h"


TurtleMonster::TurtleMonster(void)
{
}

void TurtleMonster::Init()
{
	BaseMonster::Init();
	lives = 3;
	image = al_load_bitmap("Sprites/turtle_monster.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
	startFrame = 0;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 15;
	frameWidth = 16;
	frameHeight = 32;
	animationColumns = 6;
	animationDirection = 1;
	timeToReborn = 200;
	currentTimeToReborn = 0;

}

void TurtleMonster::Hit()
{
	lives--;
	if(lives == 0)
		Kill();
	else if(lives == 1)
	{
		startFrame = 3;
		maxFrame = 6;
		frameDelay = 5;
		velX = 3;
		//curFrame = 3;
		//live = true;
	}
	else if(lives == 2)
	{
		velX = 0;
		startFrame = 3;
		maxFrame = 6;
		curFrame = 3;
	}

}

void TurtleMonster::Kill()
{

	live = false;
	velX = 0;
	startFrame = maxFrame-1;
	//maxFrame = 1;
	al_play_sample(death_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void TurtleMonster::Draw()
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;
	int flag = 0;

	if(lives == 2)
	{
		if(currentTimeToReborn++ > timeToReborn)
			revive();
	}
	else if(lives <= 1)
	{
		if(killedByShot )//&& y > deathJumpY)
		{
			y -= deathJumpY;
			flag = ALLEGRO_FLIP_VERTICAL;
			deathJumpY -= fallingSpeedFactor;
		}
		else
			fy = fy - 16;
	}
	if(show)
	{
		if(dirX == -1 && flag == 0)
			flag = ALLEGRO_FLIP_HORIZONTAL;

		al_draw_bitmap_region(image, fx, fy, frameWidth,
			frameHeight, x, y, flag);
	}
}

void TurtleMonster::KillByShot()
{
	killedByShot = true;
	lives = 0;
	Kill();


}

void TurtleMonster::revive()
{
	lives = 3;
	velX = 1;
	startFrame = 0;
	maxFrame = 2;
	curFrame = 0;
	currentTimeToReborn = 0;
}

TurtleMonster::~TurtleMonster(void)
{
}
