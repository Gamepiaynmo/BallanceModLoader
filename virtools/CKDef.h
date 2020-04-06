#pragma once

#include <Windows.h>

#include "../Export.h"
#include "CKdefines2.h"
#include "CKEnums.h"
#include "CKTypes.h"
#include "CKError.h"

#define VX_EXPORT
#define NAKED __declspec(naked)
#define UNDEFINED throw "Unimplemented function called."

#include "XUtil.h"
#include "XString.h"

#include "VxMathDefines.h"
#include "VxQuaternion.h"
#include "Vx2dVector.h"
#include "VxMatrix.h"
#include "VxVector.h"

#define JUMP(ADDR) \
	static CKDWORD addr = ADDR; \
	__asm jmp addr
#define JUMPV(OFFSET) \
	__asm mov eax, [ecx] \
	__asm mov eax, [eax + OFFSET] \
	__asm jmp eax

#define GET_MEMPTR(OFFSET, TYPE) \
	reinterpret_cast<TYPE*>(reinterpret_cast<BYTE*>(this) + OFFSET)
#define GET_MEM(OFFSET, TYPE) (*GET_MEMPTR(OFFSET, TYPE))
#define RETURN_MEMPTR(OFFSET, TYPE) return GET_MEMPTR(OFFSET, TYPE)
#define RETURN_MEM(OFFSET, TYPE) return GET_MEM(OFFSET, TYPE)
#define SET_MEM(OFFSET, TYPE, VALUE) (GET_MEM(OFFSET, TYPE) = VALUE)