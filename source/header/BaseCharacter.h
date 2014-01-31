#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


enum MARIO{ SMALL, BIG, SUPER };

class BaseCharacter
{
public:
	bool live;
	bool show;
	bool canTakeCoin;

	float x;	// current x coordinate
	float y;	// current y coordinate
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
	int score;
	int lives;
	int currentState;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *death_sound;
	BaseCharacter(void);
	~BaseCharacter(void);
	virtual void Init();
	virtual void Update();
	virtual void Draw(int flag = 0);
	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	virtual void takeCoin();
	virtual void collisionWithOther(BaseCharacter* character);
};
