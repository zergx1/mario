#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
<<<<<<< HEAD
#include "header/Keyboard.h"

//	enum STATE{ NONE, SMALL_MARIO, SUPER_MARIO, WHITE_SUPER_MARIO };	// i need to count starts 1 so, thets why there is NONE state
=======
#include "header\Bullet.h"

enum MARIO{ SMALL, BIG, SUPER };
>>>>>>> origin/master

class Player: public BaseCharacter
{
private:
	bool oldKeys[Keyboard::SIZE_KEYS];
	Map* map;
<<<<<<< HEAD
	bool jump;
=======
	ALLEGRO_BITMAP *small_mario;
	ALLEGRO_BITMAP *big_mario;
	ALLEGRO_BITMAP *super_mario;

	MARIO state;
	ALLEGRO_SAMPLE *power_up;
	ALLEGRO_SAMPLE *power_down;
	ALLEGRO_SAMPLE *power_2xup;


	int blinking_time;
	int current_blinking_time;
	bool blinking;
	ALLEGRO_SAMPLE_INSTANCE *jump;
	ALLEGRO_SAMPLE_INSTANCE *die;
	ALLEGRO_SAMPLE_INSTANCE *breakBrick;
>>>>>>> origin/master
public:
	Bullet* b;
	bool space_clicked;
	Player(void);
	~Player(void);
	virtual void Init(Map* map);
<<<<<<< HEAD
	virtual void Update(bool keys[]);
=======
	virtual void Update(bool *keys);
	void changeStatus(MARIO s);
>>>>>>> origin/master
	virtual void Draw();
	virtual void animation();
	virtual void takeCoin();
};

