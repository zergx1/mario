#include "header\Menu.h"
#include "header/Keyboard.h"
#include <iostream>
Menu::Menu(void)
{
}


void Menu::init()
{
	state = MENU;
	//state = GAME;
	ALLEGRO_BITMAP *title = NULL;
	title = al_load_bitmap("menu.png");

	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *mgImage = NULL;
	ALLEGRO_BITMAP *fgImage = NULL;

	numberOfPlayers = 0;
	current = 0;
	currentInfoTime = 0;
	infoTime = 1 * 60;
	down_clicked = false;
	up_clicked = false;
	p_clicked = false;
	bgImage = al_load_bitmap("background.png");
	mgImage = al_load_bitmap("starMG.png");
	fgImage = al_load_bitmap("menu.png");

	int h = al_get_bitmap_height(bgImage);
	int mh = al_get_bitmap_height(mgImage);

	//display = al_create_display(disp_data.width, disp_data.height);
	Background BG, MG, FG;
	M.init(0, 0, 0.5, 0, WIDTH, 1600, -1, 1, mgImage);
	B.init(0, HEIGHT - h, 0, 0, WIDTH, HEIGHT, -1, 1, bgImage);
	//pause_bg.init(0, 
	menu1 = al_load_bitmap("menu.png");
	menu2 = al_load_bitmap("menu2.png");
	menu3 = al_load_bitmap("menu3.png");
	pause_img = al_load_bitmap("pause.png");

	al_convert_mask_to_alpha(menu1, al_map_rgb(40, 123, 241));
	al_convert_mask_to_alpha(menu2, al_map_rgb(40, 123, 241));
	al_convert_mask_to_alpha(menu3, al_map_rgb(40, 123, 241));
	al_convert_mask_to_alpha(pause_img, al_map_rgb(40, 123, 241));

	//G.init(0, 0, 5, 0, 800, 600, -1, 1, fgImage);
	image = menu1;
	al_convert_mask_to_alpha(image, al_map_rgb(40, 123, 241));

	theme_song = al_load_sample("Audio/menu_music.ogg");
	on_change = al_load_sample("Audio/on_change.ogg");

	//songInstance = al_create_sample_instance(theme_song);
	//al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	//al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());

	//al_play_sample_instance(songInstance);

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
		image = menu1;
		numberOfPlayers = 0; 
		break;
	case 1:
		image = menu2; 
		numberOfPlayers = 1;
		break;
	case 2:
		image = menu3; break;
	}
	//al_rest(1);


}

void Menu::updateBackgrounds()
{
	if(state == MENU)
	{
		M.UpdateBackground();
		//B.UpdateBackground();
	}
		//G.UpdateBackground();

}

void Menu::drawBackgrounds()
{
	if(state == MENU)
	{
		M.DrawBackground();
		//B.DrawBackground();
	}
	if(state == MENU || state == PAUSE)
	{
		ALLEGRO_BITMAP *tmp;
		if(state == MENU)
			tmp = image;
		else
			tmp = pause_img;
		
		int h = al_get_bitmap_height(tmp);
		int w = al_get_bitmap_width(tmp);

		al_draw_bitmap(tmp, WIDTH/2-w/2, HEIGHT/2-h/2, 0);
	}


	//G.DrawBackground();
}
void Menu::checkIfPaused(bool *keys)
{
	if(keys[Keyboard::P])
	{
		p_clicked = true;
	}
	else if(!keys[Keyboard::P] && p_clicked)
	{

		if(state == PAUSE)
			state = GAME;
		else if(state == GAME)
			state = PAUSE;
		p_clicked = false;
		//state = GAME;
	}
}

void Menu::drawInfo(Player p)
{

	

}

void Menu::drawPaused()
{

}


Menu::~Menu(void)
{
}
