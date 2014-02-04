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
#include "header/FlowerMonster.h"
#include "header/Text.h"
#include "header\GlobalObjects.h"

int mainArtur(void)
{
	//variables
	Map map;
	Keyboard keyboard;
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
	Text text;
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

	const int numSprites = 1;

	TurtleMonster orbs[numSprites];
	Player mario;
	mario.Init(&map);
	Menu menu;
	menu.init();
	text.init();

	//Item item;
	//FlowerMonster f;
//	item.Init(FLOWER);
	//f.Init();

	if (map.init("Maps/test.fmp"))
	{
		return -5;
	}
	image = al_load_bitmap("Sprites/monster1.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	for (int i = 0; i < numSprites; i++)
		orbs[i].Init(SMART);


	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);

	while (!keyboard.keys[Keyboard::ESC])
	{
		if (menu.state == END)
			break;
		if(keyboard.keys[Keyboard::ENTER])
		{
			//item.LeaveBox();
		}

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		keyboard.update(ev);

		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (menu.state == MENU)
			{
				menu.update(keyboard.keys);
				menu.updateBackgrounds();
			}
			else if (menu.state == INFO)
			{
				text.update(&mario);
				if(menu.currentInfoTime++ > menu.infoTime)
				{
					menu.currentInfoTime = 0;
					menu.state = GAME;
				}

			}
			else
			{
				for (int i = 0; i < numSprites; i++)
				{
					orbs[i].Update();
					mario.collisionWithOther(&orbs[i]);
					simpleAnimation.collisionWithOther(&orbs[i]);
				}
				mario.Update(keyboard.keys);
				if (map.item->live)
				{
					map.item->Update();
					map.item->collisionWithOther(&mario);
				}
				//f.Update();
				//item.Update();
			}
			render = true;

		}


		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			if (menu.state == MENU)
			{
				menu.drawBackgrounds();
			}
			if (menu.state == INFO)
			{
				text.draw();
				//menu.drawInfo(mario);
			}
			else
			{
	
				map.draw();
				mario.Draw();
				if( map.item->live)
					map.item->Draw();
				//f.Draw();
				//item.Draw(xOff);

				for (int i = 0; i < numSprites; i++)
					orbs[i].Draw();
			}
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	map.del();
	keyboard.del();

	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}