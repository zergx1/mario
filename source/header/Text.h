#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "BaseCharacter.h"

class Text
{
private:
	ALLEGRO_FONT *font;
	ALLEGRO_BITMAP *image;

	int startFrame;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;

	int frameWidth;
	int frameHeight;

	char name[6];
	char score[6];
	char live;
	char* time;
	char coin[3];
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



