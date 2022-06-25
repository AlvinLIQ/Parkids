#include "Headers/Parkids.h"

D2D1_SIZE_F d2dSize = {};

Parkids::Parkids(Murrela* murla) : Control(murla, Controls::Stretch)
{
	murrela = murla;
	player = new Character(L"Blueman-");
	for (int i = 0; i < 3; i++)
		murrela->LoadBitmapFromFilename((L"Resources/" + player->CharacterName + (wchar_t)(i + 49) + L".png").c_str(), &player->CharacterBitmap[i]);

	d2dSize = murrela->d2dContext->GetSize();
	drnMap = new DrnMap(ReadFileW(L"Resources/Maps/Map1.txt"), d2dSize, murrela);
	SetCurrentItem(0);

//	threadHandle = CreateThread(0, 0, &Parkids::CountThread, NULL, 0, NULL);
	Tick();
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

void Parkids::Draw()
{
	if (GetAsyncKeyState(VK_BACK))
	{
		this->player->IsRight = false;
		this->SetCurrentItem(0);
	}
	//		murrela->d2dContext->SaveDrawingState(murrela->d2dStateBlock.Get());
	ID2D1SolidColorBrush* txtBrush;
	murrela->d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &txtBrush);

	this->drnMap->DrawAll();

	murrela->d2dContext->DrawBitmap(this->player->CharacterBitmap[this->player->CharacterState], this->player->GetRectF());
	if (this->drnMap->IsInside(this->player->CharacterPos, 0))
	{
		murrela->d2dContext->DrawTextW(L"Congratulations!\nyou passed this level.", 40, murrela->txtFormat.Get(), D2D1::RectF(0, 0, 500, 0), txtBrush);
	}
	if (this->drnMap->IsInside(this->player->CharacterPos, 3))
	{
		murrela->d2dContext->DrawTextW(L"Oh, you lost.", 14, murrela->txtFormat.Get(), D2D1::RectF(0, 0, 500, 0), txtBrush);
	}
}