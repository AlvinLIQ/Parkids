#include "Headers/Character.h"


#define Highest 80
#define MaxStep 13

Character::Character(std::wstring characterName)
{
	CharacterName = characterName;
}

Character::~Character()
{

}

void Character::Jump()
{
	if (!IsJumping)
	{
		IsJumping = true;
		isHighestReached = false;
		jumpStep = MaxStep;
	}
	Jumping();
}

void Character::Jumping()
{
	if (!jumpStep)
		isHighestReached = true;

	if (isHighestReached)
	{
		if (!CharacterPos.y)
			IsJumping = false;
		else
			CharacterPos.y -= jumpStep++;
	}
	else
		CharacterPos.y += --jumpStep;
}

void Character::PrepareDraw()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		CharacterPos.x += 1;
		step++;
		if (step == 10)
		{
			step = 0;
			CharacterState = CharacterState != 1 ? 1 : 2;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		CharacterPos.x -= 1;
		step++;
		if (step == 10)
		{
			step = 0;
			CharacterState = CharacterState != 1 ? 1 : 2;
		}
	}
	else
		CharacterState = 0;

	bool isKeyUp_Dwon = GetAsyncKeyState(VK_UP);
	if (!isKeyUp_Dwon || !lastState || IsJumping)
	{
		if (isKeyUp_Dwon)
		{
			Jump();
			CharacterState = 1;
		}
		else if (IsJumping)
		{
			SetDirection(1);
			Jump();
			CharacterState = 1;
		}
		lastState = isKeyUp_Dwon;

	}
}