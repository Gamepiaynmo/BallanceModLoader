#include "CKSpriteText.h"

NAKED void CKSpriteText::SetText(CKSTRING text) {
	JUMPV(0x1e0);
}

NAKED CKSTRING CKSpriteText::GetText() {
	JUMPV(0x1e4);
}

NAKED void CKSpriteText::SetTextColor(CKDWORD col) {
	JUMPV(0x1e8);
}

NAKED CKDWORD CKSpriteText::GetTextColor() {
	JUMPV(0x1ec);
}

NAKED void CKSpriteText::SetBackgroundColor(CKDWORD col) {
	JUMPV(0x1f0);
}

NAKED CKDWORD CKSpriteText::GetBackgroundTextColor() {
	JUMPV(0x1f4);
}

NAKED void CKSpriteText::SetFont(CKSTRING FontName, int FontSize, int Weight, CKBOOL italic, CKBOOL underline) {
	JUMPV(0x1f8);
}

NAKED void CKSpriteText::SetAlign(CKSPRITETEXT_ALIGNMENT align) {
	JUMPV(0x1fc);
}

NAKED CKSPRITETEXT_ALIGNMENT CKSpriteText::GetAlign() {
	JUMPV(0x200);
}

NAKED void CKSpriteText::SetTextU(CKUSTRING text) {
	JUMPV(0x204);
}

NAKED CKUSTRING CKSpriteText::GetTextU() {
	JUMPV(0x208);
}
