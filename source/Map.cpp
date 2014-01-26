#include "header/Map.h"
#include <iostream>
#include <cmath>
#include <allegro5/allegro_native_dialog.h>
#include "header/Keyboard.h"

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
	int status = MapLoad(path, 1);
	if (status)
	{
		al_show_native_message_box(al_get_current_display(), "Critical error", "", "Given map doesn't exist", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -5;
	}
	xOff = 0;
	return status;
}

void Map::del()
{
	MapFreeMem();
}

void Map::draw()
{
	MapDrawBG(this->xOff, 0, 0, 0, disp_data.width, mapheight * mapblockheight);
}

void Map::update(bool *keys)
{
	xOff += keys[Keyboard::RIGHT];

	if (xOff < 0)
		xOff = 0;
	if (xOff >(mapwidth*mapblockwidth - disp_data.width))
		xOff = mapwidth*mapblockwidth - disp_data.width;

}

int Map::collided(BaseCharacter* character, char axis)
{
	BLKSTR *blockdata;
	float x = character->x;
	float y = character->y;
	
	if (axis == 'x')
	{
		x += character->dirX * character->velX;
		if (character->dirX == 1)
			x += character->frameWidth;

		float yFloor = floor(y / mapblockwidth);
		float yCeil = ceil(y / mapblockwidth);
		x /= mapblockwidth;

		if (!outOfStage(x, yFloor) && !outOfStage(x, yCeil))
		{
			bool result = (MapGetBlock(x, yFloor)->tl || MapGetBlock(x, yCeil)->tl);
			int characterX = character->x + character->dirX * character->velX;
			if (result == 1 && (characterX % 16 != 0))
			{
				character->x = characterX;
				if (character->dirX == 1)	// adjustment to title 
					character->x -= ((int)character->x % 16);
				else
					character->x += 16 - ((int)character->x % 16);

			}
			return result;
		}
	}

	if (axis == 'y')
	{
		y += character->dirY * character->velY;
		if (character->dirY == 1)
			y += character->frameHeight;

		float xFloor = floor(x / mapblockwidth);
		float xCeil = ceil(x / mapblockwidth);
		
		y /= mapblockheight;

		if (!outOfStage(xFloor, y) && !outOfStage(xCeil, y))
		{
			bool result = MapGetBlock(xFloor, y)->tl || MapGetBlock(xCeil, y)->tl;
			int characterY = character->y + character->dirY * character->velY;
		
			if (result)
			{
				character->y = characterY;
				if (character->dirY == 1)	// adjustment to title 
					character->y -= ((int)character->y % 16);
				else
					character->y += 16 - ((int)character->y % 16);

				character->velY = 0;
				
			}
			return result;
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

int Map::destroyBrick(BaseCharacter* character)
{
	int x = character->x + character->frameWidth / 2;
	int y = character->y - 1;
	
	if (y < 0 || y >= mapblockheight * mapheight) // out of the map
		return 0;

	BLKSTR *blockdata;
	blockdata = MapGetBlockInPixels(x, y);
	// character->y - 1 because this function is calling when mario reach the highest point and start falling down
	// alse he is adjusted to the bottom line of the block, so we need to check one block higher then mario is.
	if (blockdata->user1 == 1) 
	{
		MapSetBlockInPixels(x, y, Map::EMPTY);
		return 1;
	}
	return 0;
}