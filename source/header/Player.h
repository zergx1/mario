#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
#include "header\Bullet.h"

enum MARIO{ SMALL, BIG, SUPER };

class Player: public BaseCharacter
{
private:
	Map* map;
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
public:
	Bullet* b;
	bool space_clicked;
	Player(void);
	~Player(void);
	virtual void Init(Map* map);
	virtual void Update(bool *keys);
	void changeStatus(MARIO s);
	virtual void Draw();
	virtual void animation();
};

