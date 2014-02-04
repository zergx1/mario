#pragma once
#include "BaseMonster.h"


class FlowerMonster :
	public BaseMonster
{
public:

	FlowerMonster(void);
	virtual void Init(int x0 = 0, int y0 = 0);

	virtual void Draw();
	virtual void Update();

	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	~FlowerMonster(void);
};

