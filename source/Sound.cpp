#pragma once
#include "header/Sound.h"

namespace Sound{

	SoundStructure * sounds;
	bool isInitialized = false;

	int init()
	{
		isInitialized = true;
		sounds = new SoundStructure[SIZE_OF_SOUNDS];

		sounds[JUMP].inst = al_create_sample_instance(al_load_sample("Audio/jump.ogg"));
		sounds[MARIO_DIE].inst = al_create_sample_instance(al_load_sample("Audio/mario_dies.ogg"));
		sounds[BREAK_BRICK].inst = al_create_sample_instance(al_load_sample("Audio/break_brick.ogg"));
		sounds[BUMP].inst = al_create_sample_instance(al_load_sample("Audio/bump.ogg"));
		sounds[COIN].inst = al_create_sample_instance(al_load_sample("Audio/coin.ogg"));
		sounds[POWER_UP].inst = al_create_sample_instance(al_load_sample("Audio/Powerup.ogg"));
		sounds[POWER_DOWN].inst = al_create_sample_instance(al_load_sample("Audio/Power Down.ogg"));
		sounds[POWER_2xUP].inst = al_create_sample_instance(al_load_sample("Audio/Powerup Appears.ogg"));
		//sounds[].inst = al_create_sample_instance(al_load_sample("")); // example to adding 

		for (int i = 0; i < SIZE_OF_SOUNDS; i++)
		{
			al_attach_sample_instance_to_mixer(Sound::sounds[i].inst, al_get_default_mixer());
		}

		return 1;
	}

	void play(int sound, ALLEGRO_PLAYMODE playmode)
	{
		if (!isInitialized)
			init();
		al_set_sample_instance_playmode(Sound::sounds[sound].inst, playmode);
		al_play_sample_instance(Sound::sounds[sound].inst);
	}

	void play(int sound)
	{
		play(sound, ALLEGRO_PLAYMODE_ONCE);
	}
}