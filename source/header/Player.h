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
	bool invisible;

	ALLEGRO_BITMAP *small_mario;
	ALLEGRO_BITMAP *big_mario;
	ALLEGRO_BITMAP *super_mario;

	int currentState;

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
	void changeStatus(int s);
	virtual void Draw(int flag = 0);
	virtual void Kill();
	virtual void animation();
	virtual void transformation();
	virtual void takeCoin();
	virtual void collisionWithOther(BaseCharacter* character);
};

