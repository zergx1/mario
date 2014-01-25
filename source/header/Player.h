#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
class Player: public BaseCharacter
{
private:
	Map* map;
	bool jump;
public:
	Player(void);
	~Player(void);
	virtual void Init(Map* map);
	virtual void Update(bool *keys);
	virtual void Draw();
};

