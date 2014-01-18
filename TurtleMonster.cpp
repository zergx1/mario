#include "TurtleMonster.h"


TurtleMonster::TurtleMonster(void)
{
}

void TurtleMonster::Init()
{
	BaseMonster::Init();
	lives = 2;
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
	
	if(lives <= 1)
	{
		fy = fy - 16;
	}
	if(show)
	{
		int flag = 0;
		if(dirX == -1)
			flag = ALLEGRO_FLIP_HORIZONTAL;

		al_draw_bitmap_region(image, fx, fy, frameWidth,
			frameHeight, x, y, flag);
	}
}

TurtleMonster::~TurtleMonster(void)
{
}
