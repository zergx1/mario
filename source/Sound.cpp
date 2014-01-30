#pragma once
#include "header/Sound.h"

namespace Sound{

	SoundStructure * sounds;
	bool isInit = false;

	int init()
	{
		isInit = true;
		sounds = new SoundStructure[SIZE_OF_SOUNDS];

		sounds[JUMP].inst = al_create_sample_instance(al_load_sample("Audio/jump.ogg"));
		sounds[MARIO_DIE].inst = al_create_sample_instance(al_load_sample("Audio/mario_dies.ogg"));
		sounds[BREAK_BRICK].inst = al_create_sample_instance(al_load_sample("Audio/break_brick.ogg"));
		sounds[COIN].inst = al_create_sample_instance(al_load_sample("Audio/coin.ogg"));

		for (int i = 0; i < SIZE_OF_SOUNDS; i++)
		{
			al_attach_sample_instance_to_mixer(Sound::sounds[i].inst, al_get_default_mixer());
		}

		return 1;
	}

	void play(int sound, ALLEGRO_PLAYMODE playmode)
	{
		init();
		al_set_sample_instance_playmode(Sound::sounds[sound].inst, playmode);
		al_play_sample_instance(Sound::sounds[sound].inst);
	}

	void play(int sound)
	{
		play(sound, ALLEGRO_PLAYMODE_ONCE);
	}
}