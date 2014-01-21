#pragma once
#include "header/Keyboard.h"
#include <iostream>
#include <allegro5/allegro_native_dialog.h>

Keyboard::Keyboard(void)
{
}


Keyboard::~Keyboard(void)
{

}

int Keyboard::init(ALLEGRO_DISPLAY *display)
{
	for (int i = 0; i < 5; i++)
	{
		keys[i] = false;
	}

	al_hide_mouse_cursor(display);
	al_install_keyboard();
	return 1;
}

void Keyboard::del()
{

}

void Keyboard::update(ALLEGRO_EVENT ev)
{
	if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			keys[ESC] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = true;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = true;
			break;
		case ALLEGRO_KEY_UP:
			keys[UP] = true;
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = true;
			break;
		}
	}
	else if (ev.type == ALLEGRO_EVENT_KEY_UP)
	{
		switch (ev.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			keys[ESC] = true;
			break;
		case ALLEGRO_KEY_LEFT:
			keys[LEFT] = false;
			break;
		case ALLEGRO_KEY_RIGHT:
			keys[RIGHT] = false;
			break;
		case ALLEGRO_KEY_UP:
			keys[UP] = false;
			//for (int i = 0; i < numSprites; i++)
			//	orbs[i].KillByShot();
			break;
		case ALLEGRO_KEY_DOWN:
			keys[DOWN] = false;
			//for (int i = 0; i < numSprites; i++)
			//	orbs[i].Hit();
			break;
		}
	}
	
}
