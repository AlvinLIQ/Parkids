#include "Headers/Parkids.h"
#include "UI/Headers/MainPage.h"

#ifndef UNICODE
#define UNICODE
#endif

using namespace Controls;

Murrela* murrela;
Parkids* parkids;
Grid* content;

bool drew = false;
/*
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
*/
PTP_TIMER d2dTimer;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE pInstance, LPWSTR Param, int ParamNum)
{
	CoreApp* coreApp = new CoreApp(hInstance);
	murrela = coreApp->murrela;
//	parkids = new Parkids(coreApp->murrela);
	
//	mContainer->AppendItem((Control*)parkids);
	coreApp->content = (Control*)new MainPage(murrela);
	
	coreApp->Run();
	delete coreApp;
	coreApp = nullptr;

	/*
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
	murrela = new Murrela(hwnd);
	while (murrela->d2dContext == nullptr);
	parkids = new Parkids(murrela);
	content = new Grid(murrela, Stretch);
	content->AppendItem((Control*)new Button(L"Text", murrela, Left | Top));
	MSG msg = {};
	while (GetMessage(&msg, hwnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	*/
	return 0;
}
/* Deprecated
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
//		murrela->d2dContext->SaveDrawingState(murrela->d2dStateBlock.Get());
		murrela->d2dContext->BeginDraw();
		murrela->d2dContext->Clear(D2D1::ColorF(D2D1::ColorF::White));
		ID2D1SolidColorBrush* txtBrush;
		murrela->d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &txtBrush);
		

		if (!drew)
		{
			parkids->drnMap->DrawAll();
		}
		murrela->d2dContext->DrawBitmap(parkids->player->CharacterBitmap[parkids->player->CharacterState], parkids->player->GetRectF());
		if (parkids->drnMap->IsInside(parkids->player->CharacterPos, 0))
		{
			murrela->d2dContext->DrawTextW(L"Congratulations!\nyou passed this level.", 40, murrela->txtFormat.Get(), D2D1::RectF(0, 0, 500, 0), txtBrush);
		}
		if (parkids->drnMap->IsInside(parkids->player->CharacterPos, 3))
		{
			murrela->d2dContext->DrawTextW(L"Oh, you lost.", 14, murrela->txtFormat.Get(), D2D1::RectF(0, 0, 500, 0), txtBrush);
		}
//		content->Draw();

		murrela->d2dContext->EndDraw();
//		murrela->d2dContext->RestoreDrawingState(murrela->d2dStateBlock.Get());
		murrela->dxgiSwapChain->Present(1, 0);
	}
	case WM_SIZE:
	{
		if (parkids != nullptr&& parkids->drnMap != nullptr)
		{
			RECT wndSize;
			GetClientRect(hwnd, &wndSize);
			D2D1_SIZE_F newSize = D2D1::SizeF((float)(wndSize.right - wndSize.left), (float)(wndSize.bottom - wndSize.top));
			parkids->drnMap->Resize(newSize);
			murrela->SetSize(newSize);
			content->UpdateLayout();
		}
		if (murrela != nullptr)
		{
			
		}
//		murrela->dxgiSurface->Release();
//		murrela->SetTargetBitmap();
	}
	return 0;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}*/