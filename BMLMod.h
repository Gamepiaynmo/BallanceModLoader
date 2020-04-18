#pragma once

#include "IMod.h"
#include "Version.h"

class BMLMod : public IMod {
public:
	BMLMod(IBML* bml) : IMod(bml) {}

	virtual CKSTRING GetID() override { return "BML"; }
	virtual CKSTRING GetVersion() override { return BML_VERSION; }
	virtual CKSTRING GetName() override { return "Ballance Mod Loader"; }
	virtual CKSTRING GetAuthor() override { return "Gamepiaynmo & Ùø³¹"; }
	virtual CKSTRING GetDescription() override { return "Implementation of functions provided by Ballance Mod Loader."; }

	virtual void OnLoad() override;

	virtual void OnLoadScript(CKSTRING filename, CKBehavior* script) override;
	virtual void OnProcess() override;

private:
	void OnEditScript_Base_EventHandler(CKBehavior* script);
	void OnEidtScript_Menu_MainMenu(CKBehavior* script);
};