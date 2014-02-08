#pragma once
#include "Text.h"
#include "BumpingBlockAnimation.h"
#include "DestroyBrickAnimation.h"
#include "JumpingCoinAnimation.h"
#include "Settings.h"
#include <vector>
using std::vector;
class Settings;
class Text;
class BumpingBlockAnimation;
class DestroyBrickAnimation;
class JumpingCoinAnimation;

extern int xOff; // for a map
extern Text globalText;
extern float normalVel0;
extern float superVel0;
extern int currentPlayer;
extern vector<BumpingBlockAnimation> bumpingBlockAnimation;
extern vector<JumpingCoinAnimation> jumpingCoinAnimation;
extern vector<DestroyBrickAnimation> destroyBrickAnimation;
extern Settings settings;

extern int WIDTH;
extern int HEIGHT;

extern const int BRICK_ID;
extern const int BRICK_DARK_ID;
extern const int EMPTY_ID;
extern const int EMPTY_BLACK_ID;
extern const int QUESTION_ID;
extern const int SOLID_ID;
extern const int COIN_ID;