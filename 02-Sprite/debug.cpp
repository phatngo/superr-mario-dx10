#include <windows.h>
#include "debug.h"
#include <string>
using namespace std;

HWND _hwnd = NULL;

void DebugOut(wchar_t *fmt, ...)
{
	wchar_t s[4096];
	VA_PRINTS(s);
	OutputDebugString(s);
}

void DebugOutTitle(wchar_t *fmt, ...)
{
	wchar_t s[1024];
	VA_PRINTS(s);
	SetWindowText(_hwnd, s);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}

LPCWSTR ToLPCWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring* w = new wstring(wcstring);

	// delete wcstring   // << can I ? 
	return w->c_str();
}



//////////////////////////////////////////