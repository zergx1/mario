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
	virtual void Init();
	virtual void Init(TURTLE s);
	virtual void Draw();
	virtual void Update();

	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	void revive();

	TURTLE type;
	int timeToReborn;
	int currentTimeToReborn;
	~TurtleMonster(void);
};

#endif