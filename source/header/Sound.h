#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

const int MAX_SIMULTANEOUS = 10;

struct SoundStructure {
	bool needSimultaneous;
	ALLEGRO_SAMPLE_INSTANCE *inst[MAX_SIMULTANEOUS];
	ALLEGRO_SAMPLE * sample;
	int index;
	bool playing;
};

namespace Sound{
	enum SOUNDS{	PIPE,JUMP, MARIO_DIE,
					MUSIC, MUSIC_HURRY_UP, MUSIC_UNDERGROUND, MUSIC_INVINCIBLE,
					BREAK_BRICK, COIN, BUMP,
					POWER_UP, POWER_DOWN, POWER_APPEARS,
					GAIN_LIFE, HURRY, WIN, GAME_OVER,
					SIZE_OF_SOUNDS };	
	int init();
	void play(int sound);	// play once
	void play(int sound, ALLEGRO_PLAYMODE playmode);
	void stopBackgroundMusic();
	void playBackgroundMusic(int sound);
}

