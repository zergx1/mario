#include "header/BaseCharacter.h"

BaseCharacter::BaseCharacter(void)
{
}

BaseCharacter::~BaseCharacter(void)
{
}

void BaseCharacter::Init()
{
	live = true;
	show = true;
	canTakeCoin = false;
	killsOtherMonsters = false;
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

void BaseCharacter::collisionWithOtherMonster(BaseCharacter* character)
{

}

bool BaseCharacter::CheckIfKillPlayer(BaseCharacter* character)
{
	return true;
}

void BaseCharacter::takeItem(BaseCharacter* character)
{

}
