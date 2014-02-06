#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include "Background.h";
#include "Player.h"

enum STATE{ MENU, GAME, INFO, END, PAUSE };

class Menu
{
public:
	Menu(void);

	STATE state;

	Background B,M,G;
	int current;
	int last_status;
	int infoTime;
	int currentInfoTime;
	int numberOfPlayers;
	ALLEGRO_BITMAP *menu1;
	ALLEGRO_BITMAP *menu2;
	ALLEGRO_BITMAP *menu3;
	ALLEGRO_SAMPLE *theme_song;
	ALLEGRO_SAMPLE *on_change;

	ALLEGRO_SAMPLE_INSTANCE *songInstance;
	bool down_clicked;
	bool up_clicked;
	bool p_clicked;

	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP *image;
	ALLEGRO_BITMAP *pause_img;

	void setState(int state);
	void update(bool* keys);
	void checkIfPaused(bool *keys);
	//void drawMenu();
	void updateBackgrounds();
	void drawBackgrounds();
	void init();
	void drawInfo(Player p);
	void drawPaused();
	~Menu(void);

};



