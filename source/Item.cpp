#include "header\Item.h"
#include "header/Sound.h"

int width3 = 320;
int height3 = 240;

Item::Item(void)
{
	live = false;
	show = false;
}

Item::~Item(void)
{
}

void Item::Init(TYPE t, float x1, float y1)
{
	BaseCharacter::Init();
	live = false;
	show = false;
	status = HIDDEN;
	type = t;
	exitSpeed = 0.1;

	//x = 1;
	//x = 50;
	//y = 20;
	x = x1;
	y = y1;
	velX = 0;
	velY = 0;
	dirX = -1;
	dirY = 1;

	startFrame = 0;
	maxFrame = 1;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 5;
	frameWidth = 16;
	frameHeight = 16;
	animationColumns = 1;
	animationDirection = 1;
	score = 100;
	lives = 1;

//	image = al_load_bitmap("Sprites/flower_monster.png");
//	al_convert_mask_to_alpha(image, al_map_rgb(238, 243, 250));

	image = al_load_bitmap("Sprites/mushroom.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));
	death_sound = al_load_sample("Audio/death_monster1.ogg");
	if(t == MUSHROOM)
	{
		speedAfterExitX = 2;
		speedAfterExitY = 0;
	}
	else
	{
		image = al_load_bitmap("Sprites/flower.png");
		speedAfterExitX = 0;
		speedAfterExitY = 0;
	}
	startY = y;


}

void Item::Update()
{
	if(status == LEAVING)
	{
		y -= exitSpeed;
		if(y <= startY-frameHeight)
		{
			status = LEFT;
			velX = speedAfterExitX;
		}


	}
	if(++frameCount >= frameDelay)
	{

			curFrame += animationDirection;
			if(curFrame >= maxFrame && animationColumns > 0)
				curFrame = startFrame;
			else if(curFrame <= startFrame && animationColumns > 0)
				curFrame = maxFrame - 1;


		frameCount = 0;
	}

	if (!live || status != LEFT)	// trick do spadania 
		return;
	
	if ((x <= 0 && dirX == -1) || (x >= width3 - frameWidth && dirX == 1) || (Map::collided(this, 'x')))
	{
		dirX *= -1;
		//animationDirection *= 1;
	}
	else
	{
		x += velX * dirX;
	}

	if ( (y >= height3 - frameHeight) || (Map::collided(this, 'y')))
	{
		velY = 0;
		//velX = 1;
		//animationDirection *= 1;
	}
	else if(status == LEFT)
	{
		velY += 10.0 / 60.0;
		//velX = 0.5;
	}
	y += velY * dirY;


}

void Item::LeaveBox()
{
	curFrame = 0;
	show = true;
	live = true;
	status = LEAVING;
	Sound::play(Sound::POWER_2xUP);
}

void Item::Draw(float xOff)
{
	int fx = (curFrame % animationColumns) * frameWidth;
	int fy = (curFrame / animationColumns) * frameHeight;
	int flag = 0;
	float new_y = frameHeight;
	if(status != LEFT)
		new_y = (startY - y);
	if(show)
	{
		al_draw_bitmap_region(image, fx, fy, frameWidth,
			new_y, (int)x - xOff, (int)y, flag);
	}
}

void Item::Hit()
{
	Kill();
}

void Item::KillByShot()
{
	Kill();
	lives = 0;

}

void Item::Kill()
{
	live = false;
	velX = 0;
	//velY = 3;
	//dirY = -1;
	startFrame = 0;
	maxFrame = 1;
	al_play_sample(death_sound, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

}


