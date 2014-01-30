#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
#include "header/Keyboard.h"

//	enum STATE{ NONE, SMALL_MARIO, SUPER_MARIO, WHITE_SUPER_MARIO };	// i need to count starts 1 so, thets why there is NONE state

class Player: public BaseCharacter
{
private:
	bool oldKeys[Keyboard::SIZE_KEYS];
	Map* map;
	bool jump;
public:
	Player(void);
	~Player(void);
	virtual void Init(Map* map);
	virtual void Update(bool keys[]);
	virtual void Draw();
	virtual void animation();
	virtual void takeCoin();
};

