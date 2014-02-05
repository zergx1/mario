#pragma once
#include "GlobalObjects.h"
#include "lib/mappy_A5.h"

class JumpingCoinAnimation
{
private:
	int x;
	int y;
	int velY;
	int dirY;
	int yOffset;
	ALLEGRO_BITMAP *image;
	int startFrame;
	int maxFrame;
	int curFrame;
	int frameCount;
	int frameDelay;

public:
	bool active;
	JumpingCoinAnimation(void);
	virtual void Init(int x, int y, BLKSTR *blockdata);
	virtual void Update();
	virtual void Draw();
	~JumpingCoinAnimation(void);
};

