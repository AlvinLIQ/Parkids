#include "Headers/DrnMap.h"

DrnMap::DrnMap(const wchar_t* mapSource, D2D1_SIZE_F nSize, DrnD2D* drnd2d)
{
	DrnResourceCompiler::GetItemsInfo(mapSource, ItemsInfo, IndexList, &ItemCount, nSize.width, nSize.height);
	drnD2D = drnd2d;
}

DrnMap::~DrnMap()
{

}

void DrnMap::DrawAll()
{
	ID2D1SolidColorBrush* itemBrush;
	drnD2D->d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &itemBrush);
	for (size_t i = 0; i < ItemCount; i++)
	{
		drnD2D->d2dContext->DrawRectangle(D2D1::RectF(ItemsInfo[i].left, ItemsInfo[i].top, ItemsInfo[i].right, ItemsInfo[i].bottom), itemBrush);
	}
}
