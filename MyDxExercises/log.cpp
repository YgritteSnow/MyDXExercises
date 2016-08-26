
#include <tchar.h>
#include <cstdio>
#include <stdarg.h>
#include <Windows.h>

#include "log.h"

void LogOutputA(char* st, ...)
{
	if( !st )
		return;

	char buf[1024];

	va_list arglist;
	va_start(arglist, st);
	vsprintf_s(buf, st, arglist);

	OutputDebugStringA(buf);
};