#include "header\Bullet.h"
#include "header\Map.h"

int width2 = 320;
int height2 = 240;

Bullet::Bullet(void)
{
}

void Bullet::Init()
{

	live = false;
	show = false;
	//currentJumpTime = 0;
	//maxJumpTime = 100;
	x = 1;
	x = 50;
	y = 0;
	velX = 3;
	velY = 0;
	dirX = 1;
	dirY = 1;

	startFrame = 0;
	maxFrame = 4;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 1;
	frameWidth = 16;
	frameHeight = 16;
	animationColumns = 4;
	animationDirection = 1;
	score = 100;
	lives = 1;

//	image = al_load_bitmap("Sprites/flower_monster.png");
//	al_convert_mask_to_alpha(image, al_map_rgb(238, 243, 250));
	on_shoot = al_load_sample("Audio/Fireball.ogg");

	image = al_load_bitmap("Sprites/bullets.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

}

void Bullet::Update()
{
	if(live)
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
		y += velY * dirY;
	
		if ((Map::collided(this, 'x')))
		{
			Kill();
			//dirX *= -1;
			//animationDirection *= 1;
		}

		if ((y >= height2 - frameHeight) || (Map::collided(this, 'y')))
		{
			if(y >= height2)
				Kill();

			//animationDirection *= 1;
		}
		else
		{
			velY += 10.0 / 120.0;
			//velX = 0.2;
		}
		if((int)y % 16 == 0 && dirY == 1 && velY == 0)
		{
			velY = -1.5;
		}

	}
	
}
void Bullet::Shoot(float x1, float y1, int dirX1)
{
	al_play_sample(on_shoot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

	x = x1;
	y = y1;
	dirX = dirX1;
			if(!live && !show)
			{
				live = true;
				show = true; 

			}
}

void Bullet::Draw(float xOff)
{
	if(live && show)
	{
		int fx = (curFrame % animationColumns) * frameWidth;
		int fy = (curFrame / animationColumns) * frameHeight;
		int flag = 0;
		if(show)
		{
			al_draw_bitmap_region(image, fx, fy, frameWidth,
				frameHeight, x - xOff, y+4, flag);
		}
	}
}

void Bullet::Hit()
{

}

void Bullet::KillByShot()
{
	
}

void Bullet::Kill()
{
	live = false;
	show = false;
}




Bullet::~Bullet(void)
{
}
