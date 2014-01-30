#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
#include "header\Bullet.h"

enum MARIO{ SMALL, BIG, INCREDIBLE };

class Player: public BaseCharacter
{
private:
	Map* map;
	ALLEGRO_BITMAP *small_mario;
	ALLEGRO_BITMAP *big_mario;
	MARIO state;
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

