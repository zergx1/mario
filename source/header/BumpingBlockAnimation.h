#pragma once
#include "GlobalObjects.h"
#include "lib/mappy_A5.h"
#include "BaseCharacter.h"
class BaseCharacter;
class BumpingBlockAnimation
{
private:
	int x;
	int y;
	int yOffset;
	int dirY;
	int animationDuration;
	int type;
	int background;
	ALLEGRO_BITMAP *image;
public:
	bool active;
	BumpingBlockAnimation(void);
	virtual void Init(int x, int y, BLKSTR *blockdata);
	virtual void Update();
	virtual void Draw();
	virtual void collisionWithOther(BaseCharacter* character);
	~BumpingBlockAnimation(void);
};

