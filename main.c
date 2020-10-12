#include <stdio.h>
#include <windows.h>

#include "include/java.h"
#include "include/logging.h"

int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	LPWSTR *szArglist;
	int nrofargs;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nrofargs);
	char libdir[MAX_PATH];

	for (size_t i = 0; i < nrofargs; i++) {
		if(wcscmp(L"-l", szArglist[i]) == 0){
			wcstombs(libdir, szArglist[i + 1], wcslen(szArglist[i + 1]));
			i++;
		}
	}
	startvm(libdir);
	return 0;
}