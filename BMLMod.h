#pragma once

#include "IMod.h"
#include "Version.h"
#include "Gui.h"
#include <queue>
#include "ICommand.h"
#include <map>

#define MSG_MAXSIZE 35

class Config;
class Property;

class GuiList : public BGui::Gui {
public:
	GuiList();
	void Init(int size, int maxsize);

	virtual BGui::Button* CreateButton(int index) = 0;
	virtual std::string GetButtonText(int index) = 0;
	virtual BGui::Gui* CreateSubGui(int index) = 0;
	virtual BGui::Gui* GetParentGui() = 0;

	virtual void SetPage(int page);
	void PreviousPage() { if (m_curpage > 0) SetPage(m_curpage - 1); }
	void NextPage() { if (m_curpage < m_maxpage - 1) SetPage(m_curpage + 1); }
	virtual void Exit();
	virtual void SetVisible(bool visible) override;

protected:
	std::vector<BGui::Button*> m_buttons;
	int m_curpage, m_maxpage, m_size, m_maxsize;
	std::vector<BGui::Gui*> m_guiList;
	BGui::Button* m_left, * m_right;
};

class GuiModOption : public GuiList {
public:
	GuiModOption();

	virtual BGui::Button* CreateButton(int index) override;
	virtual std::string GetButtonText(int index) override;
	virtual BGui::Gui* CreateSubGui(int index) override;
	virtual BGui::Gui* GetParentGui() override;
	virtual void Exit() override;
};

class GuiModMenu : public GuiList {
public:
	GuiModMenu(IMod* mod);

	virtual BGui::Button* CreateButton(int index) override;
	virtual std::string GetButtonText(int index) override;
	virtual BGui::Gui* CreateSubGui(int index) override;
	virtual BGui::Gui* GetParentGui() override;

private:
	Config* m_config;
	std::vector<std::string> m_categories;
};

class GuiModCategory : public BGui::Gui {
public:
	GuiModCategory(GuiModMenu* parent, Config* config, std::string category);

	virtual void SetVisible(bool visible) override;
	void SetPage(int page);
	void PreviousPage() { if (m_curpage > 0) SetPage(m_curpage - 1); }
	void NextPage() { if (m_curpage < m_maxpage - 1) SetPage(m_curpage + 1); }

	void SaveAndExit();
	void Exit();

private:
	std::map<std::string, Property> m_data;
	std::vector<std::vector<BGui::Element*>> m_elements;
	int m_curpage, m_maxpage, m_size;
	BGui::Button* m_left, * m_right;

	GuiModMenu* m_parent;
	Config* m_config;
	std::string m_category;
	BGui::Button* m_exit;
};

class CommandTravel : public ICommand {
	virtual std::string GetName() override { return "travel"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Switch to First-Person Camera."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) { return std::vector<std::string>(); };
public:
	CommandTravel(class BMLMod* mod) : m_mod(mod) {};

private:
	class BMLMod* m_mod;
};

class BMLMod : public IMod {
	friend class CommandClear;
	friend class CommandSector;
	friend class GuiModMenu;
public:
	BMLMod(IBML* bml) : IMod(bml) {}

	virtual CKSTRING GetID() override { return "BML"; }
	virtual CKSTRING GetVersion() override { return BML_VERSION; }
	virtual CKSTRING GetName() override { return "Ballance Mod Loader"; }
	virtual CKSTRING GetAuthor() override { return "Gamepiaynmo & YingChe"; }
	virtual CKSTRING GetDescription() override { return "Implementation of functions provided by Ballance Mod Loader."; }

	virtual void OnLoad() override;
	virtual void OnLoadObject(CKSTRING filename, CKSTRING masterName, CK_CLASSID filterClass,
		BOOL addtoscene, BOOL reuseMeshes, BOOL reuseMaterials, BOOL dynamic,
		XObjectArray* objArray, CKObject* masterObj) override;
	virtual void OnLoadScript(CKSTRING filename, CKBehavior* script) override;
	virtual void OnProcess() override;
	virtual void OnCheatEnabled(bool enable) override;
	virtual void OnModifyConfig(CKSTRING category, CKSTRING key, IProperty* prop) override;

