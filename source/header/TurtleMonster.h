#pragma once
#include "BaseMonster.h"
class TurtleMonster :
	public BaseMonster
{

public:

	TurtleMonster(void);
	virtual void Init();
	virtual void Draw();
	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	void revive();

	int timeToReborn;
	int currentTimeToReborn;
	~TurtleMonster(void);
};

