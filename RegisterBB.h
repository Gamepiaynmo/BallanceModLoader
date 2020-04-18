#pragma once

#include "virtools/CKAll.h"
#include "Version.h"
#include <vector>
#include <string>

void RegisterBBs(XObjectDeclarationArray* reg);

#define BML_ONSTARTMENU_GUID CKGUID(0x4a404bf4,0x1dd97e55)
#define BML_MODSMENU_GUID CKGUID(0x6ac12ce,0x52dc6e9d)

#define TT_PUSHBUTTON2 CKGUID(0x14d325d1, 0x6748654e)