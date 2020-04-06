#include "Logger.h"
#include "ModLoader.h"
#include <Windows.h>
#include <cstdio>

Logger::Logger(const char* modname) : m_modname(modname) {

}

void Logger::Info(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	Log("INFO", fmt, args);
	va_end(args);
}

void Logger::Warn(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	Log("WARN", fmt, args);
	va_end(args);
}

void Logger::Error(const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);
	Log("ERROR", fmt, args);
	va_end(args);
}

void Logger::Log(const char* level, const char* fmt, va_list args) {
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	FILE* out_files[] = {
#if _DEBUG
		stdout,
#endif
		ModLoader::m_instance->GetLogFile()
	};

	for (FILE* file : out_files) {
		fprintf(file, "[%02d/%02d/%d %02d:%02d:%02d.%03d] ", sys.wMonth, sys.wDay,
			sys.wYear, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
		fprintf(file, "[%s/%s]: ", m_modname, level);
		vfprintf(file, fmt, args);
		fputc('\n', file);
		fflush(file);
	}
}