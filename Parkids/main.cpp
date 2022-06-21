#include "Headers/Parkids.h"
#include "Headers/Murrela/Src/Core/Murrela/Headers/Controls.h"

#ifndef UNICODE
#define UNICODE
#endif

using namespace Controls;

Murrela* drnD2D;
Parkids* parkids;
Grid* content;

bool drew = false;

const wchar_t resStr[] =
L"[ land.png ]\n"
L"x:0.2 0.5\n"
L"y:0.9 1.0\n"
L"[ land.png ]\n"
L"x:0.5 0.6\n"
L"y:0.73 1.0\n"
L"[ land.png ]\n"
L"x:0.1 0.2\n"
L"y:0.85 1.0\n"
L"[ land.png ]\n"
L"x:0.0 0.1\n"
L"y:0.8 1.0\n"
L"[ land.png ]\n"
L"x:0.25 0.3\n"
L"y:0.8 0.82\n"
L"[ land.png ]\n"
L"x:0.33 0.38\n"
L"y:0.8 0.82\n"
L"[ land.png ]\n"
L"x:0.41 0.46\n"
L"y:0.8 0.82";

PTP_TIMER d2dTimer;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void CALLBACK drawTimer(PTP_CALLBACK_INSTANCE instance, PVOID context, PTP_TIMER timer);

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

	ShowWindow(hwnd, ParamNum);
	drnD2D = new Murrela(hwnd);
	while (drnD2D->d2dContext == nullptr);
	parkids = new Parkids(drnD2D);
	content = new Grid(drnD2D, Stretch);
	content->AppendItem((Control*)new Button(L"Text", drnD2D, Left | Top));
	MSG msg = {};
	while (GetMessage(&msg, hwnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


void CALLBACK drawTimer(PTP_CALLBACK_INSTANCE instance, PVOID context, PTP_TIMER timer)
{
	parkids->drnMap->GetRange(parkids->player->CharacterPos, &parkids->player->CharacterRange);
	parkids->player->PrepareDraw();
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		delete parkids;
		exit(0);

	case WM_PAINT:
	{
		if (GetAsyncKeyState(VK_BACK))
		{
			parkids->player->IsRight = false;
			parkids->SetCurrentItem(0);
		}
//		drnD2D->d2dContext->SaveDrawingState(drnD2D->d2dStateBlock.Get());
		drnD2D->d2dContext->BeginDraw();
		drnD2D->d2dContext->Clear(D2D1::ColorF(D2D1::ColorF::White));
		ID2D1SolidColorBrush* txtBrush;
		drnD2D->d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &txtBrush);
		
		float left = parkids->player->GetX(),
			top = parkids->player->GetY();


		if (!drew)
		{
			parkids->drnMap->DrawAll();
		}
		drnD2D->d2dContext->DrawBitmap(parkids->player->CharacterBitmap[parkids->player->CharacterState], parkids->player->GetRectF());
		if (parkids->drnMap->IsInside(parkids->player->CharacterPos, 0))
		{
			drnD2D->d2dContext->DrawTextW(L"Congratulations!\nyou passed this level.", 40, drnD2D->txtFormat.Get(), D2D1::RectF(0, 0, 500, 0), txtBrush);
		}
		if (parkids->drnMap->IsInside(parkids->player->CharacterPos, 3))
		{
			drnD2D->d2dContext->DrawTextW(L"Oh, you lost.", 14, drnD2D->txtFormat.Get(), D2D1::RectF(0, 0, 500, 0), txtBrush);
		}
//		content->Draw();

		drnD2D->d2dContext->EndDraw();
//		drnD2D->d2dContext->RestoreDrawingState(drnD2D->d2dStateBlock.Get());
		drnD2D->dxgiSwapChain->Present(1, 0);
	}
	case WM_SIZE:
	{
		if (parkids != nullptr && parkids->drnMap != nullptr)
		{
			RECT wndSize;
			GetClientRect(hwnd, &wndSize);
			D2D1_SIZE_F newSize = D2D1::SizeF((float)(wndSize.right - wndSize.left), (float)(wndSize.bottom - wndSize.top));
			parkids->drnMap->Resize(newSize);
			drnD2D->SetSize(newSize);
			content->UpdateLayout();
		}
		if (drnD2D != nullptr)
		{
			
		}
//		drnD2D->dxgiSurface->Release();
//		drnD2D->SetTargetBitmap();
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}