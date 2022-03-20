#include <windows.h>
#include <errno.h>
#include <stdio.h>
#include "err.h"

void err(int eval, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	verr(eval, fmt, args);

	va_end(args);
}

void errx(int eval, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	verrx(eval, fmt, args);

	va_end(args);
}

void warn(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	vwarn(fmt, args);

	va_end(args);
}

void warnx(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	vwarnx(fmt, args);

	va_end(args);
}

void verr(int eval, const char *fmt, va_list args)
{
	vwarn(fmt, args);
	exit(eval);
}

void verrx(int eval, const char *fmt, va_list args)
{
	vwarnx(fmt, args);
	exit(eval);
}

void vwarn(const char *fmt, va_list args)
{
	int error = errno;
	const char * errorMessage = strerror(errno);
	HLOCAL lpFilenameHandle = LocalAlloc(LHND, MAX_PATH * sizeof (CHAR));
	LPSTR lpFilename = (lpFilenameHandle != NULL && lpFilenameHandle != INVALID_HANDLE_VALUE) ? LocalLock(lpFilenameHandle) : NULL;
	DWORD ret = (lpFilename != NULL && lpFilename != INVALID_HANDLE_VALUE) ? GetModuleFileNameA(NULL, lpFilename, MAX_PATH) : ERROR_NOT_ENOUGH_MEMORY;

	if(fmt != NULL)
	{
		fprintf(stderr, "%s: ", lpFilename);
		vfprintf(stderr, fmt, args);
		fprintf(stderr, ": %s\n", errorMessage);
	}
	else
	{
		fprintf(stderr, "%s: %s\n", lpFilename, errorMessage);
	}

	if(lpFilename != NULL && lpFilename != INVALID_HANDLE_VALUE)
	{
		DWORD unlockRet = LocalUnlock(lpFilenameHandle);
		lpFilename = NULL;
	}
	if(lpFilenameHandle != NULL && lpFilenameHandle != INVALID_HANDLE_VALUE)
	{
		HANDLE freeRet = LocalFree(lpFilenameHandle);
		lpFilenameHandle = NULL;
	}

	errno = error;
}

void vwarnx(const char *fmt, va_list args)
{
	int error = errno;
	HLOCAL lpFilenameHandle = LocalAlloc(LHND, MAX_PATH * sizeof (CHAR));
	LPSTR lpFilename = (lpFilenameHandle != NULL && lpFilenameHandle != INVALID_HANDLE_VALUE) ? LocalLock(lpFilenameHandle) : NULL;
	DWORD ret = (lpFilename != NULL && lpFilename != INVALID_HANDLE_VALUE) ? GetModuleFileNameA(NULL, lpFilename, MAX_PATH) : ERROR_NOT_ENOUGH_MEMORY;

	fprintf(stderr, "%s: ", lpFilename);
	if(fmt != NULL)
	{
		vfprintf(stderr, fmt, args);
	}
	fprintf(stderr, "\n");

	if(lpFilename != NULL && lpFilename != INVALID_HANDLE_VALUE)
	{
		DWORD unlockRet = LocalUnlock(lpFilenameHandle);
		lpFilename = NULL;
	}
	if(lpFilenameHandle != NULL && lpFilenameHandle != INVALID_HANDLE_VALUE)
	{
		HANDLE freeRet = LocalFree(lpFilenameHandle);
		lpFilenameHandle = NULL;
	}

	errno = error;
}
