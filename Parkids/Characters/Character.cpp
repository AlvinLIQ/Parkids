#include "Headers/Character.h"


#define Highest 80
#define MaxStep 15

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
		IsJumping = TRUE;
		isHighestReached = false;
		jumpStep = MaxStep;
	}
	if (isHighestReached)
		Drop();
	else if (!jumpStep || CharacterPos.y <= CharacterRange.top)
		isHighestReached = true;
	else
		CharacterPos.y -= --jumpStep;
}

void Character::Drop()
{
	if (CharacterPos.y + jumpStep + 61 > CharacterRange.bottom)
	{
		CharacterPos.y = CharacterRange.bottom - 60;
		IsJumping = FALSE;
	}
	else
		CharacterPos.y += jumpStep++;
}

void Character::Walk()
{
	step++;
	if (step == 10)
	{
		step = 0;
		CharacterState = CharacterState != 1 ? 1 : 2;
	}
}

void Character::PrepareDraw()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		CharacterPos.x -= walkStep[IsJumping];
		Walk();

		IsRight = false;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		CharacterPos.x += walkStep[IsJumping];
		Walk();

		IsRight = true;
	}
	else
		CharacterState = 0;

	if (CharacterPos.x - walkStep[IsJumping] < CharacterRange.left)
		CharacterPos.x = CharacterRange.left;
	else if (CharacterPos.x + walkStep[IsJumping] > CharacterRange.right)
		CharacterPos.x = CharacterRange.right;

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
		else if (CharacterPos.y + 60 != CharacterRange.bottom)
		{
			Drop();
		}

		lastState = isKeyUp_Dwon;
	}
	
}