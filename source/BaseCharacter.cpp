#include "header/BaseCharacter.h"

BaseCharacter::BaseCharacter(void)
{
}

BaseCharacter::~BaseCharacter(void)
{
}

void BaseCharacter::Init(Text *t)
{
	live = true;
	show = true;
	canTakeCoin = false;
	text = t;
}

void BaseCharacter::Update()
{
	
}


void BaseCharacter::Draw(int flag)
{

}

void BaseCharacter::Hit()
{

}

void BaseCharacter::KillByShot()
{
	
}

void BaseCharacter::Kill()
{

}

void BaseCharacter::takeCoin()
{

}

void BaseCharacter::collisionWithOther(BaseCharacter* character)
{

}

void BaseCharacter::takeItem()
{

}

void BaseCharacter::floatingScore(int x, int y, char *score)
{
	al_draw_text(font, al_map_rgb(255, 255, 255), x, y, ALLEGRO_ALIGN_CENTRE, score);
}

void BaseCharacter::floatingScore(int x, int y, int score)
{
	int size = 1;
	int divisor = 1;
	while (score / divisor != 0)
	{
		divisor *= 10;
		size++;
	}
	int temp = score;
	char *charScore = new char[size + 1];
	for (int i = 0; i < size; i++)
	{
		charScore[i] = (char)(temp / divisor) + 48;
		if (temp / divisor != 0)
			temp %= divisor;
		divisor /= 10;
	}
	charScore[size] = '\0';	// end of array
	floatingScore(x, y, charScore);
}
