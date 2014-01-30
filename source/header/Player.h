#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
#include "header/Keyboard.h"
#include "header\Bullet.h"

enum MARIO{ SMALL, BIG, SUPER };

class Player: public BaseCharacter
{
private:
	bool oldKeys[Keyboard::SIZE_KEYS];
	Map* map;
	bool jump;

	ALLEGRO_BITMAP *small_mario;
	ALLEGRO_BITMAP *big_mario;
	ALLEGRO_BITMAP *super_mario;

	MARIO currentState;

	int blinking_time;
	int current_blinking_time;
	bool blinking;


public:
	Bullet* b;
	bool space_clicked;
	Player(void);
	~Player(void);
	virtual void Init(Map* map);
	virtual void Update(bool keys[]);
	void changeStatus(MARIO s);
	virtual void Draw();
	virtual void animation();
	virtual void transformation();
	virtual void takeCoin();
};

