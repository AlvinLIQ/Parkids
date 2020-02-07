#pragma once

#include "../../Headers/DrnResourceCompiler.h"
#include "../../Characters/Headers/Character.h"

#define itemMaxSize 20

class DrnMap
{
public:
	DrnMap(const wchar_t* mapSource, D2D1_SIZE_F nSize, DrnD2D* drnd2d);
	~DrnMap();

	DrnResourceItemInfo ItemsInfo[itemMaxSize];
	size_t ItemCount = itemMaxSize;

	void DrawAll();
private:
	DrnD2D* drnD2D;
	size_t IndexList[itemMaxSize];
};
