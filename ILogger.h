#pragma once

#include "Export.h"

class BML_EXPORT ILogger {
public:
	virtual void Info(const char* fmt, ...) = 0;
	virtual void Warn(const char* fmt, ...) = 0;
	virtual void Error(const char* fmt, ...) = 0;
};