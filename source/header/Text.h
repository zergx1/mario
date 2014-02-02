#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "BaseCharacter.h"

class Text
{
private:
	ALLEGRO_FONT *font;
	char name[6];
	char* score;
	char* live;
	char* time;
	char* coin;
	char* level;
public:
	Text(void);
	~Text(void);
	float x;
	float y;
	
	int width;
	int height;

	void draw();
	void init();
	void update(BaseCharacter *character);
	

};



