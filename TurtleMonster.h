#pragma once
#include "basemonster.h"
class TurtleMonster :
	public BaseMonster
{

public:

	TurtleMonster(void);
	virtual void Init();
	virtual void Draw();
	virtual void Hit();
	virtual void Kill();

	~TurtleMonster(void);
};

