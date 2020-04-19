#pragma once

#include "Export.h"
#include "Logger.h"
#include "virtools/CKAll.h"
#include <functional>

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
	virtual void OnExitGame() = 0;
	virtual void OnLoadLevel() = 0;
	virtual void OnStartLevel() = 0;
	virtual void OnResetLevel() = 0;
	virtual void OnPauseLevel() = 0;
	virtual void OnUnpauseLevel() = 0;
	virtual void OnExitLevel() = 0;
	virtual void OnNextLevel() = 0;
	virtual void OnDead() = 0;
	virtual void OnEndLevel() = 0;

	virtual void AddTimer(CKDWORD delay, std::function<void()> callback) = 0;
	virtual void AddTimer(CKDWORD delay, std::function<bool()> callback) = 0;
	virtual void AddTimer(float delay, std::function<void()> callback) = 0;
	virtual void AddTimer(float delay, std::function<bool()> callback) = 0;
};
