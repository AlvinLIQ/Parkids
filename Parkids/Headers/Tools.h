#pragma once

#include <stdio.h>

static wchar_t* ReadFileW(const wchar_t* fileName)
{
	FILE* fp;
	_wfopen_s(&fp, fileName, L"r");
	fseek(fp, 0L, SEEK_END);
	long fSize = ftell(fp), i = 0;
	fseek(fp, 0L, SEEK_SET);

	wchar_t* rBuffer = new wchar_t[fSize], cWChar;
	while (i < fSize)
	{
		cWChar = fgetwc(fp);
		if (cWChar != L'\r')
			rBuffer[i++] = cWChar;
		else
			fSize--;
	}
	
	rBuffer[i] = 0;
	fclose(fp);

	return rBuffer;
}