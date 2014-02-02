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
}


void Text::draw()
{
	al_draw_text(font, al_map_rgb(255, 255, 255), 3 * 15, 10, ALLEGRO_ALIGN_CENTRE, "MARIO");
	al_draw_text(font, al_map_rgb(255, 255, 255), 3 * 15, 25, ALLEGRO_ALIGN_CENTRE, name);
}

void Text::update(BaseCharacter *character)
{
	string player = "MARIO";
	int divisor = 100000;
	int temp = character->score;
	for (int i = 0; i < 6; i++)
	{
		name[i] = (char) (temp / divisor) + 48;
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
