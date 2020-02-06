#pragma once
#include <Windows.h>
#include <iostream>
#include "../../Headers/DrnD2D.h"

class Character
{
public:
	bool IsJumping = false;
	bool IsRight;

	float BaseX = 0;
	float BaseY = 0;

	std::wstring CharacterName;

	POINT CharacterPos;
	short CharacterState;

	ID2D1Bitmap1* CharacterBitmap[3];

	void Jump();
	void Jumping();

	void SetDirection(short newState)
	{
		if (newState < 2)
			isHighestReached = newState;
		else
			IsRight = newState & 1;
	}

	void PrepareDraw();

	Character(std::wstring characterName);
	~Character();
private:
	PTP_TIMER jumpTimer;
	LONG jumpStep = 0;
	bool lastState;
	int step;
	bool isHighestReached;
};

