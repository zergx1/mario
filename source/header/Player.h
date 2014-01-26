#pragma once
#include "BaseCharacter.h"
#include "header/Map.h"
class Player: public BaseCharacter
{
private:
	Map* map;
	ALLEGRO_SAMPLE_INSTANCE *jump;
	ALLEGRO_SAMPLE_INSTANCE *die;
	ALLEGRO_SAMPLE_INSTANCE *breakBrick;
public:
	Player(void);
	~Player(void);
	virtual void Init(Map* map);
	virtual void Update(bool *keys);
	virtual void Draw();
	virtual void animation();
};

