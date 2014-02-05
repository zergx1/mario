#include "header/Map.h"
#include <iostream>
#include <cmath>
#include <allegro5/allegro_native_dialog.h>
#include "header/Keyboard.h"
#include "header/Sound.h"
#include "header/GlobalObjects.h"

Map::Map(void)
{
}


Map::~Map(void)
{
	
}

int Map::init(char *path)
{
	this->MAP_PATH = path;
	al_get_display_mode(1, &disp_data);
	std::cout << disp_data.height << std::endl << disp_data.width;
	int status = MapLoad(path, true);
	if (status)
	{
		al_show_native_message_box(al_get_current_display(), "Critical error", "", "Given map doesn't exist", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -5;
	}
	xOff = 0;
	//xOff = 200 * 16 - 360;
	item = new Item();
	srand(time(0));  

	return status;

}

void Map::del()
{
	MapFreeMem();
}

void Map::draw()
{
	MapUpdateAnims();
	MapDrawBG(xOff, 0, 0, 0, disp_data.width, mapheight * mapblockheight);
}

void Map::update(int x)
{
	xOff = x - 16 * settings.getIntOption("map_scrolling");

	if (xOff >(mapwidth*mapblockwidth - disp_data.width))
		xOff = mapwidth*mapblockwidth - disp_data.width;
	if (x >= 200 * 16 - disp_data.width && xOff >= 200 * 16 - disp_data.width)
		xOff = 200 * 16 - disp_data.width;

}

int Map::collided(BaseCharacter* character, char axis, int extraX, int extraY)
{
	BLKSTR *blockdata;
	BLKSTR *blockdata2;
	float x = character->x + extraX*character->dirX;
	float y = character->y + extraY;
	
	if (axis == 'x')
	{
		x += character->dirX * character->velX;
		if (character->dirX == 1)
			x += character->frameWidth;

		float yBOTTOM = (y + character->frameHeight - 1) / mapblockheight;	//floor(y / mapblockheight);
		float yTOP = y / mapblockheight;	// ceil(y / mapblockwidth);
		x /= mapblockwidth;
		//std::cout << yBOTTOM << " " << yTOP << "\n";
		if (!outOfStage(x, yBOTTOM) && !outOfStage(x, yTOP))
		{
			blockdata = MapGetBlock(x, yBOTTOM);
			blockdata2 = MapGetBlock(x, yTOP);
			if (blockdata->user1 == COIN_ID)
				takeCoin(character, x, yBOTTOM, blockdata->user2);
			if (blockdata2->user1 == COIN_ID)
				takeCoin(character, x, yTOP, blockdata2->user2);
			bool collided = (blockdata->tl || blockdata2->tl);
			int characterX = character->x + character->dirX * character->velX;
			if (collided == 1 && (characterX % 16 != 0))
			{
				character->x = characterX;
				if (character->dirX == 1)	// adjustment to title 
					character->x -= ((int)character->x % 16);
				else
					character->x += 16 - ((int)character->x % 16);

			}
			return collided;
		}
	}

	if (axis == 'y')
	{
		y += character->dirY * character->velY;
		if (character->dirY == 1)
			y += character->frameHeight;

		float xRIGHT = (x + character->frameWidth - 1) / mapblockwidth;
		float xLEFT = x / mapblockwidth;
		//std::cout << xLEFT << " " << xRIGHT << "\n";
		y /= mapblockheight;

		if (!outOfStage(xLEFT, y) && !outOfStage(xRIGHT, y))
		{
			blockdata = MapGetBlock(xLEFT, y);
			blockdata2 = MapGetBlock(xRIGHT, y);
			if (blockdata->user1 == COIN_ID)
				takeCoin(character, xLEFT, y, blockdata->user2);
			if (blockdata2->user1 == COIN_ID)
				takeCoin(character, xRIGHT, y, blockdata2->user2);
			bool collided = blockdata->tl || blockdata2->tl;
			int characterY = character->y + character->dirY * character->velY;
		
			if (collided)
			{
				character->y = characterY;
				if (character->dirY == 1)	// adjustment to title 
					character->y -= ((int)character->y % 16);
				else
					character->y += 16 - ((int)character->y % 16);

				character->velY = 0;
				
			}
			return collided;
		}
		
	}

	return 0;

}

int Map::collided(int x, int y)
{
	std::cout << x / mapblockwidth << " " << y / mapblockheight;
	BLKSTR *blockdata;
	blockdata = MapGetBlock(x / mapblockwidth, y / mapblockheight);
	return blockdata->tl;
}

int Map::outOfStage(int x, int y)
{
	if (x < 0 || x >= mapwidth)
		return 1;
	if (y < 0 || y >= mapheight)
		return 1;

	return 0;
}

int Map::destroyBlock(BaseCharacter* character)
{
	int x = character->x + character->frameWidth / 2;
	int y = character->y - 1;
	
	if (y < 0 || y >= mapblockheight * mapheight) // out of the map
		return 0;

	BLKSTR *blockdata;
	blockdata = MapGetBlockInPixels(x, y);
	// character->y - 1 because this function is calling when mario reach the highest point and start falling down
	// alse he is adjusted to the bottom line of the block, so we need to check one block higher then mario is.
	if (blockdata->user1 == BRICK_ID || blockdata->user1 == BRICK_DARK_ID)  // brick
	{
		character->y -= 8; // a little bit more up
		if (character->currentState != SMALL)
		{
			DestroyBrickAnimation anim;
			anim.Init(x / 16 * 16, y / 16 * 16, blockdata);
			destroyBrickAnimation.push_back(anim);
			MapSetBlockInPixels(x, y, blockdata->user2);	// color of background
			character->score += 50;
			Sound::play(Sound::BREAK_BRICK);
		}
		else
		{
			Sound::play(Sound::BUMP);
			BumpingBlockAnimation anim;
			anim.Init(x / 16 * 16, y / 16 * 16, blockdata);
			bumpingBlockAnimation.push_back(anim);
		}

		cleanInactiveAnim();
		
		return BRICK_ID;
	}
	if (blockdata->user1 == QUESTION_ID)
	{
		int choice;
		choice = rand() % 100;
		if(choice <= 20)
		{
			if(character->currentState == 0)
				item->Init(x / 16 * 16, y-16, MUSHROOM);
			else
				item->Init(x / 16 * 16, y - 16, FLOWER);
		}
		else if(choice > 20 && choice < 90)
		{
			character->takeCoin();
			JumpingCoinAnimation anim;
			anim.Init(x / 16 * 16, y / 16 * 16, blockdata);
			jumpingCoinAnimation.push_back(anim);
			character->score += 200;
		}
		else
			item->Init(x / 16 * 16, y-16, STAR);


		item->LeaveBox();
		Sound::play(Sound::BUMP);
		BumpingBlockAnimation anim;
		anim.Init(x / 16 * 16, y / 16 * 16, blockdata);
		bumpingBlockAnimation.push_back(anim);
		return QUESTION_ID;
	}
	return 0;
}

void Map::takeCoin(BaseCharacter* character, int x, int y, int background)
{
	if (character->canTakeCoin)
	{
		MapSetBlock(x, y, background);
		character->takeCoin();	
	}
}

void Map::cleanInactiveAnim()
{
	for (int v = 0; v < bumpingBlockAnimation.size(); v++)
	{
		if (!bumpingBlockAnimation[v].active)
		{
			bumpingBlockAnimation.erase(bumpingBlockAnimation.begin() + v);
			v--;
		}
	}
	for (int v = 0; v < destroyBrickAnimation.size(); v++)
	{
		if (!destroyBrickAnimation[v].active)
		{
			destroyBrickAnimation.erase(destroyBrickAnimation.begin() + v);
			v--;
		}
	}

	for (int v = 0; v < jumpingCoinAnimation.size(); v++)
	{
		if (!jumpingCoinAnimation[v].active)
		{
			jumpingCoinAnimation.erase(jumpingCoinAnimation.begin() + v);
			v--;
		}
	}
}
