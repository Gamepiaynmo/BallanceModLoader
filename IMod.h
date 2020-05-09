#pragma once

#include "virtools/CKAll.h"
#include "IBML.h"
#include "IConfig.h"

class BML_EXPORT IMod : public IMessageReciver {
public:
	IMod(IBML* bml) : m_bml(bml) {};
	virtual ~IMod();

	virtual CKSTRING GetID() = 0;
	virtual CKSTRING GetVersion() = 0;
	virtual CKSTRING GetName() = 0;
	virtual CKSTRING GetAuthor() = 0;
	virtual CKSTRING GetDescription() = 0;

	virtual void OnLoad() {};
	virtual void OnUnload() {};
	virtual void OnModifyConfig(CKSTRING category, CKSTRING key, IProperty* prop) {};

	virtual void OnLoadObject(CKSTRING filename, CKSTRING masterName, CK_CLASSID filterClass,
		BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials, BOOL dynamic,
		XObjectArray* objArray, CKObject* masterObj) {};
	virtual void OnLoadScript(CKSTRING filename, CKBehavior* script) {};

	virtual void OnProcess() {};
	virtual void OnRender(CK_RENDER_FLAGS flags) {};

	virtual void OnCheatEnabled(bool enable) {};

protected:
	virtual ILogger* GetLogger() final;
	virtual IConfig* GetConfig() final;

	IBML* m_bml;

private:
	ILogger* m_logger = nullptr;
	IConfig* m_config = nullptr;
};