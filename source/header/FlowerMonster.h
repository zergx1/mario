#pragma once
#include "BaseMonster.h"


class FlowerMonster :
	public BaseMonster
{
public:

	FlowerMonster(void);
	virtual void Init();
	virtual void Draw();
	virtual void Update();

	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	~FlowerMonster(void);
};

