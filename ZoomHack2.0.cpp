#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <string>
#include <atlstr.h>
#include <iostream>
#include <dos.h>
#pragma warning(disable:4996)

uint8_t strContains(char* string, char* toFind)
{
	uint8_t slen = strlen(string);
	uint8_t tFlen = strlen(toFind);
	uint8_t found = 0;

	if (slen >= tFlen)
	{
		for (uint8_t s = 0, t = 0; s<slen; s++)
		{
			do {

				if (string[s] == toFind[t])
				{
					if (++found == tFlen) return 1;
					s++;
					t++;
				}
				else { s -= found; found = 0; t = 0; }

			} while (found);
		}
		return 0;
	}
	else return -1;
}

BOOL CALLBACK EnumWindowsProc(HWND hWnd, long lParam) {
	wchar_t buff[255];

	if (IsWindowVisible(hWnd)) {
		GetWindowText(hWnd, (LPWSTR)buff, 254);
		char name[255];
		char search[5] = "Zoom";
		char search2[5] = "zoom";
		wcstombs(name, buff, 255);
		if (strContains(name, search) || strContains(name, search2)) {
			wprintf(L"%s %s\n", L"found a Zoom instance, starting workaround...", buff);
			SendMessage(hWnd, WM_ACTIVATE, WA_CLICKACTIVE, (LPARAM)hWnd);
		}
	}

	return TRUE;
}

int main() {
	while (1) {
		EnumWindows(EnumWindowsProc, 0);
		Sleep(2000);
	}
	system("pause");
	return 0;
}
	/*if (_tcsstr(szProcessName, _T("Zoom")) != NULL || _tcsstr(szProcessName, _T("zoom")) != NULL)

	{
		SendMessage(hWnd, WM_ACTIVATE, WA_CLICKACTIVE, hWnd);
		_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);

	}*/

	// Release the handle to the process.
