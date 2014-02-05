#include "header\Text.h"
#include "header/Sound.h"
#include <iostream>


Text::Text(void)
{
}

void Text::init()
{
	font = al_load_ttf_font("Fonts/arial.ttf", 15, 0);

	image = al_load_bitmap("Sprites/timer.png");
	mario_image = al_load_bitmap("Sprites/big_mario.png");
	al_convert_mask_to_alpha(image, al_map_rgb(96, 128, 192));

	counter = settings.getIntOption("time");	// time
	counterTemp = 0;
	startFrame = 0;
	maxFrame = 2;
	curFrame = 0;
	frameCount = 0;
	frameDelay = 30;
	frameWidth = 16;
	frameHeight = 16;
	reset = false;	// when mario is clear the stage
	name = "Player";
}


void Text::draw(bool world_info)
{
	int x = 0;
	int row1 = 10;
	int row2 = 25;

	al_draw_text(font, al_map_rgb(255, 255, 255), x += 3 * 15, row1, ALLEGRO_ALIGN_CENTRE, name);
	al_draw_text(font, al_map_rgb(255, 255, 255), 3 * 15, row2, ALLEGRO_ALIGN_CENTRE, score);

	int fx = curFrame * frameWidth;
	al_draw_bitmap_region(image, fx, 0, frameWidth, frameHeight, x += 70, row2 - 3, 0);
	al_draw_text(font, al_map_rgb(255, 255, 255), x += 30, row2, ALLEGRO_ALIGN_CENTRE, coin);

	al_draw_text(font, al_map_rgb(255, 255, 255), x += 60, row1, ALLEGRO_ALIGN_CENTRE, "WORLD");
	al_draw_text(font, al_map_rgb(255, 255, 255), x, row2, ALLEGRO_ALIGN_CENTRE, "1-1");



	
	for (int i = 0; i < vecFloatingText.size(); i++)
	{
		FloatingTextStruct text = vecFloatingText[i];
		al_draw_text(font, al_map_rgb(255, 255, 255), text.x - xOff, text.y, ALLEGRO_ALIGN_CENTRE,text.score);
	}

	if(world_info)
	{
			al_draw_bitmap_region(mario_image, 16, 0, 16, 32, x/2, 60 - 3, 0);
			al_draw_text(font, al_map_rgb(255, 255, 255), x/2+32, 60 + 8, ALLEGRO_ALIGN_CENTRE, live);


	}
	else
	{
			al_draw_text(font, al_map_rgb(255, 255, 255), x += 80, row1, ALLEGRO_ALIGN_CENTRE, "TIME");
			al_draw_text(font, al_map_rgb(255, 255, 255), x, row2, ALLEGRO_ALIGN_CENTRE, time);
	}
}

void Text::update(BaseCharacter *character, bool world_info)
{
	// NAME
	name = character->name;

	// ANIMATION
	if (++frameCount >= frameDelay)
	{

		curFrame += 1;
		if (curFrame >= maxFrame)
			curFrame = startFrame;

		frameCount = 0;
	}

	// SCORE
	int divisor = 100000;
	int temp = character->score;
	for (int i = 0; i < 6; i++)
	{
		score[i] = (char)(temp / divisor) + 48;
		if (temp / divisor != 0)
			temp %= divisor;
		divisor /= 10;
	}
	score[7] = '\0';	// end of array

	live[0] = 'x';
	live[1] = (char)(character->lives) + 48;


	// COINS
	divisor = 10;
	temp = character->coins;
	coin[0] = 'x';
	for (int i = 1; i < 3; i++)
	{
		//std::cout << temp << " " << divisor << "\n";
		coin[i] = (char)(temp / divisor) + 48;
		if (temp / divisor != 0)
			temp %= divisor;
		divisor /= 10;
	}
	coin[3] = '\0';	// end of array

	// TIMER
	if(!world_info)
	{
	divisor = 100;
	temp = counter;
	if (counter >= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			time[i] = (char)(temp / divisor) + 48;
			if (temp / divisor != 0)
				temp %= divisor;
			divisor /= 10;
		}
		time[3] = '\0';	// end of array
		if (reset)
		{
			counter--;
			character->score++;
		}
		else
			if (++counterTemp == 60 )
			{
				counter--;
				counterTemp = 0;
			}
	}
	if (!reset)
	{

		if (counter == 100)
			Sound::play(Sound::HURRY);
		if (counter == 0)
		{
			counter = settings.getIntOption("time");
			character->Kill();
		}
	}
	// FLOATING TEXT WITH SCORE
	for (int i = 0; i < vecFloatingText.size(); i++)
	{
		FloatingTextStruct &text = vecFloatingText[i];
		text.y -= 1;
		text.counter--;
		if (text.counter == 0 || text.y < 0)
		{
			vecFloatingText.erase(vecFloatingText.begin() + i);
			i--;
		}
		
	}

}

void Text::floatingScore(int x, int y, char *score)
{
	FloatingTextStruct text =
	{
		x, y, 60, score
	};
	vecFloatingText.push_back(text);
}

void Text::floatingScore(int x, int y, int score)
{
	int size = 1;
	int divisor = 1;
	
	while (score / (10 * divisor) != 0)
	{
		divisor *= 10;
		size++;
	}
	int temp = score;
	char *charScore = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		charScore[i] = (char)(temp / divisor) + 48;
		if (temp / divisor != 0)
			temp %= divisor;
		divisor /= 10;
	}
	charScore[size] = '\0';	// end of array
	floatingScore(x, y, charScore);
}


Text::~Text(void)
{
}
