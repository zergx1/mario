#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#pragma once
#include "Text.h"
#include "SimpleAnimation.h"
#include "Settings.h"

class Settings;
class Text;
class SimpleAnimation;

extern int xOff; // for a map
extern Text globalText;
extern SimpleAnimation simpleAnimation;
extern Settings settings;

extern const int BRICK_ID;
extern const int EMPTY_ID;
extern const int QUESTION_ID;
extern const int SOLID_ID;
extern const int COIN_ID;
#endif