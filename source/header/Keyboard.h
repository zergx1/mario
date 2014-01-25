#pragma once
#include <allegro5/allegro.h>

class Keyboard
{
public:
	bool keys[5];
	int numberButtons;
	enum KEYS{ UP, DOWN, LEFT, RIGHT, ESC, SPACE, ENTER, Z, X };
public:
	Keyboard(void);
	~Keyboard(void);
	int init(ALLEGRO_DISPLAY *display);
	void del();
	void update(ALLEGRO_EVENT ev);
};

