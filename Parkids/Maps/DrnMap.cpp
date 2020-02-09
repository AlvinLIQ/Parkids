#include "Headers/DrnMap.h"

DrnMap::DrnMap(const wchar_t* mapSource, D2D1_SIZE_F nSize, DrnD2D* drnd2d)
{
	mapSize = nSize;
	DrnResourceCompiler::GetItemsInfo(mapSource, ItemsInfo, IndexList, &ItemCount, nSize.width, nSize.height);
	drnD2D = drnd2d;
	CurrentIndex = 0;
}

DrnMap::~DrnMap()
{

}

size_t DrnMap::FindAbove(float x, float y)
{
	size_t result = NOT_FOUND;
	float lastPosY = 0;
	for (size_t i = 0; i < ItemCount; i++)
		if (x > ItemsInfo[i].left && x + 32 < ItemsInfo[i].right && ItemsInfo[i].bottom < y && ItemsInfo[i].bottom > lastPosY)
		{
			lastPosY = ItemsInfo[i].bottom;
			result = i;
		}

	return result;
}

size_t DrnMap::FindBelow(float x, float y)
{
	size_t result = NOT_FOUND;
	float lastPosY = std::numeric_limits<float>::max();
	for (size_t i = 0; i < ItemCount; i++)
		if (x + 8 > ItemsInfo[i].left && x + 20 < ItemsInfo[i].right && ItemsInfo[i].top > y && ItemsInfo[i].top < lastPosY)
		{
			lastPosY = ItemsInfo[i].top;
			result = i;
		}

	return result;
}

void DrnMap::GetRange(D2D1_POINT_2F pos, D2D1_RECT_F* pRange)
{
	pos.y += 60;
	bool changed[4] = { false };
	float* ppRange = (float*)pRange, offsets[] = {0.0f, 0.0f, mapSize.width, mapSize.height};
	size_t i;
	for (i = 0; i < ItemCount; i++)
	{
		if (ItemsInfo[i].bottom >= pos.y && ItemsInfo[i].top < pos.y)
		{
			if (ItemsInfo[i].left >= pos.x + 28)
			{
				if ((changed[2] && ItemsInfo[i].left < pRange->right) || !changed[2])
				{
					pRange->right = ItemsInfo[i].left - 32;
					changed[2] = true;
				}
			}
			else if (ItemsInfo[i].right <= pos.x + 15)
			{
				if ((changed[0] && ItemsInfo[i].right > pRange->left) || !changed[0])
				{
					pRange->left = ItemsInfo[i].right;
					changed[0] = true;
				}
			}
		}
		else if(ItemsInfo[i].left - 28 <= pos.x && (ItemsInfo[i].right >= pos.x + 10 || ItemsInfo[i].right >= pos.x + 28))
		{
			if (ItemsInfo[i].top >= pos.y - 60)
			{
				if ((changed[3] && ItemsInfo[i].top < pRange->bottom) || !changed[3])
				{
					pRange->bottom = ItemsInfo[i].top;
					changed[3] = true;

					CurrentIndex = i;
				}
			}
			else if (ItemsInfo[i].bottom <= pos.y)
			{
				if ((changed[1] && ItemsInfo[i].bottom > pRange->top) || !changed[1])
				{
					pRange->top = ItemsInfo[i].bottom;
					changed[1] = true;
				}
			}
		}
	}
	
	for (i = 0; i < 4; i++)
		if (!changed[i])
		{
			ppRange[i] = offsets[i];
		}
}

bool DrnMap::IsInside(D2D1_POINT_2F pos, size_t itemIndex)
{
	return (pos.x > ItemsInfo[itemIndex].left&& pos.x + 32 < ItemsInfo[itemIndex].right && pos.y < ItemsInfo[itemIndex].bottom && pos.y > ItemsInfo[itemIndex].top);
}

void DrnMap::DrawAll()
{
	ID2D1SolidColorBrush* itemBrush;
	ID2D1SolidColorBrush* currentBrush;
	drnD2D->d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &itemBrush);
	drnD2D->d2dContext->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &currentBrush);
	for (size_t i = 0; i < ItemCount; i++)
	{
		drnD2D->d2dContext->DrawRectangle(D2D1::RectF(ItemsInfo[i].left, ItemsInfo[i].top, ItemsInfo[i].right, ItemsInfo[i].bottom), i == CurrentIndex ? currentBrush : itemBrush);
	}
}
