#pragma once

#include "CKDef.h"
#include "CKSprite.h"

class BML_EXPORT CKSpriteText : public CKSprite {
public:
	void SetText(CKSTRING text);
	CKSTRING GetText();
	void SetTextColor(CKDWORD col);
	CKDWORD GetTextColor();
	void SetBackgroundColor(CKDWORD col);
	CKDWORD GetBackgroundTextColor();
	void SetFont(CKSTRING FontName, int FontSize = 12, int Weight = 400, CKBOOL italic = FALSE, CKBOOL underline = FALSE);
	void SetAlign(CKSPRITETEXT_ALIGNMENT align);
	CKSPRITETEXT_ALIGNMENT GetAlign();
	void SetTextU(CKUSTRING text);
	CKUSTRING GetTextU();

protected:
	CKSpriteText() {};
	~CKSpriteText() {};
};