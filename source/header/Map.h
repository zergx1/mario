#pragma once
#include "BaseCharacter.h"

class Map
{
private:
	//const char *MAP_PATH = "Maps/level.fmp";
	//const short TILE_WIDTH = 16;
	//const short TILE_HEIGHT = 16;
	//const  short MAP_WIDTH = 200;
	//const short MAP_HEIGHT = 15;

	//short** mapMatrix;

public:
	Map(void);
	~Map(void);
	void init();
	bool isFallingDown(BaseCharacter character);
};

