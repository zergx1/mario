#include "header/Player.h"
#include "header/Keyboard.h"
#include <iostream>
#include <cmath>

Player::Player(void)
{
}


Player::~Player(void)
{
}

void Player::Init(Map* map)
{
	space_clicked = false;
	this->map = map;
	this->lives = 3;
	this->x = 0;
	this->y = 0;
	this->live = true;

	image = al_load_bitmap("Sprites/small_mario.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	jump = al_create_sample_instance(al_load_sample("Audio/jump.ogg"));
	die = al_create_sample_instance(al_load_sample("Audio/mario_dies.ogg"));
	breakBrick = al_create_sample_instance(al_load_sample("Audio/break_brick.ogg"));

	al_attach_sample_instance_to_mixer(jump, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(die, al_get_default_mixer());
	al_attach_sample_instance_to_mixer(breakBrick, al_get_default_mixer());

	velX = 1;
	velY = 0;
	dirX = 1;
	dirY = 1;

	show = true;

	startFrame = 0;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 10;
	frameWidth = 16;
	frameHeight = 16;
	animationColumns = 4;
	animationDirection = 1;
	score = 0;
	b = new Bullet[2];

	for(int i=0;i<2;i++)
		b[i].Init();
}

void Player::Update(bool *keys)
{
	if (!live)
		return;
	int width = 320;
	int height = 240;
	
	if (keys[Keyboard::SPACE])	// go to the left
	{
		space_clicked = true;
	}
	else if(space_clicked && !keys[Keyboard::SPACE])
	{
		space_clicked = false;
		for(int i=0;i<2;i++)
		{
			if(!b[i].live && !b[i].show)
			{
				b[i].Shoot(x, y, dirX);
				break;
			}
		}
	}
	if (keys[Keyboard::LEFT])	// go to the left
	{
		dirX = -1;
		velX = 1;
	}
	else if (keys[Keyboard::RIGHT]) // go to the right
	{
		dirX = 1;
		velX = 1;
	}

	if (keys[Keyboard::UP] && (int)y % 16 == 0 && dirY == 1 && velY == 0)	// if player is on the ground and didn't jump yet
	{
		startFrame = 2;
		maxFrame = 3;
		curFrame = 2;
		//al_play_sample(jump, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		al_play_sample_instance(jump);
		velY = 3.0;
		dirY = -1;
		if (Map::collided(this, 'y'))
		{
			velY = 0;
			dirY = 1;
		}
	}
	
	if ((keys[Keyboard::LEFT] || keys[Keyboard::RIGHT]) && !(Map::collided(this, 'x')) && x + 1 * dirX >= map->xOff) // horizontal moves
	{
		animation();
		x += velX * dirX;

		if (x - map->xOff > 16 * 8) // map moves
			map->update(keys);
	}
	else
	{
		velX = 0;
	}

	y += dirY * velY;

	if (velY == 0 && dirY == 1) // player is on the ground 
	{
		// start animation again
		startFrame = 0;
		maxFrame = 2;
		if (velX == 0)
			curFrame = 0;
	}

	if (velY <= 0 && dirY == -1) // start falling down
	{
		velY = 0;
		dirY = 1;
		if (map->destroyBrick(this) == 1) // break brick
		{
			al_play_sample_instance(breakBrick);
			//al_play_sample(breakBrick, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
			score += 100;	// add point
		}
	}

	
	
	if (!Map::collided(this, 'y'))
	{
		velY += dirY * 10.0 / 60.0;	
	}

	if (y >= height)
	{
		live = false;
		al_play_sample_instance(die);
		//al_play_sample(die, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
	}
	for(int i=0;i<2;i++)
	{
		b[i].Update();
	}

}

void Player::Draw()
{
	int fx = curFrame * frameWidth;
	int fy = 0;
	for(int i=0;i<2;i++)
	{
		b[i].Draw(map->xOff);
	}
	if (show)
	{
		int flag = 0;
		if (dirX == -1)
			flag = ALLEGRO_FLIP_HORIZONTAL;
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - map->xOff, y, flag);
	}
}

void Player::animation()
{
	if (++frameCount >= frameDelay)
	{
		curFrame += animationDirection;
		if (curFrame >= maxFrame )
			curFrame = startFrame;
		else if (curFrame <= startFrame)
			curFrame = maxFrame - 1;

		frameCount = 0;
	}
}