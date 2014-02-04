#pragma once
#include "GlobalObjects.h"
#include "lib/mappy_A5.h"
#include "BaseCharacter.h"
class BaseCharacter;
class DestroyBrickAnimation
{
private:
	float x;
	float y;
	float x2;
	float y2;
	float yOffset;
	float xOffset;
	int dirY;
	int angle;
	float velY;
	float velY2;
	int type;
	int background;
	ALLEGRO_BITMAP *image;
public:
	bool active;
	DestroyBrickAnimation(void);
	virtual void Init(int x, int y, BLKSTR *blockdata);
	virtual void Update();
	virtual void Draw();
	~DestroyBrickAnimation(void);
};

