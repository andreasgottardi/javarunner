#ifndef MYLOG_H
#define MYLOG_H

#define LOG_ERROR (0x1)
#define LOG_INFO (0x2)
#define LOG_DEBUG (0x3)

int WriteToLog(char *str, DWORD mode);

#endif /* MYLOG_H */