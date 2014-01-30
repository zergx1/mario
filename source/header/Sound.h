#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


struct SoundStructure {
	ALLEGRO_SAMPLE_INSTANCE *inst;
};

namespace Sound{
	enum SOUNDS{ JUMP, MARIO_DIE, BREAK_BRICK, COIN, SIZE_OF_SOUNDS };	

	int init();
	void play(int sound);	// play once
	void play(int sound, ALLEGRO_PLAYMODE playmode);
}

