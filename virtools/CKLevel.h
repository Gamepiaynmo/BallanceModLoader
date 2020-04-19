#pragma once

#include "CKDef.h"
#include "CKBeObject.h"

class BML_EXPORT CKLevel : public CKBeObject {
public:
	CKERROR AddObject(CKObject* obj);
	CKERROR RemoveObject(CKObject* obj);
	CKERROR RemoveObject(CK_ID obj);
	void BeginAddSequence(CKBOOL Begin);
	void BeginRemoveSequence(CKBOOL Begin);

	const XObjectPointerArray& ComputeObjectList(CK_CLASSID cid, CKBOOL derived = TRUE);

	CKERROR AddPlace(CKPlace* pl);
	CKERROR RemovePlace(CKPlace* pl);
	CKPlace* RemovePlace(int pos);
	CKPlace* GetPlace(int pos);
	int GetPlaceCount();

	CKERROR AddScene(CKScene* scn);
	CKERROR RemoveScene(CKScene* scn);
	CKScene* RemoveScene(int pos);
	CKScene* GetScene(int pos);
	int GetSceneCount();

	CKERROR SetNextActiveScene(CKScene*, CK_SCENEOBJECTACTIVITY_FLAGS Active = CK_SCENEOBJECTACTIVITY_SCENEDEFAULT,
		CK_SCENEOBJECTRESET_FLAGS Reset = CK_SCENEOBJECTRESET_RESET);

	CKERROR LaunchScene(CKScene*, CK_SCENEOBJECTACTIVITY_FLAGS Active = CK_SCENEOBJECTACTIVITY_SCENEDEFAULT,
		CK_SCENEOBJECTRESET_FLAGS Reset = CK_SCENEOBJECTRESET_RESET);
	CKScene* GetCurrentScene();

	void AddRenderContext(CKRenderContext*, CKBOOL Main = FALSE);
	void RemoveRenderContext(CKRenderContext*);
	int GetRenderContextCount();
	CKRenderContext* GetRenderContext(int count);

	CKScene* GetLevelScene();

	CKERROR Merge(CKLevel* mergedLevel, CKBOOL asScene);

protected:
	CKLevel() {};
	~CKLevel() {};
};