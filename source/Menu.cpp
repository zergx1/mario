#include "header\Menu.h"
#include "header/Keyboard.h"
#include <iostream>
Menu::Menu(void)
{
}


void Menu::init()
{

	//state = MENU;
	state = INFO;
	ALLEGRO_BITMAP *title = NULL;
	title = al_load_bitmap("menu.png");

	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *mgImage = NULL;
	ALLEGRO_BITMAP *fgImage = NULL;
	current = 0;
	currentInfoTime = 0;
	infoTime = 2000;
	down_clicked = false;
	up_clicked = false;
	bgImage = al_load_bitmap("background.png");
	mgImage = al_load_bitmap("starMG.png");
	fgImage = al_load_bitmap("menu.png");
	ALLEGRO_DISPLAY_MODE   disp_data;
	al_get_display_mode(0, &disp_data);
	int h = al_get_bitmap_height(bgImage);
	int mh = al_get_bitmap_height(mgImage);

	//display = al_create_display(disp_data.width, disp_data.height);
	Background BG, MG, FG;
	M.init(0, disp_data.height - h-mh, 0.5, 0, al_get_bitmap_width(mgImage), 1600, -1, 1, mgImage);
	B.init(0, disp_data.height - h, 0, 0, disp_data.width, disp_data.height, -1, 1, bgImage);

	menu1 = al_load_bitmap("menu.png");
	menu2 = al_load_bitmap("menu2.png");
	menu3 = al_load_bitmap("menu3.png");
	al_convert_mask_to_alpha(menu1, al_map_rgb(40, 123, 241));
	al_convert_mask_to_alpha(menu2, al_map_rgb(40, 123, 241));
	al_convert_mask_to_alpha(menu3, al_map_rgb(40, 123, 241));

	//G.init(0, 0, 5, 0, 800, 600, -1, 1, fgImage);
	image = menu1;
	al_convert_mask_to_alpha(image, al_map_rgb(40, 123, 241));

	theme_song = al_load_sample("Audio/menu_music.ogg");
	on_change = al_load_sample("Audio/on_change.ogg");

	songInstance = al_create_sample_instance(theme_song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	al_play_sample_instance(songInstance);

}

void Menu::setState(int state)
{

}

void Menu::update(bool *keys)
{

	if(keys[Keyboard::DOWN])
	{
		down_clicked = true;
	}
	else if(!keys[Keyboard::DOWN] && down_clicked)
	{
		al_play_sample(on_change, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

		down_clicked = false;
		current += 1;
		if(current > 2)
			current = 0;
		//state = GAME;
	}
	if(keys[Keyboard::UP])
	{
		up_clicked = true;
		//state = GAME;
	}
	else if(!keys[Keyboard::UP] && up_clicked)
	{
		al_play_sample(on_change, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);

		up_clicked = false;
		current -= 1;
		if(current < 0)
			current = 2;
	}
	if(keys[Keyboard::ENTER])
	{
		switch(current)
		{
		case 0:
			state = GAME; break;
		case 1:
			state = GAME; break;
		case 2:
			state = END; break;
		}
	}
	switch(current)
	{
	case 0:
		image = menu1; break;
	case 1:
		image = menu2; break;
	case 2:
		image = menu3; break;
	}
	//al_rest(1);


}

void Menu::updateBackgrounds()
{
	M.UpdateBackground();

	B.UpdateBackground();
		//G.UpdateBackground();

}

void Menu::drawBackgrounds()
{
	M.DrawBackground();
	B.DrawBackground();
	ALLEGRO_DISPLAY_MODE   disp_data;
	al_get_display_mode(1, &disp_data);
	int h = al_get_bitmap_height(image);
	int w = al_get_bitmap_width(image);

	al_get_display_mode(1, &disp_data);
	al_draw_bitmap(image, disp_data.width/2-w/2, disp_data.height/2-h/2, 0);

	//G.DrawBackground();
}

void Menu::drawInfo(Player p)
{

	

}

Menu::~Menu(void)
{
}
