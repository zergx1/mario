#pragma once
#include "lib/mappy_A5.h"
#include "BaseCharacter.h"

class Map
{
public:
	const char *MAP_PATH;
	ALLEGRO_DISPLAY_MODE disp_data;
	int xOff;
	int yOff;

public:
	Map(void);
	~Map(void);
	int init(char *path);
	void del();
	void draw();
	void update(bool* keys);
	static int collided(BaseCharacter* character, char axis);
};

