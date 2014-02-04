#pragma once
#include "Text.h"
#include "BumpingBlockAnimation.h"
#include "DestroyBrickAnimation.h"
#include <vector>
using std::vector;
class Text;
class BumpingBlockAnimation;
class DestroyBrickAnimation;

extern int xOff; // for a map
extern Text globalText;
extern const int normalJump;
extern const int superJump;
extern float normalVel0;
extern float superVel0;
extern vector<BumpingBlockAnimation> bumpingBlockAnimation;
extern vector<DestroyBrickAnimation> destroyBrickAnimation;

extern const int BRICK_ID;
extern const int BRICK_DARK_ID;
extern const int EMPTY_ID;
extern const int EMPTY_BLACK_ID;
extern const int QUESTION_ID;
extern const int SOLID_ID;
extern const int COIN_ID;