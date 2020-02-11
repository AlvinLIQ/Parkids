#include "Headers/Parkids.h"

D2D1_SIZE_F d2dSize = {};

Parkids::Parkids(DrnD2D* drnd2d)
{
	drnD2D = drnd2d;

	player = new Character(L"Blueman-");
	for (int i = 0; i < 3; i++)
		drnD2D->LoadBitmapFromFilename((L"Resources/" + player->CharacterName + (wchar_t)(i + 49) + L".png").c_str(), &player->CharacterBitmap[i]);

	d2dSize = drnD2D->d2dContext->GetSize();
	drnMap = new DrnMap(ReadFileW(L"Resources/Maps/Map1.txt"), d2dSize, drnD2D);
	SetCurrentItem(0);

//	threadHandle = CreateThread(0, 0, &Parkids::CountThread, NULL, 0, NULL);
	mThread = std::thread(&Parkids::CountThread, this);
	mThread.detach();
}

Parkids::~Parkids()
{
	isRunning = false;
	if (mThread.joinable())
		mThread.join();
}

void Parkids::CountThread()
{
	while (isRunning)
	{
		QueryPerformanceCounter(&currentCount);
		passed += currentCount.QuadPart - oldCount.QuadPart;
		oldCount = currentCount;
		if (passed > 160000)
		{
			passed = 0LL;
			Tick();
		}
	}
}

void Parkids::Tick()
{
	drnMap->GetRange(player->CharacterPos, &player->CharacterRange);
	player->PrepareDraw();
}