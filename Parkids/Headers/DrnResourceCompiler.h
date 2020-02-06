#pragma once
#include <stdio.h>

typedef struct
{
	float left;
	float top;
	float right;
	float bottom;
	wchar_t name[10];
} DrnResourceItemInfo;

DrnResourceItemInfo GetFirstItemInfo(const wchar_t* source)
{
	DrnResourceItemInfo resultItem;
	swscanf_s(source, L"[ %s ]\n", resultItem.name, 10);
	swscanf_s(source, L"%*[^:]:%f %f\ny:%f %f", &resultItem.left, &resultItem.right, &resultItem.top, &resultItem.bottom);

	return resultItem;
}