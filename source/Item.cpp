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

void Item::Init(float x1, float y1, TYPE t)
{
	BaseCharacter::Init(x1, y1);
	live = true;
	show = false;
	status = HIDDEN;
	type = t;
	exitSpeed = 0.1;
	score = 1000;

	//x = 1;
	//x = 50;
	//y = 20;
	x = x1;
	y = y1;
	velX = 0;
	velY = 0;
	dirX = 1;
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
	else if( t == FLOWER)
	{
		image = al_load_bitmap("Sprites/flower.png");
		speedAfterExitX = 0;
		speedAfterExitY = 0;
	}
	else if( t == GREEN_MUSHROOM)
	{
		image = al_load_bitmap("Sprites/green_mushroom.png");
		speedAfterExitX = 2;
		speedAfterExitY = 0;
	}
	else
	{
		image = al_load_bitmap("Sprites/star.png");
		speedAfterExitX = 2;
		speedAfterExitY = 2;
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
	
	if (x < 0 || y > height3)
		live = false;

	if ( (Map::collided(this, 'x')))
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
	if(speedAfterExitY && (int)y % 16 == 0 && dirY == 1 && velY == 0)
	{
			velY = -speedAfterExitY;
	}
	y += velY * dirY;

}

void Item::LeaveBox()
{
	if (live)
	{
		curFrame = 0;
		show = true;
		//live = true;
		status = LEAVING;
		Sound::play(Sound::POWER_APPEARS);

	}
}

void Item::Draw()
{
	int fx = curFrame * frameWidth;
	int fy = curFrame * frameHeight;
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
	if (status != LEAVING)
	{
		dirX *= -1;
		velY = -2;
	}
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

void Item::collisionWithOther(BaseCharacter* character)
{
	if (live)
	{
		float myXLEFT = x;
		float myYTOP = y;
		float myXRIGHT = x + frameWidth;
		float myYBOTTOM = y + frameHeight;

		float xLEFT = character->x;
		float yTOP = character->y;
		float xRIGHT = character->x + character->frameWidth;
		float yBOTTOM = character->y + character->frameHeight;

		bool horizontal = (xLEFT >= myXLEFT && xLEFT <= myXRIGHT) || (xRIGHT >= myXLEFT && xRIGHT <= myXRIGHT);
		bool vertical = (yTOP >= myYTOP && yTOP <= myYBOTTOM) || (yBOTTOM >= myYTOP && yBOTTOM <= myYBOTTOM);
		if (horizontal && vertical && character->live)
		{
			character->takeItem(this);
			live = false;
		}
	}
}