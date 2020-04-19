#pragma once

#include "virtools/CKAll.h"

namespace ExecuteBB {
	enum FontType {
		NOFONT,
		GAMEFONT_01, // Normal
		GAMEFONT_02, // Larger
		GAMEFONT_03, // Small
		GAMEFONT_03A, // Small, Gray
		GAMEFONT_04, // Large
		GAMEFONT_CREDITS_SMALL,
		GAMEFONT_CREDITS_BIG
	};
	void InitFont(FontType type, int fontIndex);

	void Init(CKContext* context);

#define TEXT_SCREEN				1
#define TEXT_BACKGROUND			2
#define TEXT_CLIP				4
#define TEXT_RESIZE_VERT		8
#define TEXT_RESIZE_HORI		16
#define TEXT_WORDWRAP			32
#define TEXT_JUSTIFIED			64
#define TEXT_COMPILED			128
#define TEXT_MULTIPLE			256
#define TEXT_SHOWCARET			512
#define TEXT_3D					1024
#define TEXT_SCREENCLIP			2048
	CKBehavior* Create2DText(CK2dEntity* target = nullptr, FontType font = NOFONT, CKSTRING text = "", int align = 0,
		VxRect margin = { 2, 2, 2, 2 }, Vx2DVector offset = { 0, 0 }, Vx2DVector pindent = { 0, 0 }, CKMaterial* bgmat = nullptr,
		int caretsize = 10, CKMaterial* caretmat = nullptr, int flags = TEXT_SCREEN);
	void Call2DText(CK2dEntity* target = nullptr, FontType font = NOFONT, CKSTRING text = "", int align = 0,
		VxRect margin = { 2, 2, 2, 2 }, Vx2DVector offset = { 0, 0 }, Vx2DVector pindent = { 0, 0 }, CKMaterial* bgmat = nullptr,
		int caretsize = 10, CKMaterial* caretmat = nullptr, int flags = TEXT_SCREEN);
}