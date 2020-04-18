#pragma once

#include "ILogger.h"
#include <cstdarg>

class BML_EXPORT Logger : public ILogger {
	friend class ModLoader;
public:
	Logger(const char* modname);

	virtual void Info(const char* fmt, ...) override;
	virtual void Warn(const char* fmt, ...) override;
	virtual void Error(const char* fmt, ...) override;

private:
	void Log(const char* level, const char* fmt, va_list args);

	const char* m_modname;
};

