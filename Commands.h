#pragma once

#include "ICommand.h"
#include "virtools/CKAll.h"
#include <map>

class CommandBML : public ICommand {
public:
	virtual std::string GetName() override { return "bml"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Show Information about Ballance Mod Loader."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };
};

class CommandHelp : public ICommand {
public:
	virtual std::string GetName() override { return "help"; };
	virtual std::string GetAlias() override { return "?"; };
	virtual std::string GetDescription() override { return "Show Help Information about Existing Commands."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };
};

class CommandCheat : public ICommand {
public:
	virtual std::string GetName() override { return "cheat"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Enable or Disable Cheat Mode."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override {
		return args.size() == 2 ? std::vector<std::string>({ "true", "false" }) : std::vector<std::string>();
	};
};

class CommandClear : public ICommand {
	virtual std::string GetName() override { return "clear"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Clear the Console."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };
};

class CommandScore : public ICommand {
	virtual std::string GetName() override { return "score"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Manage Ingame Score."; };
	virtual bool IsCheat() override { return true; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override {
		return args.size() == 2 ? std::vector<std::string>({ "add", "sub", "set" }) : std::vector<std::string>();
	};

private:
	CKDataArray* m_energy = nullptr;
};

class CommandSpeed : public ICommand {
	virtual std::string GetName() override { return "speed"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Change Realtime Ball Speed."; };
	virtual bool IsCheat() override { return true; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };

private:
	CKDataArray* m_curLevel = nullptr, * m_phyBall = nullptr;
	CKParameter* m_force = nullptr;
	std::map<std::string, float> m_forces;
};

class CommandKill : public ICommand {
	virtual std::string GetName() override { return "kill"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Suicide."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };

private:
	CKBehavior* m_deactBall = nullptr;
};

class CommandSetSpawn : public ICommand {
	virtual std::string GetName() override { return "spawn"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Set Ball Spawn Point to Current Position."; };
	virtual bool IsCheat() override { return true; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };

private:
	CKDataArray* m_curLevel;
};

class CommandSector : public ICommand {
	virtual std::string GetName() override { return "sector"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Start playing specified sector."; };
	virtual bool IsCheat() override { return true; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };
	void ResetBall(IBML* bml, CKContext* ctx);

private:
	CKDataArray* m_curLevel, * m_checkpoints, * m_resetpoints, * m_ingameParam;
	CKParameter* m_curSector;
};

class CommandWatermark : public ICommand {
	virtual std::string GetName() override { return "watermark"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Enable or Disable the BML watermark."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override {
		return args.size() == 2 ? std::vector<std::string>({ "true", "false" }) : std::vector<std::string>();
	};
};

class CommandWin : public ICommand {
	virtual std::string GetName() override { return "win"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Finish this Level."; };
	virtual bool IsCheat() override { return true; };

	virtual void Execute(IBML* bml, const std::vector<std::string>& args) override;
	virtual const std::vector<std::string> GetTabCompletion(IBML* bml, const std::vector<std::string>& args) override { return std::vector<std::string>(); };
};
