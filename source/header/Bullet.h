#pragma once
#include "BaseCharacter.h"

class Bullet: public BaseCharacter
{
public:
	Bullet(void);
	int currentJumpTime;
	int maxJumpTime;
	ALLEGRO_SAMPLE *on_shoot;
	virtual void Init();
	virtual void Update();
	virtual void Shoot(float x, float y, int dirX);
	virtual void Draw(float xOff);
	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	virtual void collisionWithOther(BaseCharacter* character);
	~Bullet(void);
};

