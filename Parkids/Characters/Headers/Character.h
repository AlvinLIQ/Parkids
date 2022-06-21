#pragma once
#include <Windows.h>
#include <iostream>
#include "../../Headers/Murrela/Src/Core/Murrela/Headers/Murrela.h"

#define WalkStep 1

class Character
{
public:
	BOOL IsJumping = FALSE;
	bool IsRight;

	std::wstring CharacterName;

	D2D1_POINT_2F CharacterPos;
	short CharacterState;

	D2D1_RECT_F CharacterRange = {};

	ID2D1Bitmap1* CharacterBitmap[3];

	void Jump();
	void Drop();

	void SetDirection(short newState)
	{
		if (newState & 2)
			IsRight = newState & 1;
		else
			isHighestReached = newState & 1;
	}
	short GetDirection()//1 down 2 up 4 left 8 right
	{
		return (isHighestReached ? 1 : 2) + (IsRight ? 8 : 4);
	}

	float GetX()
	{
		return CharacterPos.x;
	}
	float GetY()
	{
		return CharacterPos.y;
	}

	D2D1_RECT_F GetRectF()
	{
		return D2D1::RectF(GetX(), GetY(), GetX() + 32, GetY() + 64);
	}

	void PrepareDraw();

	Character(std::wstring characterName);
	~Character();
private:
	const float walkStep[2] = {2, 1.5};

	PTP_TIMER jumpTimer;
	LONG jumpStep = 0;
	bool lastState;
	int step = 0;
	bool isHighestReached;

	void Walk();
};

