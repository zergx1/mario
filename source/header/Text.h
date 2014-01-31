#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "BaseCharacter.h"

class Text
{
private:
	ALLEGRO_FONT *font;
public:
	Text(void);
	~Text(void);
	float x;
	float y;
	
	int width;
	int height;

	void draw(BaseCharacter *character);
	void init();
	

};



