#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>

#include "Background.h";


enum STATE{ MENU, GAME, END };

class Menu
{
public:
	Menu(void);

	STATE state;

	Background B,M,G;
	int current;
	int last_status;
	ALLEGRO_BITMAP *menu1;
	ALLEGRO_BITMAP *menu2;
	ALLEGRO_BITMAP *menu3;
	ALLEGRO_SAMPLE *theme_song;
	ALLEGRO_SAMPLE *on_change;

	ALLEGRO_SAMPLE_INSTANCE *songInstance;
	bool down_clicked;
	bool up_clicked;

	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP *image;

	void setState(int state);
	void update(bool* keys);
	//void drawMenu();
	void updateBackgrounds();
	void drawBackgrounds();
	void init();
	~Menu(void);

};



