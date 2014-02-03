#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "BaseCharacter.h"

class BaseCharacter;

class Text
{
private:
	ALLEGRO_BITMAP *image;
	ALLEGRO_FONT *font;

	int startFrame;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;

	int frameWidth;
	int frameHeight;
	int counter;
	int counterTemp;

	char* name;
	char score[7];
	char coin[4];
	char live;
	char time[4];
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

#endif

