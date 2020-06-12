#pragma once

#include "virtools/CKAll.h"
#include <utility>

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
	int GetFont(FontType type);
	FontType GetFontType(int font);

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

#define ALIGN_CENTER		0
#define ALIGN_LEFT			1
#define ALIGN_RIGHT			2
#define ALIGN_TOP			4
#define ALIGN_TOPLEFT		5
#define ALIGN_TOPRIGHT		6
#define ALIGN_BOTTOM		8
#define ALIGN_BOTTOMLEFT	9
#define ALIGN_BOTTOMRIGHT	10

	BML_EXPORT CKBehavior* Create2DText(CK2dEntity* target = nullptr, FontType font = NOFONT, CKSTRING text = "", int align = ALIGN_CENTER,
		VxRect margin = { 2, 2, 2, 2 }, Vx2DVector offset = { 0, 0 }, Vx2DVector pindent = { 0, 0 }, CKMaterial* bgmat = nullptr,
		float caretsize = 0.1f, CKMaterial* caretmat = nullptr, int flags = TEXT_SCREEN);

	BML_EXPORT CKBehavior* CreatePhysicalizeConvex(CK3dEntity* target = nullptr, CKBOOL fixed = false, float friction = 0.7f, float elasticity = 0.4f,
		float mass = 1.0f, CKSTRING collGroup = "", CKBOOL startFrozen = false, CKBOOL enableColl = true, CKBOOL calcMassCenter = false,
		float linearDamp = 0.1f, float rotDamp = 0.1f, CKSTRING collSurface = "", VxVector massCenter = VxVector(), CKMesh* mesh = nullptr);

	BML_EXPORT CKBehavior* CreatePhysicalizeBall(CK3dEntity* target = nullptr, CKBOOL fixed = false, float friction = 0.7f, float elasticity = 0.4f,
		float mass = 1.0f, CKSTRING collGroup = "", CKBOOL startFrozen = false, CKBOOL enableColl = true, CKBOOL calcMassCenter = false,
		float linearDamp = 0.1f, float rotDamp = 0.1f, CKSTRING collSurface = "", VxVector massCenter = VxVector(),
		VxVector ballCenter = VxVector(), float ballRadius = 2.0f);

	BML_EXPORT CKBehavior* CreatePhysicalizeConcave(CK3dEntity* target = nullptr, CKBOOL fixed = false, float friction = 0.7f, float elasticity = 0.4f,
		float mass = 1.0f, CKSTRING collGroup = "", CKBOOL startFrozen = false, CKBOOL enableColl = true, CKBOOL calcMassCenter = false,
		float linearDamp = 0.1f, float rotDamp = 0.1f, CKSTRING collSurface = "", VxVector massCenter = VxVector(), CKMesh* mesh = nullptr);

	BML_EXPORT void PhysicalizeConvex(CK3dEntity* target = nullptr, CKBOOL fixed = false, float friction = 0.7f, float elasticity = 0.4f,
		float mass = 1.0f, CKSTRING collGroup = "", CKBOOL startFrozen = false, CKBOOL enableColl = true, CKBOOL calcMassCenter = false,
		float linearDamp = 0.1f, float rotDamp = 0.1f, CKSTRING collSurface = "", VxVector massCenter = VxVector(), CKMesh* mesh = nullptr);

	BML_EXPORT void PhysicalizeBall(CK3dEntity* target = nullptr, CKBOOL fixed = false, float friction = 0.7f, float elasticity = 0.4f,
		float mass = 1.0f, CKSTRING collGroup = "", CKBOOL startFrozen = false, CKBOOL enableColl = true, CKBOOL calcMassCenter = false,
		float linearDamp = 0.1f, float rotDamp = 0.1f, CKSTRING collSurface = "", VxVector massCenter = VxVector(),
		VxVector ballCenter = VxVector(), float ballRadius = 2.0f);

	BML_EXPORT void PhysicalizeConcave(CK3dEntity* target = nullptr, CKBOOL fixed = false, float friction = 0.7f, float elasticity = 0.4f,
		float mass = 1.0f, CKSTRING collGroup = "", CKBOOL startFrozen = false, CKBOOL enableColl = true, CKBOOL calcMassCenter = false,
		float linearDamp = 0.1f, float rotDamp = 0.1f, CKSTRING collSurface = "", VxVector massCenter = VxVector(), CKMesh* mesh = nullptr);

	BML_EXPORT void Unphysicalize(CK3dEntity* target);

	BML_EXPORT CKBehavior* CreateObjectLoad(CKSTRING file = "", CKSTRING mastername = "", CK_CLASSID filter = CKCID_3DOBJECT,
		CKBOOL addToScene = true, CKBOOL reuseMesh = true, CKBOOL reuseMtl = true, CKBOOL dynamic = true);

	BML_EXPORT ::std::pair<XObjectArray*, CKObject*> ObjectLoad(CKSTRING file = "", bool rename = true, CKSTRING mastername = "",
		CK_CLASSID filter = CKCID_3DOBJECT, CKBOOL addToScene = true, CKBOOL reuseMesh = true, CKBOOL reuseMtl = true, CKBOOL dynamic = true);

	BML_EXPORT CKBehavior* CreatePhysicsImpulse(CK3dEntity* target = nullptr, VxVector position = VxVector(), CK3dEntity* posRef = nullptr,
		VxVector direction = VxVector(), CK3dEntity* dirRef = nullptr, float impulse = 0.0f);

	BML_EXPORT void PhysicsImpulse(CK3dEntity* target = nullptr, VxVector position = VxVector(), CK3dEntity* posRef = nullptr,
		VxVector direction = VxVector(), CK3dEntity* dirRef = nullptr, float impulse = 0.0f);
}