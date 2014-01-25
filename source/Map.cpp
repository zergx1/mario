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
	if (character->dirX == 1)
		x += character->frameWidth;

		float yFloor = floor(y / mapblockwidth);
		float yCeil = ceil(y / mapblockwidth);
		x /= mapblockwidth;

		if (!outOfStage(x, yFloor) && !outOfStage(x, yCeil))
			return (MapGetBlock(x, yFloor)->tl || MapGetBlock(x, yCeil)->tl);
		
	}

	if (axis == 'y')
	{
		if (character->dirY == 1)
			y += character->frameHeight;
		float xFloor = floor(x / mapblockwidth);
		float xCeil = ceil(x / mapblockwidth);
		
		y /= mapblockheight;

		if (!outOfStage(xFloor, y) && !outOfStage(xCeil, y))
			return (MapGetBlock(xFloor, y)->tl || MapGetBlock(xCeil, y)->tl);
		
	}

	return 0;

}

int Map::outOfStage(int x, int y)
{
	if (x < 0 || x >= mapwidth)
		return 1;
	if (y < 0 || y >= mapheight)
		return 1;

	return 0;
}