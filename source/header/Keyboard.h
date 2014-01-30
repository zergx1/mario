#pragma once
#include <allegro5/allegro.h>

class Keyboard
{
public:
	enum KEYS{ UP, DOWN, LEFT, RIGHT, ESC, SPACE, ENTER, Z, X, SIZE_KEYS };
	bool keys[SIZE_KEYS];
	int numberButtons;
public:
	Keyboard(void);
	~Keyboard(void);
	int init(ALLEGRO_DISPLAY *display);
	void del();
	void update(ALLEGRO_EVENT ev);
};

