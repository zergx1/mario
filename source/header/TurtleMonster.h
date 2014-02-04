#ifndef TURTLE_H_INCLUDED
#define TURTLE_H_INCLUDED

#pragma once
#include "BaseMonster.h"

enum TURTLE{NORMAL, SMART};

class TurtleMonster :
	public BaseMonster
{

public:

	TurtleMonster(void);
	virtual void Init(int x0 = 0, int y0 = 0);
	virtual void Init(int x0, int y0, TURTLE s);
	virtual void Draw();
	virtual void Update();

	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	void revive();
	virtual bool CheckIfKillPlayer(BaseCharacter* character);

	TURTLE type;
	int timeToReborn;
	int currentTimeToReborn;
	~TurtleMonster(void);
};

#endif