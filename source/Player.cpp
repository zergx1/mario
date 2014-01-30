#include "header/Player.h"
#include "header/Sound.h"
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
	this->map = map;
	this->lives = 3;
	this->x = 0;
	this->y = 0;
	this->live = true;
	this->jump = false;
	this->canTakeCoin = true;

	for (int i = 0; i < Keyboard::SIZE_KEYS; i++)
	{
		oldKeys[i] = false;
	}

	image = al_load_bitmap("Sprites/small_mario.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

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
}

void Player::Update(bool keys[])
{
	bool brick = false;
	if (!live)
		return;
	int width = 320;
	int height = 240;
	

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

	if (!oldKeys[Keyboard::UP] && keys[Keyboard::UP] && (int)y % 16 == 0 && dirY == 1 && velY == 0)	// if player is on the ground and didn't jump yet
	{
		std::cout << "Jump bitch\n";
		jump = true;
		startFrame = 2;
		maxFrame = 3;
		curFrame = 2;
		velY = 5.0;
		dirY = -1;
		if (Map::collided(this, 'y'))
		{
			velY = 0;
			dirY = 1;
			brick = true;
		}
		else
		{
		Sound::play(Sound::JUMP);
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

	if (velY == 0 && dirY == 1 && !jump) // player is on the ground 
	{
		std::cout << "Ground\n";

		// start animation again
		startFrame = 0;
		maxFrame = 2;
		if (velX == 0)
			curFrame = 0;
	}

	if (velY <= 0 && dirY == -1 || brick) // start falling down
	{
		std::cout << "Start falling down\n";
		velY = 0;
		dirY = 1;
		if (map->destroyBrick(this) == 1) // break brick
		{
			Sound::play(Sound::BREAK_BRICK);
			score += 100;	// add point
		}
	}

	
	
	if (!Map::collided(this, 'y'))
	{
		velY += dirY * 10.0 / 60.0;	 // gravity
	}
	else
	{
		jump = false;
	}

	if (y >= height)
	{
		live = false;
		Sound::play(Sound::MARIO_DIE);
	}

	/*for (int i = 0; i < Keyboard::SIZE_KEYS; i++)
	{
		oldKeys[i] = keys[i];
	}*/
	oldKeys[Keyboard::UP] = keys[Keyboard::UP]; // i need to store only old up key value
}

void Player::Draw()
{
	int fx = curFrame * frameWidth;
	int fy = 0;

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

void Player::takeCoin()
{
	score += 100;
	Sound::play(Sound::COIN);
}