#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Background
{
public:
	Background(void);

	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP *image;
	void init(float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
	void UpdateBackground();
	void DrawBackground();
	~Background(void);
};

