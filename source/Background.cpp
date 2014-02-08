#include "header\Background.h"


Background::Background(void)
{
}

void Background::init(float x1, float y1, float velx1, float vely1, int width1, int height1, int dirX1, int dirY1, ALLEGRO_BITMAP *image1)
{
	x = x1;
	y = y1;
	velX = velx1;
	velY = vely1;
	width = width1;
	height = height1;
	dirX = dirX1;
	dirY = dirY1;
	image = image1;
	//al_convert_mask_to_alpha(image, al_map_rgb(40, 123, 241));
}

void Background::UpdateBackground()
{
	x += velX * dirX;
	if(x + width <= 0)
		x = 0;
}

void Background::DrawBackground()
{

	al_draw_bitmap(image, x, y, 0);


}

Background::~Background(void)
{
}
