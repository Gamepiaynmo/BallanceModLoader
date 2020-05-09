#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"

#undef GetObject

#define CKM_BASE							0
#define CKM_BEHAVIORPRESAVE					CKM_BASE + 1		
#define CKM_BEHAVIORDELETE					CKM_BASE + 2	
#define CKM_BEHAVIORATTACH					CKM_BASE + 3	
#define CKM_BEHAVIORDETACH					CKM_BASE + 4		
#define CKM_BEHAVIORPAUSE					CKM_BASE + 5		
#define CKM_BEHAVIORRESUME					CKM_BASE + 6	
#define CKM_BEHAVIORCREATE					CKM_BASE + 7	
#define CKM_BEHAVIORRESET					CKM_BASE + 9	
#define CKM_BEHAVIORPOSTSAVE				CKM_BASE + 10	
#define CKM_BEHAVIORLOAD					CKM_BASE + 11	
#define CKM_BEHAVIOREDITED					CKM_BASE + 12	
#define CKM_BEHAVIORSETTINGSEDITED			CKM_BASE + 13	
#define CKM_BEHAVIORREADSTATE				CKM_BASE + 14	
#define CKM_BEHAVIORNEWSCENE				CKM_BASE + 15	
#define CKM_BEHAVIORACTIVATESCRIPT			CKM_BASE + 16	
#define CKM_BEHAVIORDEACTIVATESCRIPT		CKM_BASE + 17	
#define CKM_BEHAVIORRESETINBREAKBPOINT		CKM_BASE + 18	
#define CKM_MAX_BEHAVIOR_CALLBACKS			CKM_BASE + 19	

class BML_EXPORT CKBehaviorManager : public CKBaseManager {
public:
	CKERROR Execute(float delta);
	CKERROR AddObject(CKBeObject* b);
	CKERROR RemoveObject(CKBeObject* b);
	int GetObjectsCount();
	CKERROR RemoveAllObjects();
	CKBeObject* GetObject(int pos);
	CKERROR AddObjectNextFrame(CKBeObject* b);
	CKERROR RemoveObjectNextFrame(CKBeObject* b);
	int GetBehaviorMaxIteration();
	void SetBehaviorMaxIteration(int n);

protected:
	CKBehaviorManager() {};
	~CKBehaviorManager() {};
};