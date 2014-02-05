#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#pragma once
#include "lib/mappy_A5.h"
#include "BaseCharacter.h"
#include "Item.h"

class Item;

class Map
{
public:
	const char *MAP_PATH;
	ALLEGRO_DISPLAY_MODE disp_data;
	Item *item;
	int checkpoints[4];
public:
	Map(void);
	~Map(void);
	int init(char *path);
	void del();
	void draw();
	void update(int x);
	int destroyBlock(BaseCharacter* character);
	void cleanInactiveAnim();
	static void takeCoin(BaseCharacter* character, int x, int y, int background);
	static int collided(BaseCharacter* character, char axis, int extraX = 0, int extraY = 0);
	static int collided(int x, int y);
	static int outOfStage(int x, int y);

};

#endif
