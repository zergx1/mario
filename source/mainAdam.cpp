#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "lib/mappy_A5.h"
#include "header/BaseMonster.h"
#include "header/TurtleMonster.h"

int mainAdam(void)
{
	int WIDTH = 1000;
	const int HEIGHT = 240;

	bool keys[] = { false, false, false, false };
	enum KEYS{ UP, DOWN, LEFT, RIGHT };

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
	ALLEGRO_BITMAP *image;

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
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(1);

	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;
	int width = 640;
	int height = 480;

	const int numSprites = 3;

	TurtleMonster orbs[numSprites];

	if (MapLoad("Maps/level2.fmp", 1))
	{
		al_show_native_message_box(al_get_current_display(), "Window Title", "Content Title", "The error message here", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -5;
	}
	image = al_load_bitmap("Sprites/monster1.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	for (int i = 0; i < numSprites; i++)
		orbs[i].Init();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);



	gameTime = al_current_time();

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
				for (int i = 0; i < numSprites; i++)
					orbs[i].KillByShot();
				break;
			case ALLEGRO_KEY_DOWN:
				keys[DOWN] = false;
				for (int i = 0; i < numSprites; i++)
					orbs[i].Hit();
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
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			for (int i = 0; i < numSprites; i++)
				orbs[i].Update();

			render = true;

		}


		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			MapDrawBG(xOff, yOff, 0, 0, WIDTH, HEIGHT);

			for (int i = 0; i < numSprites; i++)
				orbs[i].Draw();

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	MapFreeMem();

	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}