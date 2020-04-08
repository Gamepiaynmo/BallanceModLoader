#pragma once

#include "CKDef.h"
#include "CKBeObject.h"

typedef enum VXFOG_MODE {
	VXFOG_NONE = 0UL,
	VXFOG_EXP = 1UL,
	VXFOG_EXP2 = 2UL,
	VXFOG_LINEAR = 3UL
} VXFOG_MODE;

typedef XHashTable<CKSceneObjectDesc, CK_ID> CKSODHash;
typedef CKSODHash::Iterator CKSODHashIt;

class CKSceneObjectIterator {
public:
	CKSceneObjectIterator(CKSODHashIt it, CKSODHash& iHash) : m_Iterator(it), m_Hash(iHash) {}
	CK_ID GetObjectID() { return m_Iterator.GetKey(); }
	CKSceneObjectDesc* GetObjectDesc() { return &(*m_Iterator); }
	void Rewind() { m_Iterator = m_Hash.Begin(); }
	void RemoveAt() { m_Iterator = m_Hash.Remove(m_Iterator); }
	int End() { return m_Iterator == m_Hash.End(); }
	CKSceneObjectIterator& operator++(int) {
		++m_Iterator;
		return *this;
	}

	CKSODHashIt m_Iterator;
	CKSODHash& m_Hash;
};

class BML_EXPORT CKScene : public CKBeObject {
public:
	void AddObjectToScene(CKSceneObject* o, CKBOOL dependencies = TRUE);
	void RemoveObjectFromScene(CKSceneObject* o, CKBOOL dependencies = TRUE);
	CKBOOL IsObjectHere(CKObject* o);
	void BeginAddSequence(CKBOOL Begin);
	void BeginRemoveSequence(CKBOOL Begin);
	int GetObjectCount();
	const XObjectPointerArray& ComputeObjectList(CK_CLASSID cid, CKBOOL derived = TRUE);
	CKSceneObjectIterator GetObjectIterator();
	void Activate(CKSceneObject* o, CKBOOL Reset);
	void DeActivate(CKSceneObject* o);
	void SetObjectFlags(CKSceneObject* o, CK_SCENEOBJECT_FLAGS flags);
	CK_SCENEOBJECT_FLAGS GetObjectFlags(CKSceneObject* o);
	CK_SCENEOBJECT_FLAGS ModifyObjectFlags(CKSceneObject* o, CKDWORD Add, CKDWORD Remove);
	CKBOOL SetObjectInitialValue(CKSceneObject* o, CKStateChunk* chunk);
	CKStateChunk* GetObjectInitialValue(CKSceneObject* o);
	CKBOOL IsObjectActive(CKSceneObject* o);
	void ApplyEnvironmentSettings(XObjectPointerArray* renderlist = NULL);
	void UseEnvironmentSettings(BOOL use = TRUE);
	CKBOOL EnvironmentSettings();
	void SetAmbientLight(CKDWORD Color);
	CKDWORD GetAmbientLight();
	void SetFogMode(VXFOG_MODE Mode);
	void SetFogStart(float Start);
	void SetFogEnd(float End);
	void SetFogDensity(float Density);
	void SetFogColor(CKDWORD Color);
	VXFOG_MODE GetFogMode();
	float GetFogStart();
	float GetFogEnd();
	float GetFogDensity();
	CKDWORD GetFogColor();
	void SetBackgroundColor(CKDWORD Color);
	CKDWORD GetBackgroundColor();
	void SetBackgroundTexture(CKTexture* texture);
	CKTexture* GetBackgroundTexture();
	void SetStartingCamera(CKCamera* camera);
	CKCamera* GetStartingCamera();
	CKLevel* GetLevel();
	CKERROR Merge(CKScene* mergedScene, CKLevel* fromLevel = NULL);

protected:
	CKScene() {};
	~CKScene() {};
};