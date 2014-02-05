#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "BaseCharacter.h"
#include <vector>

using std::vector;

class BaseCharacter;

struct FloatingTextStruct{
	int x, y, counter;
	char * score;
};
class Text
{
private:
	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *mario_image;

	ALLEGRO_FONT *font;
	int startFrame;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;

	int frameWidth;
	int frameHeight;
	int counterTemp;

	char* name;
	char score[7];
	char coin[4];
	char live[2];
	char time[4];
	char* level;
	vector<FloatingTextStruct> vecFloatingText;

public:
	bool reset;
	int counter;
	Text(void);
	~Text(void);
	float x;
	float y;
	
	int width;
	int height;

	void draw(bool world_info=false);
	void init();
	void update(BaseCharacter *character, bool world_info=false);
	void Text::floatingScore(int x, int y, char *score);
	void Text::floatingScore(int x, int y, int score);

};
