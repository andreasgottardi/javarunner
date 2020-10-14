#include <stdio.h>
#include <time.h>
#include <windows.h>

#include "include/logging.h"

int WriteToLog(char *str, DWORD mode)
{

	time_t timer;
	char timebuff[26];
	struct tm* tm_info;
	FILE *log;
	char* lmt;

	if(mode == LOG_ERROR){
		lmt = "ERROR";
	} else if (mode == LOG_INFO) {
		lmt = "INFO";
	} else if (mode == LOG_DEBUG) {
		lmt = "DEBUG";
	}

	time(&timer);
	tm_info = localtime(&timer);
	strftime(timebuff, 26, "%Y-%m-%d %H:%M:%S", tm_info);
	log = _wfopen(L"logs\\svc.log", L"a+");

	if (log == NULL){
		return -1;
	}
	fprintf(log, "[%s] [%s] - %s\n", lmt, timebuff, str);
	fclose(log);

	return 0;
}