#pragma once
#include "BaseCharacter.h"

class Bullet: public BaseCharacter
{
public:
	Bullet(void);
	int currentJumpTime;
	int maxJumpTime;
	ALLEGRO_SAMPLE *on_shoot;
	virtual void Init(int x0 = 0, int y0 = 0);
	virtual void Update();
	virtual void Shoot(float x, float y, int dirX);
	virtual void Draw(float xOff);
	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	virtual void collisionWithOther(BaseCharacter* character);
	~Bullet(void);
};

