#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
#include "header/Keyboard.h"
#include "header\Bullet.h"

enum PIPE_MOVE{NONE, RIGHT, DOWN, UP};

class Player: public BaseCharacter
{
private:
	bool oldKeys[Keyboard::SIZE_KEYS];
	Map* map;
	bool jump;
	bool invisible;
	

	bool incerdible; //if mario took star
	int incerdileTime;
	int currentIncredibleTime;

	PIPE_MOVE pipeMoveState;
	bool inPipeMove;
	float pipeMoveToX;
	float pipeMoveToY;
	float pipeCounter; // for moving effect

	ALLEGRO_BITMAP *small_mario;
	ALLEGRO_BITMAP *big_mario;
	ALLEGRO_BITMAP *super_mario;

	ALLEGRO_BITMAP *inc_small_mario;
	ALLEGRO_BITMAP *inc_big_mario;
	ALLEGRO_BITMAP *inc_super_mario;

	int blinking_time;
	int current_blinking_time;
	bool blinking;

public:
	bool win;
	Bullet* bullets;
	bool beforeStart; //show info before start
	bool space_clicked;
	Player(void);
	~Player(void);
	virtual void Init(Map* map);
	virtual void Update(bool keys[]);
	void changeStatus(int s, bool instant = false);
	virtual void Draw(int flag = 0);
	virtual void Kill();
	virtual void animation();
	virtual void transformation();
	virtual void setIncerdible();
	virtual void updateIncerdible();
		
	virtual void takeCoin();
	virtual void pipeMove(int toX, int toY, PIPE_MOVE from);
	virtual void collisionWithOther(BaseCharacter* character);
	virtual void takeItem(BaseCharacter* character);
	void stageClear();
};

