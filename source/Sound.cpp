#pragma once
#include "header/Sound.h"

namespace Sound{

	SoundStructure * sounds;
	bool isInitialized = false;

	int init()
	{
		isInitialized = true;
		sounds = new SoundStructure[SIZE_OF_SOUNDS]; 
		for(int i = 0; i  <SIZE_OF_SOUNDS; i++)
		{
			sounds[i].index = 0;
			sounds[i].needSimultaneous = false;
			sounds[i].playing = false;
		}

		sounds[MUSIC].sample = al_load_sample("Audio/music.ogg");
		sounds[MUSIC_UNDERGROUND].sample = al_load_sample("Audio/musicDown.ogg");
		sounds[MUSIC_HURRY_UP].sample = al_load_sample("Audio/musicHurry.ogg");
		sounds[MUSIC_INVINCIBLE].sample = al_load_sample("Audio/musicInvcible.ogg");

		sounds[JUMP].sample = al_load_sample("Audio/jump.ogg");
		sounds[MARIO_DIE].sample = al_load_sample("Audio/mario_dies.ogg");

		sounds[BREAK_BRICK].sample = al_load_sample("Audio/break_brick.ogg");
		sounds[BREAK_BRICK].needSimultaneous = true;
		sounds[BUMP].sample = al_load_sample("Audio/bump.ogg");
		sounds[BUMP].needSimultaneous = true;
		sounds[COIN].sample = al_load_sample("Audio/coin.ogg");
		sounds[COIN].needSimultaneous = true;

		sounds[HURRY].sample = al_load_sample("Audio/Hurry.ogg");
		sounds[WIN].sample = al_load_sample("Audio/win.ogg");
		sounds[GAME_OVER].sample = al_load_sample("Audio/Game Over.ogg");
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

	void stopBackgroundMusic()
	{
		if (!isInitialized)
			init();
		if (sounds[MUSIC].playing)
			al_stop_sample_instance(sounds[MUSIC].inst[0]);
		if (sounds[MUSIC_INVINCIBLE].playing)
			al_stop_sample_instance(sounds[MUSIC_INVINCIBLE].inst[0]);
		if (sounds[MUSIC_HURRY_UP].playing)
			al_stop_sample_instance(sounds[MUSIC_HURRY_UP].inst[0]);
		if (sounds[MUSIC_UNDERGROUND].playing)
			al_stop_sample_instance(sounds[MUSIC_UNDERGROUND].inst[0]);

	}

	void playBackgroundMusic(int sound)
	{
		stopBackgroundMusic();
		al_set_sample_instance_playmode(sounds[sound].inst[0], ALLEGRO_PLAYMODE_LOOP);
		al_play_sample_instance(sounds[sound].inst[0]);
		sounds[sound].playing = true;
	}
}