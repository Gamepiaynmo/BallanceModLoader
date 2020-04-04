#pragma once

#include "Export.h"
#include "Logger.h"

class BML_EXPORT IBML {
public:
	virtual Logger* CreateLogger(const char* modname) = 0;
};
