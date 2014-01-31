#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#pragma once
#include "lib/mappy_A5.h"
#include "BaseCharacter.h"
#include "Item.h"

class Item;

class Map
{
	static const int BRICK = 49;
	static const int EMPTY = 44;
	static const int SOLID = 12; //  after destroy quote block
	static const int COIN = 232;
public:
	const char *MAP_PATH;
	ALLEGRO_DISPLAY_MODE disp_data;
	int xOff;
	
public:
	Map(void);
	~Map(void);
	int init(char *path);
	void del();
	void draw();
	void update(bool* keys);


	int destroyBrick(BaseCharacter* character);
	Item *item;
	static void takeCoin(BaseCharacter* character, int x, int y);
	static int collided(BaseCharacter* character, char axis);
	static int collided(int x, int y);
	static int outOfStage(int x, int y);
};

#endif