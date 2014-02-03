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
	BaseCharacter::Init();
	name = new char[6];
	name = "MARIO\0";
	space_clicked = false;
	currentState = SMALL;
	blinking_time = 60;
	current_blinking_time = 0;
	blinking = false;
	invisible = false;

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
	small_mario = al_load_bitmap("Sprites/small_mario.png");
	big_mario = al_load_bitmap("Sprites/big_mario.png");
	super_mario = al_load_bitmap("Sprites/super_mario.png");

	al_convert_mask_to_alpha(small_mario, al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(big_mario, al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(super_mario, al_map_rgb(0, 0, 0));

	image = small_mario;
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
	coins = 0;
	b = new Bullet[2];

	for(int i=0;i<2;i++)
		b[i].Init();
}

void Player::Update(bool keys[])
{
	bool brick = false;
	if (!live)
	{
		Kill();
		return;
	}
	int width = 320;
	int height = 240;
	
	if (!oldKeys[Keyboard::ENTER] && keys[Keyboard::ENTER])	// go to the left
	{	
		if (currentState == SMALL)
			changeStatus(BIG);
		else if (currentState == BIG)
			changeStatus(SUPER);
		else
			changeStatus(SMALL);
	}
	else if (!oldKeys[Keyboard::SPACE] && keys[Keyboard::SPACE])
	{
		for(int i=0;i<2;i++)
		{
			if(image == super_mario)
			{
				if(!b[i].live && !b[i].show)
				{
					b[i].Shoot(x, y, dirX);
					break;
				}
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
	else if (keys[Keyboard::DOWN] && currentState != SMALL) // go to the down
	{
		//std::cout << "DOWN\n";
		curFrame = 4;
		Draw();
		return;

	}

	if (!oldKeys[Keyboard::UP] && keys[Keyboard::UP] && (int)y % 16 == 0 && dirY == 1 && velY == 0)	// if player is on the ground and didn't jump yet
	{
		//std::cout << "Jump bitch\n";
		jump = true;
		startFrame = 2;
		maxFrame = 3;
		curFrame = 2;
		velY = 4.8;
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
		//std::cout << "Ground\n";

		// start animation again
		startFrame = 0;
		maxFrame = 2;
		if (velX == 0)
			curFrame = 0;
	}

	if (velY <= 0 && dirY == -1 || brick) // start falling down
	{
		//std::cout << "Start falling down\n";
		velY = 0;
		dirY = 1;
		if (map->destroyBrick(this) == BRICK_ID) // break brick
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

	if (y > height + frameHeight)
	{
		Kill();
	}

	for(int i=0;i<2;i++)
	{
		b[i].Update();
	}
	
	transformation();
	/*for (int i = 0; i < Keyboard::SIZE_KEYS; i++)
	{
		oldKeys[i] = keys[i];
	}*/
	oldKeys[Keyboard::UP] = keys[Keyboard::UP]; // i need to store only old up key value
	oldKeys[Keyboard::SPACE] = keys[Keyboard::SPACE]; // i need to store only old up key value
	oldKeys[Keyboard::ENTER] = keys[Keyboard::ENTER]; // i need to store only old up key value

}

void Player::Draw(int flag)
{
	int fx = curFrame * frameWidth;
	int fy = 0;
	for(int i=0;i<2;i++)
	{
		b[i].Draw(map->xOff);
	}
	if (show)
	{
		if (dirX == -1)
			flag = ALLEGRO_FLIP_HORIZONTAL;
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight, x - map->xOff, y, flag);
	}
}

void Player::Kill()
{
	if (live)
	{
		Sound::play(Sound::MARIO_DIE);
		dirY = -1;
		velY = 3;
		lives--;
		live = false;
		startFrame = 3;
		maxFrame = 4;
		curFrame = 3;
	}
	else
	{
		if (y <= 240 + frameHeight)
		{
			velY += dirY * 10.0 / 60.0;	 // gravity
			if (velY <= 0)
				dirY = 1;
			y += dirY * velY;
		}
		else
		{
			changeStatus(SMALL);
			x = map->xOff;
			y = 0;
			live = true;
			startFrame = 0;
			maxFrame = 2;
			curFrame = 0;
			//al_rest(2);
		}

	}

}
void Player::changeStatus(int s)
{
	if (s < 0 || s > 2)
		s = 0;
	currentState = s;
	blinking = true;
	if (currentState == SMALL)
	{
		image = small_mario;
		frameHeight = 16;
		Sound::play(Sound::POWER_DOWN);

	}
	else if (currentState == BIG)
	{
		image = big_mario;
		frameHeight = 32;
		y -= 16;
		Sound::play(Sound::POWER_UP);
	}
	else if (currentState == SUPER)
	{
		image = super_mario;
		frameHeight = 32;
		//y -= 16;
		Sound::play(Sound::POWER_UP);
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
	//std::cout << "Take coin \n";
	coins++;
	Sound::play(Sound::COIN);
	if (coins == 100)
	{
		coins = 0;
		lives++;
		Sound::play(Sound::GAIN_LIFE);
	}
}

void Player::transformation()
{
	if (blinking)
	{
		if (current_blinking_time++ >= blinking_time)
		{
			blinking = false;
			current_blinking_time = 0;
			if (currentState == SMALL)
			{
				image = small_mario;
				frameHeight = 16;
				//y += 16;
			}
			else if (currentState == BIG)
			{
				image = big_mario;
				frameHeight = 32;
				//y -= 16;
			}
			else if (currentState == SUPER)
			{
				image = super_mario;
				frameHeight = 32;
			}
		}
		else
		{
			//if(timeToClear/(deathBlinks - currentdeathBlinks) <= currentTimeToClear  )
			if (current_blinking_time % 10 == 0)
			{
				if (currentState == SUPER)
				{
					if (image == big_mario)
					{
						image = super_mario;
					}
					else
						image = big_mario;
				}
				else
				{

					if (image == small_mario)
					{
						image = big_mario;
						frameHeight = 32;
						y -= 16;
					}
					else
					{
						image = small_mario;
						frameHeight = 16;
						y += 16;

					}
				}

			}
		}
	}
}

void Player::collisionWithOther(BaseCharacter* character)
{
	// bullets
	b[0].collisionWithOther(character);
	b[1].collisionWithOther(character);
	if (character->live)
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
		if (horizontal && vertical && !blinking)
		{
			if (velY > 0 && this->live)
			{
				character->Kill();
				velY = 2;
				dirY = -1;
			}
			else
			{
				if (currentState == SMALL)
				{
					this->Kill();
				}
				else
				{
					currentState--;
					changeStatus(currentState);
				}
			}
		}
	}
}

void Player::takeItem()
{
	score += 1000;
	if (currentState != 2)
		changeStatus(++currentState);
	else
		Sound::play(Sound::POWER_UP);
}