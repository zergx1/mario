#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class BaseMonster
{
	public:
		bool live;
		bool show;
		bool killedByShot;

		int timeToClear;
		int currentTimeToClear;
		int score;
		int lives;
		float fallingSpeedFactor;
		float deathJumpY;

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
		ALLEGRO_SAMPLE *death_sound;
		BaseMonster(void);
		virtual void Init();
		virtual void Update();
		virtual void Draw();
		virtual void Hit();
		virtual void Kill();
		virtual void KillByShot();
		~BaseMonster(void);
};

