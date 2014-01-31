#include "header\Text.h"
#include "header/Keyboard.h"
#include <iostream>
Text::Text(void)
{
}

void Text::init()
{
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	font = al_load_ttf_font("Fonts/arial.ttf", 15, 0);
}


void Text::draw(BaseCharacter *character)
{
	al_draw_text(font, al_map_rgb(255, 255, 255), 3 * 15, 10, ALLEGRO_ALIGN_CENTRE, "MARIO");
	//al_draw_text(font, al_map_rgb(255, 255, 255), 10, 25, ALLEGRO_ALIGN_CENTRE, character->score);
}


Text::~Text(void)
{
}
