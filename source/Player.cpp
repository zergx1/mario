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
	win = false;

	normalVel0 = sqrt(settings.getIntOption("normal_jump") * 16 * 2 * 0.16);
	superVel0 = sqrt(settings.getIntOption("super_jump") * 16 * 2 * 0.16);

	pipeMoveState = NONE;
	pipeCounter = 0;

	incerdible=false; //if mario took star
	incerdileTime=900;
	currentIncredibleTime=0;
	this->map = map;
	this->lives = settings.getIntOption("mario_lives");
	this->x = 0;
	this->y = 12 * 16;
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

	inc_small_mario = al_load_bitmap("Sprites/inv_small_mario.png");
	inc_big_mario = al_load_bitmap("Sprites/inv_big_mario.png");
	inc_super_mario = al_load_bitmap("Sprites/inv_super_mario.png");

	al_convert_mask_to_alpha(small_mario, al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(big_mario, al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(super_mario, al_map_rgb(0, 0, 0));

	al_convert_mask_to_alpha(inc_small_mario, al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(inc_big_mario, al_map_rgb(0, 0, 0));
	al_convert_mask_to_alpha(inc_super_mario, al_map_rgb(0, 0, 0));
	image = small_mario;
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	show = true;
	dirX = 1;
	dirY = 1;

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
	bullets = new Bullet[2];

	for(int i=0;i<2;i++)
		bullets[i].Init();
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
	if(pipeMoveState == DOWN)
	{
		pipeCounter += 0.5;

		if(pipeCounter > frameHeight)
		{
			pipeMoveState = NONE;
			x = pipeMoveToX;
			y = pipeMoveToY;
			xOff = x;
			pipeCounter = 0;
		}
		return;

	}

	updateIncerdible();
	if (!oldKeys[Keyboard::ENTER] && keys[Keyboard::ENTER])	// go to the left
	{	
		//pipeMove(200*16,y-50, DOWN);
		//setIncerdible();
		//if (currentState == SMALL)
		//	changeStatus(BIG);
		//else if (currentState == BIG)
		//	changeStatus(SUPER);
		//else
		//	changeStatus(SMALL);
	}

	if (currentState == SUPER && !oldKeys[Keyboard::X] && keys[Keyboard::X])
	{
		for(int i=0;i<2;i++)
		{
				if(!bullets[i].live && !bullets[i].show)
				{
					bullets[i].Shoot(x, y, dirX);
					break;
				}
		}
	}

	if (keys[Keyboard::X])
	{
		velX = settings.getIntOption("x_mario_speed_super") * 0.26;
	}
	else
	{
		velX = settings.getIntOption("x_mario_speed_normal")  * 0.26;
	}

	if (keys[Keyboard::LEFT])	// go to the left
	{
		dirX = -1;
	}
	if (keys[Keyboard::RIGHT]) // go to the right
	{
		dirX = 1;
	}
	if (keys[Keyboard::DOWN]  && velY == 0) // go to the down
	{
		if( 27*16 < x  && x <27*16+32 && pipeMoveState == NONE)
		{
			pipeMove(201 *16, 0, DOWN);
		}
		else if(217*16 < x  && x <217*16+32 && pipeMoveState == NONE)
		{
			pipeMove(144*16, 32, DOWN);
		}

		if(currentState != SMALL)
		{
			curFrame = 4;
			Draw();
			return;
		}

	}

	if (!oldKeys[Keyboard::Z] && keys[Keyboard::Z] && (int)y % 16 == 0 && dirY == 1 && velY == 0)	// if player is on the ground and didn't jump yet
	{
		//std::cout << "Jump\n";
		jump = true;
		startFrame = 2;
		maxFrame = 3;
		curFrame = 2;
		velY = keys[Keyboard::X] ? superVel0 : normalVel0;
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
	
	if ((keys[Keyboard::LEFT] || keys[Keyboard::RIGHT]) && !(Map::collided(this, 'x')) && x + 1 * dirX >= xOff) // horizontal moves
	{
		animation();
		x += velX * dirX;
		std::cout << velX << "\n";
		if (x - xOff > 16 * settings.getIntOption("map_scrolling")) // map scrolling
			map->update(x);
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
		
		map->destroyBlock(this); 

	}

	if (!Map::collided(this, 'y'))
	{
		velY += dirY * settings.getIntOption("gravity") / 60.0;	 // gravity
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
		bullets[i].Update();
	}
	
	transformation();


	/*for (int i = 0; i < Keyboard::SIZE_KEYS; i++)
	{
		oldKeys[i] = keys[i];
	}*/
	oldKeys[Keyboard::Z] = keys[Keyboard::Z]; // i need to store only old up key value
	oldKeys[Keyboard::X] = keys[Keyboard::X]; // i need to store only old up key value
	oldKeys[Keyboard::ENTER] = keys[Keyboard::ENTER]; // i need to store only old up key value

}

void Player::Draw(int flag)
{
	int fx = curFrame * frameWidth;
	int fy = 0;
	float extraX=0;
	float extraY=0;
	for(int i=0;i<2;i++)
	{
		bullets[i].Draw(xOff);
	}
	if (show)
	{
		if(pipeMoveState == DOWN)
		{
			extraY = pipeCounter;
		}

		if (dirX == -1)
			flag = ALLEGRO_FLIP_HORIZONTAL;
		al_draw_bitmap_region(image, fx, fy, frameWidth, frameHeight-extraY, x - xOff, y+extraY, flag);
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
			x = xOff;
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

void Player::pipeMove(int toX, int toY, PIPE_MOVE from)
{
	pipeMoveToX = toX;
	pipeMoveToY = toY;
	pipeMoveState = from;
	Sound::play(Sound::PIPE);

}

void Player::collisionWithOther(BaseCharacter* character)
{
	// bullets
	bullets[0].collisionWithOther(character);
	bullets[1].collisionWithOther(character);
	if (character->live)
	{

		float myXLEFT = x;
		float myYTOP = y;
		float myXRIGHT = x + frameWidth;
		float myYBOTTOM = y + frameHeight;

		float xLEFT = character->x+ character->marginX;
		float yTOP = character->y + character->marginY;
		float xRIGHT = character->x + character->frameWidth - character->marginX;
		float yBOTTOM = character->y + character->frameHeight - character->marginY;

		bool horizontal = (xLEFT >= myXLEFT && xLEFT <= myXRIGHT) || (xRIGHT >= myXLEFT && xRIGHT <= myXRIGHT);
		bool vertical = (yTOP >= myYTOP && yTOP <= myYBOTTOM) || (yBOTTOM >= myYTOP && yBOTTOM <= myYBOTTOM);
		if (horizontal && vertical && !blinking)
		{
			if(incerdible && this->live)
			{
				character->KillByShot();
				score += character->score;
				//globalText.floatingScore(character->x, character->y, character->score);
			}
			else if (velY > 0 && this->live && character->killableByJump)
			{
				character->Hit();
				velY = 3;
				dirY = -1;
				if(!character->live)
				{
					score += character->score;
					globalText.floatingScore(character->x, character->y, character->score);
				}
			}
			else
			{
				if(character->CheckIfKillPlayer(this))
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
}

void Player::setIncerdible()
{
	incerdible = true;
	currentIncredibleTime = 0;
	Sound::play(Sound::POWER_APPEARS);

}

void Player::updateIncerdible()
{
	ALLEGRO_BITMAP *norm = NULL;
	ALLEGRO_BITMAP *inc = NULL;
	if(incerdible && currentIncredibleTime++ < incerdileTime)
	{
		switch(currentState)
		{
		case SMALL:
			norm = small_mario;
			inc = inc_small_mario;
			break;
		case BIG:
			norm = big_mario;
			inc = inc_big_mario;
			break;
		case SUPER:
			norm = super_mario;
			inc = inc_super_mario;
			break;
		}
		if(currentIncredibleTime % 10 == 0)
		{
			if(image == norm)
				image = inc;
			else
				image = norm;
		}
		if(currentIncredibleTime+1 >= incerdileTime)
		{
			incerdible =  false;
			image = norm;
			currentIncredibleTime = 0;
		}

	}


}


void Player::takeItem(BaseCharacter* character)
{
	//stageClear();
	globalText.floatingScore(character->x, character->y, character->score);
	score += character->score;
	if( dynamic_cast<Item*>(character)->type == GREEN_MUSHROOM)
	{
		live++;
		Sound::play(Sound::POWER_UP);
	}
	else if(dynamic_cast<Item*>(character)->type == STAR)
	{
		setIncerdible();
	}
	else if (currentState != 2)
		changeStatus(++currentState);
	else
		Sound::play(Sound::POWER_UP);
}

void Player::stageClear()
{
	Sound::play(Sound::WIN);
	globalText.reset = true;
	win = true;
}