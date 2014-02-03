#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include "basecharacter.h"
#include "header/Map.h"

enum TYPE{ MUSHROOM, FLOWER };
enum ITEM_STATUS{HIDDEN, LEAVING, LEFT};


class Item :
	public BaseCharacter
{
public:
	ITEM_STATUS status;
	float speedAfterExitX;
	float speedAfterExitY;
	float exitSpeed;
	TYPE type;
	float startY;

	Item(void);
	virtual void Init(TYPE t, float x, float y);
	virtual void LeaveBox();
	virtual void Update();
	virtual void Draw();
	virtual void Hit();
	virtual void Kill();
	virtual void KillByShot();
	virtual void collisionWithOther(BaseCharacter* character);
	~Item(void);
};

#endif