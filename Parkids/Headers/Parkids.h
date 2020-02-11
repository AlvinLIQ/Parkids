#pragma once
#include "Tools.h"
#include "../Maps/Headers/DrnMap.h"
#include <thread>

#define CurrentItem drnMap->ItemsInfo[drnMap->CurrentIndex]

class Parkids
{
public:
	DrnD2D* drnD2D;
	DrnMap* drnMap;
	Character* player;
	Character* monster;

	void SetCurrentItem(size_t newIndex)
	{
		drnMap->CurrentIndex = newIndex;
		player->CharacterPos.x = player->IsRight ? CurrentItem.left : CurrentItem.right - 32;
		player->CharacterPos.y = CurrentItem.top - 60;
	}

	Parkids(DrnD2D* drnd2d);
	~Parkids();
private:
	void Tick();
//	HANDLE threadHandle;
	void CountThread();
	LARGE_INTEGER oldCount = {};
	LARGE_INTEGER currentCount = {};
	LONGLONG passed = 0;
	std::thread mThread;
	

	bool isRunning = true;
};

