#pragma once

#include "Export.h"
#include "Logger.h"
#include "virtools/CKAll.h"

class BML_EXPORT IBML {
public:
	virtual CKContext* GetCKContext() = 0;
	virtual CKRenderContext* GetRenderContext() = 0;

	virtual void ExitGame() = 0;

	virtual CKAttributeManager* GetAttributeManager() = 0;
	virtual CKBehaviorManager* GetBehaviorManager() = 0;
	virtual CKCollisionManager* GetCollisionManager() = 0;
	virtual CKInputManager* GetInputManager() = 0;
	virtual CKMessageManager* GetMessageManager() = 0;
	virtual CKParameterManager* GetParameterManager() = 0;
	virtual CKRenderManager* GetRenderManager() = 0;
	virtual CKSoundManager* GetSoundManager() = 0;
	virtual CKTimeManager* GetTimeManager() = 0;

	virtual void OnStartMenu() = 0;
};
