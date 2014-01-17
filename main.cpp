#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "BaseMonster.h"
 


int main(void)
{
	//variables
	bool done = false;
	bool render = false;	
	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;
	int width = 640;
	int height = 480;

	const int numSprites = 1;

	BaseMonster orbs[numSprites];

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_FONT *font18 = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *image;
	
	//program init
	if(!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(width, height);			//create our display object

	if(!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	font18 = al_load_font("Fonts/arial.ttf", 18, 0);

	image = al_load_bitmap("Sprites/monster1.png");
	al_convert_mask_to_alpha(image, al_map_rgb(0, 0, 0));

	for(int i = 0; i < numSprites; i++)
		orbs[i].Init(image);

	
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:
				
				break;
			case ALLEGRO_KEY_RIGHT:
				
				break;
			case ALLEGRO_KEY_UP:
				
				break;
			case ALLEGRO_KEY_DOWN:
				
				break;
			}
		}
		else if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			frames++;
			if(al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			for(int i = 0; i < numSprites; i++)
				orbs[i].Update();

			render = true;
		}

		if(render && al_is_event_queue_empty(event_queue))
		{
			render = false;
						
			for(int i = 0; i < numSprites; i++)
				orbs[i].Draw();

			al_draw_textf(font18, al_map_rgb(255, 0, 255), 5, 5, 0, "FPS: %i", gameFPS);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0,0,0));
		}
	}

	al_destroy_bitmap(image);
	al_destroy_font(font18);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

//#include <allegro5\allegro.h>
//#include <allegro5\allegro_image.h>
//
//int main(void)
//{
//	//variables
//	int width = 640;
//	int height = 480;
//
//	int imageWidth = 16;
//	int imageHeight = 16;
//
//	const int arraySize = 3;
//	
//	//allegro variable
//	ALLEGRO_DISPLAY *display = NULL;
//	ALLEGRO_BITMAP *image[arraySize];
//	ALLEGRO_BITMAP *outImage;
//	
//	//program init
//	if(!al_init())										//initialize Allegro
//		return -1;
//
//	display = al_create_display(width, height);			//create our display object
//
//	if(!display)										//test display object
//		return -1;
//
//	//addon init
//	al_init_image_addon();
//
//	image[0] = al_load_bitmap("33.png");
//	image[1] = al_load_bitmap("34.png");
//	image[2] = al_load_bitmap("35.png");
//
//	//imageWidth = al_get_bitmap_width(image[0]);
//	//imageHeight = al_get_bitmap_height(image[0]);
//
//	outImage = al_create_bitmap(imageWidth * arraySize, imageHeight);
//
//	al_set_target_bitmap(outImage);
//	al_clear_to_color(al_map_rgb(0, 0, 0));
//
//	for(int i = 0; i < arraySize; i++)
//	{
//		al_draw_bitmap(image[i], i * imageWidth, 0, 0);
//	}
//
//	al_save_bitmap("sprite_sheet_demo.png", outImage);
//
//	al_set_target_bitmap(al_get_backbuffer(display));
//
//
//	for(int i = 0; i < arraySize; i++)
//		al_destroy_bitmap(image[i]);
//	al_destroy_bitmap(outImage);
//	al_destroy_display(display);						//destroy our display object
//
//	return 0;
//}