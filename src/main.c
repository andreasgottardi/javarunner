#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "include/java.h"
#include "include/logging.h"


int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	LPWSTR *szArglist;
	int nrofargs;
	szArglist = CommandLineToArgvW(GetCommandLineW(), &nrofargs);

	char libdir[MAX_PATH];
	libdir[0] = '\0';

	char jvmpath[MAX_PATH];
	jvmpath[0] = '\0';

	for (size_t i = 0; i < nrofargs; i++) {
		if(wcscmp(L"-l", szArglist[i]) == 0){
			wcstombs(libdir, szArglist[i + 1], wcslen(szArglist[i + 1]));
			i++;
		}
	}

	for (size_t i = 0; i < nrofargs; i++) {
		if(wcscmp(L"-j", szArglist[i]) == 0){
			wcstombs(jvmpath, szArglist[i + 1], wcslen(szArglist[i + 1]));
			i++;
		}
	}

	if(strlen(libdir) == 0){
		strcat(libdir, "..\\lib");
	}

	if(strlen(libdir) == 0){
		strcat(jvmpath, "..\\jre\\bin\\server\\jvm.dll");
	}

	startvm(libdir, jvmpath);

	return 0;
	
}