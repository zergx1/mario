#pragma once
#include "header/GlobalObjects.h"
#include <cmath>

vector<BumpingBlockAnimation> bumpingBlockAnimation; // simple animation which which wasn't possible to put on the map
vector<DestroyBrickAnimation> destroyBrickAnimation;
vector<JumpingCoinAnimation> jumpingCoinAnimation;
Text globalText;	// TOP text - statistic
int xOff;			//	xOFF for map
Settings settings;

float normalVel0;	// = sqrt(settings.getIntOption("normal_jump") * 16 * 2 * 0.16);
float superVel0;	// = sqrt(settings.getIntOption("super_jump") * 16 * 2 * 0.16);

// ID of the blocks
const int BRICK_ID = 49;
const int BRICK_DARK_ID = 51;
const int EMPTY_ID = 44;
const int EMPTY_BLACK_ID = 0;
const int QUESTION_ID = 229;
const int SOLID_ID = 12; //  after destroy quote block
const int COIN_ID = 232;
