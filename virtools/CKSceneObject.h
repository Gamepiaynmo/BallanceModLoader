#pragma once

#include "CKDef.h"
#include "CKObject.h"

class BML_EXPORT CKSceneObject : public CKObject {
public:
	CKBOOL IsActiveInScene(CKScene* scene);
	CKBOOL IsActiveInCurrentScene();
	CKBOOL IsInScene(CKScene* scene);
	int GetSceneInCount();
	CKScene* GetSceneIn(int index);

protected:
	CKSceneObject() {};
	~CKSceneObject() {};
};