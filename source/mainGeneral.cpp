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


int mainGeneral(void)
{
	//variables
	Map map;
	Keyboard keyboard;
	bool done = false;
	bool render = false;
	settings.init();



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

	const int numMonsters = 16;

	BaseMonster *monsters[numMonsters];
	monsters[0] = new TurtleMonster();//.Init(13*16, 12*16);
	monsters[0]->InitType(13*16, 12*15, SMART);
	monsters[1] =  new BaseMonster();
	monsters[1]->Init(26*16, 12*16);
	monsters[2] =  new BaseMonster();
	monsters[2]->Init(53*16, 12*16);
	monsters[3] =  new TurtleMonster();
	monsters[3]->InitType(42*16, 11*16, SMART);
	monsters[4] =  new BaseMonster();
	monsters[4]->Init(49*16, 5*16);
	monsters[5] =  new TurtleMonster();
	monsters[5]->Init(75*16, 7*16);
	monsters[6] =  new BaseMonster();
	monsters[6]->Init(80*16, 12*16);
	monsters[7] =  new BaseMonster();
	monsters[7]->Init(98*16, 12*16);
	monsters[8] =  new TurtleMonster();
	monsters[8]->InitType(138*16, 11*16, SMART);
	monsters[9] =  new BaseMonster();
	monsters[9]->Init(120*16, 12*16);
	monsters[10] =  new BaseMonster();
	monsters[10]->Init(168*16, 5*16);
	monsters[11] =  new TurtleMonster();
	monsters[11]->Init(166*16, 6*16);
	monsters[12] =  new TurtleMonster();
	monsters[12]->Init(164*16, 2*16);
	monsters[13] =  new BaseMonster();
	monsters[13]->Init(162*16, 11*16);
	monsters[14] =  new FlowerMonster();
	monsters[14]->Init(33*16, 9*16);
	monsters[15] =  new FlowerMonster();
	monsters[15]->Init(83*16, 11*16);
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

	//for (int i = 0; i < numMonsters; i++)
	//	monsters[i]->Init(SMART);


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
			if(menu.state == PAUSE)
			{
				menu.checkIfPaused(keyboard.keys);

			}
			else if (menu.state == MENU)
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
				menu.checkIfPaused(keyboard.keys);
				for (int i = 0; i < numMonsters; i++)
				{
					monsters[i]->startAction(720);
				}
				for (int i = 0; i < numMonsters; i++)
				{
					if(monsters[i]->started)
					{
						monsters[i]->Update();
						mario.collisionWithOther(monsters[i]);
						for (int v = 0; v < bumpingBlockAnimation.size(); v++)
							bumpingBlockAnimation[v].collisionWithOther(monsters[i]);
						for(int j=0;j< numMonsters; j++)
						{
							if(i == j)
								continue;
							if(monsters[j]->started)
								monsters[i]->collisionWithOtherMonster(monsters[j]);
						}
					}
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

				for (int i = 0; i < numMonsters; i++)
				{
					if(monsters[i]->started)
						monsters[i]->Draw();
				}
				menu.drawBackgrounds();

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