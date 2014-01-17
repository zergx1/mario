#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class BaseMonster
{
	public:
		float x;
		float y;
		float velX;
		float velY;
		int dirX;
		int dirY;
		int startFrame;
		int maxFrame;
		int curFrame;
		int frameCount;
		int frameDelay;
		int frameWidth;
		int frameHeight;
		int animationColumns;
		int animationDirection;

		ALLEGRO_BITMAP *image;
		BaseMonster(void);
		void Init(ALLEGRO_BITMAP *img);
		void Update();
		void Draw();
		~BaseMonster(void);
};