	virtual void OnPostStartMenu() override;
	virtual void OnPostResetLevel() override;
	virtual void OnStartLevel() override;
	virtual void OnPostExitLevel() override;
	virtual void OnPauseLevel() override;
	virtual void OnUnpauseLevel() override;
	virtual void OnCounterActive() override;
	virtual void OnCounterInactive() override;

	void AddIngameMessage(CKSTRING msg);
	void ShowCheatBanner(bool show);
	void ShowModOptions();
	void ShowGui(BGui::Gui* gui);
	void ShowGuiList(GuiList* gui);
	void CloseCurrentGui();

	void EnterTravelCam();
	void ExitTravelCam();
	bool IsInTravelCam();

private:
	void OnEditScript_Base_DefaultLevel(CKBehavior* script);
	void OnEditScript_Base_EventHandler(CKBehavior* script);
	void OnEditScript_Menu_MenuInit(CKBehavior* script);
	void OnEditScript_Menu_OptionsMenu(CKBehavior* script);
	void OnEditScript_Gameplay_Ingame(CKBehavior* script);
	void OnEditScript_Gameplay_Energy(CKBehavior* script);
	void OnEditScript_Gameplay_Events(CKBehavior* script);

	void OnCmdEdit(CKDWORD key);

	BGui::Gui* m_cmdBar = nullptr;
	bool m_cmdTyping = false;
	BGui::Input* m_cmdInput;
	std::vector<std::string> m_cmdHistory;
	unsigned int m_historyPos;

	BGui::Gui* m_msgLog = nullptr;
	int m_msgCnt = 0;
	struct {
		BGui::Panel* m_bg;
		BGui::Label* m_text;
		int timer;
	} m_msg[MSG_MAXSIZE];

	BGui::Gui* m_ingameBanner = nullptr;
	BGui::Label* m_cheat[3], * m_fps, * m_srScore, * m_srTitle;
	int m_fpscnt = 0, m_fpstimer = 0;
	float m_srtimer = 0.0f;
	bool m_sractive = false;

	BGui::Gui* m_currentGui = nullptr;
	GuiModOption* m_modOption = nullptr;

	IProperty* m_skipAnim;
	bool m_skipSpeed = false;
	IProperty* m_fullscreenKey;
	IProperty* m_unlockRes;

	IProperty* m_ballCheat[2];
	IProperty* m_suicide;
	CKParameterLocal* m_ballForce[2] = { 0 };
	int m_suicideCd = 0;

	IProperty* m_camRot[2], * m_camY[2], * m_camZ[2], * m_cam45, * m_camReset, * m_camOn;
	CK3dEntity* m_camPos, * m_camOrient, * m_camOrientRef, * m_camTarget;

	IProperty* m_overclock;
	CKBehaviorLink* m_oclinks[3];
	CKBehaviorIO* m_oclinkio[3][2];

	IProperty* m_changeBall[3];
	CKBehavior* m_setNewBall;
	CKParameter* m_curTrafo;
	CKDataArray* m_curLevel, * m_ingameParam;
	int m_changeBallCd = 0;
	IProperty* m_speedupBall;
	bool m_speedup;

	IProperty* m_resetBall;
	CKParameter* m_curSector;
	CKBehavior* m_phyNewBall, * m_dynamicPos;

	IProperty* m_addLife;
	int m_addLifeCd = 0;

	IProperty* m_addBall[4];
	int m_curSel = -1;
	CK3dEntity* m_curObj = nullptr;
	CK3dEntity* m_pBalls[4];
	std::vector<std::pair<int, CK3dEntity*>> m_tempBalls;
	IProperty* m_moveKeys[6];

	IProperty* m_fpsKeys[6];
	CKCamera* m_travelCam;
};