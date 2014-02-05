#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "header/GlobalObjects.h"

enum MARIO{ SMALL, BIG, SUPER };
class BaseCharacter
{
public:
	char *name;
	bool live;
	bool show;
	bool canTakeCoin;
	bool killsOtherMonsters;
	bool started; // when maps is close 
	bool killableByJump;

	float x;	// current x coordinate
	float y;	// current y coordinate
	float velX;
	float velY;
	// for collision, escape from too fast collision
	float marginX; // default 0
	float marginY;  // default 0
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
	int coins;
	int lives;
	int currentState;

	ALLEGRO_BITMAP *image;
	ALLEGRO_SAMPLE *death_sound;

	BaseCharacter(void);
	~BaseCharacter(void);
	virtual void startAction(int width);
	virtual void Init(int x0 = 0, int y0 = 0);

	virtual void Update();
	virtual void Draw(int flag = 0);
	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	virtual bool CheckIfKillPlayer(BaseCharacter* character);
	virtual void takeCoin();
	virtual void collisionWithOther(BaseCharacter* character);
	virtual void collisionWithOtherMonster(BaseCharacter* character);
	virtual void takeItem(BaseCharacter* character);

};
