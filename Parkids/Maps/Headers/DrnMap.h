#pragma once

#include "../../Headers/DrnResourceCompiler.h"
#include "../../Characters/Headers/Character.h"

#define itemMaxSize 20
#define NOT_FOUND (size_t)-1

class DrnMap
{
public:
	DrnMap(const wchar_t* mapSource, D2D1_SIZE_F nSize, Murrela* murla);
	~DrnMap();

	DrnResourceItemInfo ItemsInfo[itemMaxSize];
	size_t ItemCount = itemMaxSize;
	size_t CurrentIndex;

	size_t FindAbove(float x, float y);
	size_t FindBelow(float x, float y);
	void GetRange(D2D1_POINT_2F pos, D2D1_RECT_F* pRange);
	void DrawAll();

	void Resize(D2D1_SIZE_F newSize);

	bool IsInside(D2D1_POINT_2F pos, size_t itemIndex);
private:
	Murrela* murrela;
	D2D1_SIZE_F mapSize;
	size_t IndexList[itemMaxSize];
};
