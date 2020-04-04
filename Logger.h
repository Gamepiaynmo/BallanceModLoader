#pragma once

#include "Export.h"
#include <cstdarg>

class BML_EXPORT Logger {
	friend class ModLoader;
public:
	void Info(const char* fmt, ...);
	void Warn(const char* fmt, ...);
	void Error(const char* fmt, ...);

private:
	Logger(const char* modname);

	void Log(const char* level, const char* fmt, va_list args);

	const char* m_modname;
};

