#include "header/Map.h"
#include <iostream>
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
	return status;
}

void Map::del()
{
	MapFreeMem();
}

void Map::draw()
{
	MapDrawBG(this->xOff, this->yOff, 0, 0, disp_data.width, disp_data.height);
}

void Map::update(bool *keys)
{
	xOff += keys[Keyboard::RIGHT] * 10;
	xOff -= keys[Keyboard::LEFT] * 10;
	yOff += keys[Keyboard::DOWN] * 10;
	yOff -= keys[Keyboard::UP] * 10;

	if (xOff < 0)
		xOff = 0;
	if (yOff < 0)
		yOff = 0;
	if (xOff >(mapwidth*mapblockwidth - disp_data.width))
		xOff = mapwidth*mapblockwidth - disp_data.width;
	if (yOff > mapheight*mapblockheight - disp_data.height)
		yOff = mapheight*mapblockheight - disp_data.height;

	this->xOff = xOff;
	this->yOff = yOff;
}

int Map::collided(BaseCharacter* character, char axis)
{
	BLKSTR *blockdata;
	float x = character->x;
	float y = character->y;

	if (character->dirX == 1 && axis == 'x')
		x += character->frameWidth;

	if (character->dirY == 1 && axis == 'y')
		y += character->frameHeight;
	
	x /= mapblockwidth;
	y /= mapblockheight;

	blockdata = MapGetBlock(x, y);

	return blockdata->tl;
}