#pragma once
#include "header/Sound.h"

namespace Sound{

	SoundStructure * sounds;
	bool isInitialized = false;

	int init()
	{
		isInitialized = true;
		sounds = new SoundStructure[SIZE_OF_SOUNDS]; 

		sounds[JUMP].sample = al_load_sample("Audio/jump.ogg");
		sounds[MARIO_DIE].sample = al_load_sample("Audio/mario_dies.ogg");

		sounds[BREAK_BRICK].sample = al_load_sample("Audio/break_brick.ogg");
		sounds[BREAK_BRICK].needSimultaneous = true;
		sounds[BUMP].sample = al_load_sample("Audio/bump.ogg");
		sounds[BUMP].needSimultaneous = true;
		sounds[COIN].sample = al_load_sample("Audio/coin.ogg");
		sounds[COIN].needSimultaneous = true;

		sounds[POWER_UP].sample = al_load_sample("Audio/Powerup.ogg");
		sounds[POWER_DOWN].sample = al_load_sample("Audio/Power Down.ogg");
		sounds[POWER_APPEARS].sample = al_load_sample("Audio/Powerup Appears.ogg");
		sounds[GAIN_LIFE].sample = al_load_sample("Audio/Gain Life.ogg");
		sounds[PIPE].sample = al_load_sample("Audio/Pipe.ogg");
		//sounds[].sample = al_create_sample_instance(al_load_sample("")); // example to adding 

		for (int i = 0; i < SIZE_OF_SOUNDS; i++)
		{
			for (int j = 0; j < MAX_SIMULTANEOUS; j++)
			{
				sounds[i].inst[j] = al_create_sample_instance(sounds[i].sample);
				al_attach_sample_instance_to_mixer(Sound::sounds[i].inst[j], al_get_default_mixer());
				if (!sounds[i].needSimultaneous)
					break;
			}
		}

		return 1;
	}

	void play(int sound, ALLEGRO_PLAYMODE playmode)
	{
		if (!isInitialized)
			init();
		al_set_sample_instance_playmode(sounds[sound].inst[sounds[sound].index], playmode);
		al_play_sample_instance(sounds[sound].inst[sounds[sound].index]);

		if (++sounds[sound].index == MAX_SIMULTANEOUS || !sounds[sound].needSimultaneous)
			sounds[sound].index = 0;
	}

	void play(int sound)
	{
		play(sound, ALLEGRO_PLAYMODE_ONCE);
	}
}