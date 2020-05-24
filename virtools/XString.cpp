#include "CKDef.h"
#include "XString.h"

XString::XString(const char* iString, const int iLength) {
	Constructor(iString, iLength);
}

NAKED void XString::Constructor(const char* iString, const int iLength) {
	JUMP(0x2429E630);
}

XString::XString(const XString& iSrc) {
	Constructor(iSrc);
}

NAKED void XString::Constructor(const XString& iSrc) {
	JUMP(0x2429E7E0);
}

XString::XString(const XBaseString& iSrc) {
	Constructor(iSrc);
}

NAKED void XString::Constructor(const XBaseString& iSrc) {
	JUMP(0x2429E870);
}

XString::~XString() {
	Deconstructor();
}

NAKED void XString::Deconstructor() {
	JUMP(0x2429E7A0);
}

NAKED XString& XString::operator = (const XString& iSrc) {
	JUMP(0x2429E990);
}

NAKED XString& XString::operator = (const char* iSrc) {
	JUMP(0x2429E950);
}

NAKED XString& XString::operator = (const XBaseString& iSrc) {
	JUMP(0x2429E990);
}

NAKED XString& XString::Create(const char* iString, const int iLength) {
	JUMP(0x2429E900);
}

NAKED XString& XString::ToUpper() {
	JUMP(0x2429EA00);
}

NAKED XString& XString::ToLower() {
	JUMP(0x2429EA40);
}

NAKED int XString::ICompare(const XBaseString& iStr) const {
	JUMP(0x2429EA80);
}

NAKED XString& XString::Trim() {
	JUMP(0x2429EB10);
}

NAKED XString& XString::Strip() {
	JUMP(0x2429EBA0);
}

NAKED XWORD XString::Find(char iCar, XWORD iStart) const {
	JUMP(0x2429EC70);
}

NAKED XWORD XString::Find(const XBaseString& iStr, XWORD iStart) const {
	JUMP(0x2429ECC0);
}

NAKED XWORD XString::IFind(const XBaseString& iStr, XWORD iStart) const {
	UNDEFINED;
}

NAKED XWORD XString::RFind(char iCar, XWORD iStart) const {
	JUMP(0x2429ED10);
}

NAKED XString XString::Substring(XWORD iStart, XWORD iLength) const {
	JUMP(0x2429EFD0);
}

NAKED XString& XString::Crop(XWORD iStart, XWORD iLength) {
	JUMP(0x2429F020);
}

NAKED XString& XString::Cut(XWORD iStart, XWORD iLength) {
	JUMP(0x2429F070);
}

NAKED int XString::Replace(char iSrc, char iDest) {
	JUMP(0x2429F0C0);
}

NAKED int XString::Replace(const XBaseString& iSrc, const XBaseString& iDest) {
	JUMP(0x2429F100);
}

NAKED XString& XString::operator << (const char* iString) {
	JUMP(0x2429E950);
}

NAKED XString& XString::operator << (const XBaseString& iString) {
	JUMP(0x2429EDE0);
}

NAKED XString& XString::operator << (const char iValue) {
	JUMP(0x2429EE40);
}

NAKED XString& XString::operator << (const int iValue) {
	JUMP(0x2429EE80);
}

NAKED XString& XString::operator << (const unsigned int iValue) {
	JUMP(0x2429EEF0);
}

NAKED XString& XString::operator << (const float iValue) {
	JUMP(0x2429EF60);
}

NAKED XString& XString::operator << (const void* iValue) {
	UNDEFINED;
}