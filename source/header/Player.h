#pragma once
#include "BaseCharacter.h"
class Player: public BaseCharacter
{
public:
	Player(void);
	~Player(void);
	virtual void Init();
};

