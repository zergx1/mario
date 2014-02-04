#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "lib/mappy_A5.h"
#include "header/BaseMonster.h"
#include "header/Player.h"
#include "header/TurtleMonster.h"
#include "header/Map.h"
#include "header/Keyboard.h"
#include "header/Menu.h"
#include "header/GlobalObjects.h"


int mainAdam(void)
{
	//variables
	const int numSprites = 1;
	BaseMonster orbs[numSprites];
	Player mario;
	Map map;
	Menu menu;
	Keyboard keyboard;
	bool done = false;
	bool render = false;

	//int xOff = 0;
	//int yOff = 0;

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
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	keyboard.init(display);
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(1);


	mario.Init(&map);
	globalText.init();
	//menu.init();

	if (map.init("Maps/test.fmp"))
	{
		return -5;
	}

	for (int i = 0; i < numSprites; i++)
		orbs[i].Init();


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	while (!keyboard.keys[Keyboard::ESC])
	{
		/*if (menu.state == END)
			break;*/
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		keyboard.update(ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			/*if (menu.state == MENU)
			{
				menu.update(keyboard.keys);
				menu.updateBackgrounds();
			}
			else
			{*/
			for (int i = 0; i < numSprites; i++){
					orbs[i].Update();
					mario.collisionWithOther(&orbs[i]);
					for (int v = 0; v < bumpingBlockAnimation.size(); v++)
						bumpingBlockAnimation[v].collisionWithOther(&orbs[i]);
			}
				mario.Update(keyboard.keys);
				for (int v = 0; v < bumpingBlockAnimation.size(); v++)
					bumpingBlockAnimation[v].Update();
				for (int v = 0; v < destroyBrickAnimation.size(); v++)
					destroyBrickAnimation[v].Update();
				if (map.item->live)
				{
					map.item->Update();
					map.item->collisionWithOther(&mario);
					for (int v = 0; v < bumpingBlockAnimation.size(); v++)
						bumpingBlockAnimation[v].collisionWithOther(map.item);
				}
			//}
			render = true;

		}


		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			/*if (menu.state == MENU)
			{
				menu.drawBackgrounds();
			}
			else
			{*/

				map.draw();
				globalText.update(&mario);
				globalText.draw();
				mario.Draw(); 
				for (int v = 0; v < bumpingBlockAnimation.size(); v++)
					bumpingBlockAnimation[v].Draw();
				for (int v = 0; v < destroyBrickAnimation.size(); v++)
					destroyBrickAnimation[v].Draw();
				if (map.item->live)
					map.item->Draw();
				for (int i = 0; i < numSprites; i++)
					orbs[i].Draw();
			//}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	map.del();
	keyboard.del();

	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}