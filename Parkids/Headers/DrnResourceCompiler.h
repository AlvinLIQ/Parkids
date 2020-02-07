#pragma once
#include <stdio.h>
#include <string.h>

typedef struct
{
	float left;
	float top;
	float right;
	float bottom;
	wchar_t name[10];
} DrnResourceItemInfo;

class DrnResourceCompiler
{
public:
	static size_t FindAll(const wchar_t* source, const wchar_t target, size_t* list, size_t listSize)
	{
		size_t sLen = wcslen(source), count = 0;
		for (size_t i = 0; i < sLen; i++)
		{
			if (source[i] == target)
			{
				if (listSize == count)
					break;
				list[count++] = i;
			}
		}
		return count;
	}

	static DrnResourceItemInfo GetFirstItemInfo(const wchar_t* source)
	{
		DrnResourceItemInfo resultItem;
		swscanf_s(source, L"[ %s ]\n", resultItem.name, 10);
		swscanf_s(source, L"%*[^:]:%f %f\ny:%f %f", &resultItem.left, &resultItem.right, &resultItem.top, &resultItem.bottom);

		return resultItem;
	}

	static void GetItemsInfo(const wchar_t* source, DrnResourceItemInfo* infoList, size_t* list, size_t* listSize, float x = 1.0f, float y = 1.0f)
	{
		size_t sLen = wcslen(source), count = 0;
		for (size_t i = 0; i < sLen; i++)
		{
			if (source[i] == L'[')
			{
				if (count == *listSize)
					return;
				swscanf_s(&source[i], L"[ %s ]\n", infoList[count].name, 10);
				swscanf_s(&source[i], L"%*[^:]:%f %f\ny:%f %f", &infoList[count].left, &infoList[count].right, &infoList[count].top, &infoList[count].bottom);
				infoList[count].left *= x;
				infoList[count].top *= y;
				infoList[count].right *= x;
				infoList[count].bottom *= y;
				count++;
			}
		}
		*listSize = count;
	}
};