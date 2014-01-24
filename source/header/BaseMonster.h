#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "BaseCharacter.h"

class BaseMonster: public BaseCharacter
{
	public:
		bool killedByShot;

		int timeToClear;
		int currentTimeToClear;

		int startY;

		int waitY;
		int currentWaitY;

		float fallingSpeedFactor;
		float deathJumpY;

		ALLEGRO_BITMAP *image;
		ALLEGRO_SAMPLE *death_sound;
		BaseMonster(void);
		virtual void Init();
		virtual void Update();
		virtual void Draw(float xOff, float yOff);
		virtual void Hit();
		virtual void Kill();
		virtual void KillByShot();
		~BaseMonster(void);
};

