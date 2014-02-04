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
		virtual void Init(int x0 = 0, int y0 = 0);
		virtual void Update();
		virtual void Draw();
		virtual void Hit();
		virtual void Kill();
		virtual void KillByShot();
		virtual void collisionWithOtherMonster(BaseCharacter* character);

		~BaseMonster(void);
};

