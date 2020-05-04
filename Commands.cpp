#include "Commands.h"
#include "ModLoader.h"
#include "Version.h"
#include "BMLMod.h"
#include "ScriptHelper.h"

void CommandBML::Execute(IBML* bml, std::vector<std::string> args) {
	ModLoader* loader = ModLoader::m_instance;
	bml->SendIngameMessage("Ballance Mod Loader " BML_VERSION);
	bml->SendIngameMessage((std::to_string(loader->m_mods.size()) + " Mods Installed:").c_str());
	for (IMod* mod : loader->m_mods) {
		std::string str = std::string("  ") + mod->GetID() + ": " + mod->GetName() + " " + mod->GetVersion() + " by " + mod->GetAuthor();
		bml->SendIngameMessage(str.c_str());
	}
}

void CommandHelp::Execute(IBML* bml, std::vector<std::string> args) {
	ModLoader* loader = ModLoader::m_instance;
	bml->SendIngameMessage((std::to_string(loader->m_cmds.size()) + " Existing Commands:").c_str());
	for (ICommand* cmd : loader->m_cmds) {
		std::string str = std::string("  /") + cmd->GetName();
		if (!cmd->GetAlias().empty())
			str += "(" + cmd->GetAlias() + ")";
		if (cmd->IsCheat()) str += "[Cheat]";
		str += ": " + cmd->GetDescription();
		bml->SendIngameMessage(str.c_str());
	}
}

void CommandCheat::Execute(IBML* bml, std::vector<std::string> args) {
	ModLoader* loader = ModLoader::m_instance;
	if (args.size() == 1) {
		loader->EnableCheat(!loader->IsCheatEnabled());
	}
	else {
		loader->EnableCheat(ParseBoolean(args[1]));
	}
	bml->SendIngameMessage(loader->IsCheatEnabled() ? "Cheat Mode On" : "Cheat Mode Off");
}

void CommandClear::Execute(IBML* bml, std::vector<std::string> args) {
	BMLMod* bmlmod = ModLoader::m_instance->m_bmlmod;
	bmlmod->m_msgCnt = 0;
	for (int i = 0; i < MSG_MAXSIZE; i++) {
		bmlmod->m_msg[i].m_bg->SetVisible(false);
		bmlmod->m_msg[i].m_text->SetVisible(false);
		bmlmod->m_msg[i].m_text->SetText("");
		bmlmod->m_msg[i].timer = 0;
	}
}

void CommandScore::Execute(IBML* bml, std::vector<std::string> args) {
	if (args.size() > 2) {
		int num = ParseInteger(args[2], 0);
		if (!m_energy) {
			m_energy = static_cast<CKDataArray*>(bml->GetCKContext()->GetObjectByNameAndClass("Energy", CKCID_DATAARRAY));
		}

		if (m_energy) {
			int score;
			m_energy->GetElementValue(0, 0, &score);
			if (args[1] == "add")
				score += num;
			else if (args[1] == "sub")
				score = (std::max)(0, score - num);
			else if (args[1] == "set")
				score = num;
			m_energy->SetElementValue(0, 0, &score);
			bml->SendIngameMessage(("Ingame Score Changed to " + std::to_string(score)).c_str());
		}
	}
}

void CommandSpeed::Execute(IBML* bml, std::vector<std::string> args) {
	if (args.size() > 1) {
		float time = ParseFloat(args[1], 0, 1000);
		if (!m_curLevel) {
			CKContext* ctx = bml->GetCKContext();
			m_curLevel = static_cast<CKDataArray*>(ctx->GetObjectByNameAndClass("CurrentLevel", CKCID_DATAARRAY));
			m_phyBall = static_cast<CKDataArray*>(ctx->GetObjectByNameAndClass("Physicalize_GameBall", CKCID_DATAARRAY));
			CKBehavior* ingame = static_cast<CKBehavior*>(ctx->GetObjectByNameAndClass("Gameplay_Ingame", CKCID_BEHAVIOR));
			m_force = ScriptHelper::FindFirstBB(ingame, "Ball Navigation", false)->GetInputParameter(0)->GetRealSource();

			for (int i = 0; i < m_phyBall->GetRowCount(); i++) {
				char ballName[100];
				m_phyBall->GetElementStringValue(i, 0, ballName);
				float force;
				m_phyBall->GetElementValue(i, 7, &force);
				m_forces[ballName] = force;
			}
		}

		if (m_curLevel) {
			CKObject* curBall = m_curLevel->GetElementObject(0, 1);
			if (curBall) {
				auto iter = m_forces.find(curBall->GetName());
				if (iter != m_forces.end()) {
					float force = iter->second;
					force *= time;
					ScriptHelper::SetParamValue(m_force, force);
				}
			}

			for (int i = 0; i < m_phyBall->GetRowCount(); i++) {
				char ballName[100];
				m_phyBall->GetElementStringValue(i, 0, ballName);
				auto iter = m_forces.find(ballName);
				if (iter != m_forces.end()) {
					float force = iter->second;
					force *= time;
					m_phyBall->SetElementValue(i, 7, &force);
				}
			}

			bml->SendIngameMessage(("Current Ball Speed Changed to " + std::to_string(time) + " times").c_str());
		}
	}
}