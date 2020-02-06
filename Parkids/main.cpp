#include <Windows.h>
#include "Characters/Headers/Character.h"
#include "Headers/DrnResourceCompiler.h"

#ifndef UNICODE
#define UNICODE
#endif

DrnD2D* drnD2D;
Character* player;
DrnResourceItemInfo itemInfo;

bool waitingForKey = false;

const wchar_t resStr[] = 
L"[ land.png ]\n"
L"x:0.2 0.5\n"
L"y:0.9 1.0";

D2D1_SIZE_F d2dSize = {};

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPWSTR Param, int ParamNum)
{
	WNDCLASS wc = {};
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"Parkids";

	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(0, wc.lpszClassName, wc.lpszClassName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, NULL, hInstance, NULL);

	player = new Character(L"Blueman-");
	ShowWindow(hwnd, ParamNum);
	drnD2D = new DrnD2D(hwnd);
	while (drnD2D->txtFormat == nullptr);
	for (int i = 0; i < 3; i++)
		drnD2D->LoadBitmapFromFilename((L"Resources/" + player->CharacterName + (wchar_t)(i + 49) + L".png").c_str(), &player->CharacterBitmap[i]);

	itemInfo = GetFirstItemInfo(resStr);

	MSG msg = {};
	while (GetMessage(&msg, hwnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		delete drnD2D;
		exit(0);

	case WM_PAINT:
	{
		if (waitingForKey)
		{
			waitingForKey = !GetAsyncKeyState(VK_RETURN);
			return 0;
		}
		player->PrepareDraw();

		drnD2D->d2dContext->BeginDraw();
		drnD2D->d2dContext->Clear();
		ID2D1SolidColorBrush* txtBrush;
		drnD2D->d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &txtBrush);

		if (!d2dSize.height)
		{
			d2dSize = drnD2D->d2dContext->GetSize();
			itemInfo.left *= d2dSize.width;
			itemInfo.top *= d2dSize.height;
			itemInfo.right *= d2dSize.width;
			itemInfo.bottom *= d2dSize.height;
		}
		
		drnD2D->d2dContext->DrawRectangle(D2D1::RectF(itemInfo.left, itemInfo.top, itemInfo.right, itemInfo.bottom), txtBrush);
		if (!player->IsJumping)
		{
			player->BaseX = itemInfo.left;
			player->BaseY = itemInfo.top - 60;
		}
		float left = player->BaseX - player->CharacterPos.x,
			top = player->BaseY - player->CharacterPos.y;
		if ((left + 24 < itemInfo.left || left > itemInfo.right - 8) && player->CharacterPos.y <= 0)
		{
			if (top > itemInfo.bottom)
			{
				drnD2D->d2dContext->DrawTextW(L"       You died\nPress Enter To Continue", 40, drnD2D->txtFormat.Get(), D2D1::RectF(0, 0, 300, 48), txtBrush);
				player->CharacterPos.x = 0;
				player->CharacterPos.y = 0;
				waitingForKey = true;
			}
			else
			{
				player->CharacterPos.y -= 100;
				player->SetDirection(1);
				player->Jumping();
			}
		}
		drnD2D->d2dContext->DrawBitmap(player->CharacterBitmap[player->CharacterState], D2D1::RectF(left, top, left + 32, top + 64));
		drnD2D->d2dContext->EndDraw();
		drnD2D->dxgiSwapChain->Present(1, 0);
	}
	case WM_SIZE:
	{
//			drnD2D->dxgiSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_NONPREROTATED);
//			drnD2D->dxgiSurface->Release();
//			drnD2D->SetTargetBitmap();
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}