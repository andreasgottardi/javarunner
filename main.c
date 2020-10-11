#include <stdio.h>
#include <windows.h>

#include "include/java.h"
#include "include/logging.h"


int wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{ 
    startvm();
    WriteToLog("Program finished.", LOG_DEBUG);
    return 0;
}