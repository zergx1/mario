#pragma once
#include "GlobalObjects.h"
#include "lib/mappy_A5.h"
#include "BaseCharacter.h"
class BaseCharacter;
class SimpleAnimation
{
private:
	int x;
	int y;
	int yOffset;
	int dirY;
	int animationDuration;
	int type;
	bool active;
	ALLEGRO_BITMAP *image;
public:
	SimpleAnimation(void);
	virtual void Init(int x, int y, int type);
	virtual void Update();
	virtual void Draw();
	virtual void collisionWithOther(BaseCharacter* character);
	~SimpleAnimation(void);
};

