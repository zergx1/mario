#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "lib/mappy_A5.h"

const int WIDTH = 1000;
const int HEIGHT = 240;

bool keys[] = { false, false, false, false };
enum KEYS{ UP, DOWN, LEFT, RIGHT };

int main(void)
{
	//variables
	bool done = false;
	bool render = false;

	int xOff = 0;
	int yOff = 0;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;
	int i = al_get_num_display_modes();

	al_get_display_mode(1, &disp_data);
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_hide_mouse_cursor(display);
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	if (MapLoad("Maps/level.fmp", 1))
		return -5;

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
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
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				keys[LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				keys[RIGHT] = false;
				break;
			case ALLEGRO_KEY_UP:
				keys[UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			xOff += keys[RIGHT] * 10;
			xOff -= keys[LEFT] * 10;
			yOff += keys[DOWN] * 10;
			yOff -= keys[UP] * 10;

			if (xOff < 0)
				xOff = 0;
			if (yOff < 0)
				yOff = 0;
			if (xOff >(mapwidth*mapblockwidth - WIDTH))
				xOff = mapwidth*mapblockwidth - WIDTH;
			if (yOff > mapheight*mapblockheight - HEIGHT)
				yOff = mapheight*mapblockheight - HEIGHT;


			render = true;
		}

		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	MapFreeMem();
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}
