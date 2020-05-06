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

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) { return std::vector<std::string>(); };
};

class CommandHelp : public ICommand {
public:
	virtual std::string GetName() override { return "help"; };
	virtual std::string GetAlias() override { return "?"; };
	virtual std::string GetDescription() override { return "Show Help Information about Existing Commands."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) { return std::vector<std::string>(); };
};

class CommandCheat : public ICommand {
public:
	virtual std::string GetName() override { return "cheat"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Enable or Disable Cheat Mode."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) {
		return args.size() == 2 ? std::vector<std::string>({ "true", "false" }) : std::vector<std::string>();
	};
};

class CommandClear : public ICommand {
	virtual std::string GetName() override { return "clear"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Clear the Console."; };
	virtual bool IsCheat() override { return false; };

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) { return std::vector<std::string>(); };
};

class CommandScore : public ICommand {
	virtual std::string GetName() override { return "score"; };
	virtual std::string GetAlias() override { return ""; };
	virtual std::string GetDescription() override { return "Manage Ingame Score."; };
	virtual bool IsCheat() override { return true; };

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) {
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

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) { return std::vector<std::string>(); };

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

	virtual void Execute(IBML* bml, std::vector<std::string> args) override;
	virtual std::vector<std::string> GetTabCompletion(IBML* bml, std::vector<std::string> args) { return std::vector<std::string>(); };

private:
	CKBehavior* m_deactBall = nullptr;
};