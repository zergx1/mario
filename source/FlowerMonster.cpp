#include "header/FlowerMonster.h"

FlowerMonster::FlowerMonster(void)
{
}

void FlowerMonster::Init()
{
	BaseMonster::Init();
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
	BaseMonster::Update();
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
