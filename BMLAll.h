#pragma once

#include "Export.h"

#define BML_MAJOR_VER 0
#define BML_MINOR_VER 0
#include "BuildVer.h"
#define TOSTRING2(arg) #arg
#define TOSTRING(arg) TOSTRING2(arg)
#define BML_VERSION TOSTRING(BML_MAJOR_VER) "." TOSTRING(BML_MINOR_VER) "." TOSTRING(BML_BUILD_VER) "-alpha"

#include "IBML.h"
#include "Logger.h"

#ifdef BML_EXPORTS
#include "ModLoader.h"
#endif