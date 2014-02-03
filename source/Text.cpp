#include "header\Text.h"
#include <stdlib.h>
#include <iostream>
#include <string>
using std::string;
Text::Text(void)
{
}

void Text::init()
{
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	font = al_load_ttf_font("Fonts/arial.ttf", 15, 0);

	image = al_load_bitmap("Sprites/timer.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	startFrame = 0;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 30;
	frameWidth = 16;
	frameHeight = 16;
}


void Text::draw()
{
	int x = 0;
	int row1 = 10;
	int row2 = 25;
	al_draw_text(font, al_map_rgb(255, 255, 255), x += 3 * 15, row1, ALLEGRO_ALIGN_CENTRE, "MARIO");
	al_draw_text(font, al_map_rgb(255, 255, 255), 3 * 15, row2, ALLEGRO_ALIGN_CENTRE, score);

	int fx = curFrame * frameWidth;
	al_draw_bitmap_region(image, fx, 0, frameWidth, frameHeight, x += 70, row2 - 3, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), x += 30, row2, ALLEGRO_ALIGN_CENTRE, coin);

	al_draw_text(font, al_map_rgb(255, 255, 255), x += 60, row1, ALLEGRO_ALIGN_CENTRE, "WORLD");
	al_draw_text(font, al_map_rgb(255, 255, 255), x, row2, ALLEGRO_ALIGN_CENTRE, "1-1");

	al_draw_text(font, al_map_rgb(255, 255, 255), x += 80, row1, ALLEGRO_ALIGN_CENTRE, "TIME");
	al_draw_text(font, al_map_rgb(255, 255, 255), x, row2, ALLEGRO_ALIGN_CENTRE, "xxx");
	
}

void Text::update(BaseCharacter *character)
{
	// animation
	if (++frameCount >= frameDelay)
	{

		curFrame += 1;
		if (curFrame >= maxFrame)
			curFrame = startFrame;

		frameCount = 0;
	}

	string player = "MARIO";

	// SCORE
	int divisor = 100000;
	int temp = character->score;
	for (int i = 0; i < 6; i++)
	{
		score[i] = (char)(temp / divisor) + 48;
		if (temp / divisor != 0)
			temp %= divisor;
		divisor /= 10;
	}

	// COINS
	divisor = 10;
	temp = character->coins;
	coin[0] = 'x';
	for (int i = 1; i < 3; i++)
	{
		//std::cout << temp << " " << divisor << "\n";
		coin[i] = (char)(temp / divisor) + 48;
		if (temp / divisor != 0)
			temp %= divisor;
		divisor /= 10;
	}
	/*std::string s = std::to_string(character->score);
	strncpy(name, s.c_str(), sizeof(name));
	name[sizeof(name)-1] = 0;*/


}

Text::~Text(void)
{
}
