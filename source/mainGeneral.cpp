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
#include "header/Sound.h"


int mainGeneral(void)
{
	//variables
	Map map;
	Keyboard keyboard;
	Player *players[2];
	players[0] = new Player();
	players[1] = new Player();
	Menu menu;
	const int numMonsters = 16;
	BaseMonster *monsters[numMonsters];
	bool done = false;
	bool render = false;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_DISPLAY_MODE   disp_data;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;

	//program init
	if (!al_init())	//initialize Allegro
		return -1;
	
	al_get_display_mode(1, &disp_data);
	//al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	display = al_create_display(disp_data.width, disp_data.height);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_init_font_addon(); // initialize the font addon
	al_init_ttf_addon();// initialize the ttf (True Type Font) addon
	al_init_image_addon();
	al_install_audio();
	al_reserve_samples(5);
	al_init_acodec_addon();
	al_hide_mouse_cursor(display);
	al_install_keyboard();

	al_reserve_samples(1);

	start:

	// INIT
	menu.init();
	settings.init();
	globalText.init();
	keyboard.init(display);
	players[0]->Init(&map, false);
	players[1]->Init(&map, true);

respawn:
	if (++currentPlayer > menu.numberOfPlayers)
		currentPlayer = 0;
	players[currentPlayer]->readyToRespawn = false;
	xOff = players[currentPlayer]->x;
	if (map.init("Maps/test.fmp"))
	{
		return -5;
	}
	map.draw();
	monsters[0] = new TurtleMonster();
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
		if(players[currentPlayer]->beforeStart && menu.state == GAME )
		{
				menu.state = INFO;
				players[currentPlayer]->beforeStart = false;
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
				globalText.update(players[currentPlayer], true);
				if(++menu.currentInfoTime > menu.infoTime)
				{
					menu.currentInfoTime = 0;
					menu.state = GAME;
					Sound::playBackgroundMusic(Sound::MUSIC);
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
					if (monsters[i]->started && !players[currentPlayer]->win)
					{
						monsters[i]->Update();
						players[currentPlayer]->collisionWithOther(monsters[i]);
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
				players[currentPlayer]->Update(keyboard.keys);
				globalText.update(players[currentPlayer]);
				for (int v = 0; v < bumpingBlockAnimation.size(); v++)
					bumpingBlockAnimation[v].Update();
				for (int v = 0; v < destroyBrickAnimation.size(); v++)
					destroyBrickAnimation[v].Update();
				for (int v = 0; v < jumpingCoinAnimation.size(); v++)
					jumpingCoinAnimation[v].Update();
				if (map.item->live)
				{
					map.item->Update();
					map.item->collisionWithOther(players[currentPlayer]);
					for (int v = 0; v < bumpingBlockAnimation.size(); v++)
						bumpingBlockAnimation[v].collisionWithOther(map.item);
				}
				//if (globalText.counter == 290)
				//	Sound::playBackgroundMusic(Sound::MUSIC_INVINCIBLE);

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
			else if (menu.state == INFO)
			{
				globalText.draw(true);
				//menu.drawInfo(players);
			}
			else
			{
				map.draw();
				players[currentPlayer]->Draw();
				globalText.draw();
				if( map.item->live)
					map.item->Draw();
				for (int v = 0; v < bumpingBlockAnimation.size(); v++)
					bumpingBlockAnimation[v].Draw();
				for (int v = 0; v < destroyBrickAnimation.size(); v++)
					destroyBrickAnimation[v].Draw();
				for (int v = 0; v < jumpingCoinAnimation.size(); v++)
					jumpingCoinAnimation[v].Draw();

				for (int i = 0; i < numMonsters; i++)
				{
					if(monsters[i]->started)
						monsters[i]->Draw();
				}
				menu.drawBackgrounds();

			}
			if (players[0]->lives <= 0 && players[0]->beforeStart && ((players[1]->lives <= 0 && players[1]->beforeStart) || !menu.numberOfPlayers == 1)) // material implication
			{
				Sound::play(Sound::GAME_OVER);
				goto start;
			}
			if (players[currentPlayer]->readyToRespawn)
				goto respawn;

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