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
	if (bml->IsIngame() && args.size() > 2) {
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
	if (bml->IsIngame() && args.size() > 1) {
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

void CommandKill::Execute(IBML* bml, std::vector<std::string> args) {
	if (bml->IsPlaying() && !m_deactBall) {
		CKContext* ctx = bml->GetCKContext();
		CKBehavior* ingame = static_cast<CKBehavior*>(ctx->GetObjectByNameAndClass("Gameplay_Ingame", CKCID_BEHAVIOR));
		CKBehavior* ballMgr = ScriptHelper::FindFirstBB(ingame, "BallManager", false);
		m_deactBall = ScriptHelper::FindFirstBB(ballMgr, "Deactivate Ball", false);
	}

	if (m_deactBall) {
		m_deactBall->ActivateInput(0);
		m_deactBall->Activate();
		bml->SendIngameMessage("Killed Ball");
	}
}

void CommandSetSpawn::Execute(IBML* bml, std::vector<std::string> args) {
	if (bml->IsIngame() && !m_curLevel) {
		m_curLevel = static_cast<CKDataArray*>(bml->GetCKContext()->GetObjectByNameAndClass("CurrentLevel", CKCID_DATAARRAY));
	}

	if (m_curLevel) {
		CK3dEntity* camRef = static_cast<CK3dEntity*>(bml->GetCKContext()->GetObjectByNameAndClass("Cam_OrientRef", CKCID_3DENTITY));
		VxMatrix matrix = camRef->GetWorldMatrix();
		for (int i = 0; i < 4; i++) {
			std::swap(matrix[0][i], matrix[2][i]);
			matrix[0][i] = -matrix[0][i];
		}
		m_curLevel->SetElementValue(0, 3, &matrix);
		bml->SendIngameMessage(("Set Spawn Point to ("
			+ std::to_string(matrix[3][0]) + ", "
			+ std::to_string(matrix[3][1]) + ", "
			+ std::to_string(matrix[3][2]) + ")").c_str());
	}
}

void CommandSector::Execute(IBML* bml, std::vector<std::string> args) {
	if (bml->IsPlaying() && args.size() > 1) {
		CKContext* ctx = bml->GetCKContext();
		if (!m_curLevel) {
			m_curLevel = static_cast<CKDataArray*>(ctx->GetObjectByNameAndClass("CurrentLevel", CKCID_DATAARRAY));
			m_checkpoints = static_cast<CKDataArray*>(ctx->GetObjectByNameAndClass("Checkpoints", CKCID_DATAARRAY));
			m_resetpoints = static_cast<CKDataArray*>(ctx->GetObjectByNameAndClass("ResetPoints", CKCID_DATAARRAY));
			m_ingameParam = static_cast<CKDataArray*>(ctx->GetObjectByNameAndClass("IngameParameter", CKCID_DATAARRAY));
			CKBehavior* events = static_cast<CKBehavior*>(ctx->GetObjectByNameAndClass("Gameplay_Events", CKCID_BEHAVIOR));
			CKBehavior* id = ScriptHelper::FindNextBB(events, events->GetInput(0));
			m_curSector = id->GetOutputParameter(0)->GetDestination(0);
		}

		if (m_curLevel) {
			int curSector = ScriptHelper::GetParamValue<int>(m_curSector);
			int sector = ParseInteger(args[1], 1, m_checkpoints->GetRowCount() + 1);
			if (curSector != sector) {
				VxMatrix matrix;
				m_resetpoints->GetElementValue(sector - 1, 0, &matrix);
				m_curLevel->SetElementValue(0, 3, &matrix);

				m_ingameParam->SetElementValue(0, 1, &sector);
				m_ingameParam->SetElementValue(0, 2, &curSector);
				ScriptHelper::SetParamValue(m_curSector, sector);

				bml->SendIngameMessage(("Changed to Sector " + std::to_string(sector)).c_str());

				CKBehavior* sectorMgr = static_cast<CKBehavior*>(ctx->GetObjectByNameAndClass("Gameplay_SectorManager", CKCID_BEHAVIOR));
				ctx->GetCurrentScene()->Activate(sectorMgr, true);

				bml->AddTimerLoop(1u, [this, bml, sector, sectorMgr, ctx]() {
					if (sectorMgr->IsActive())
						return true;

					bml->AddTimer(2u, [this, bml, sector, ctx]() {
						CKBOOL active = false;
						m_curLevel->SetElementValue(0, 4, &active);

						CK_ID flameId;
						m_checkpoints->GetElementValue(sector % 2, 1, &flameId);
						CK3dEntity* flame = static_cast<CK3dEntity*>(ctx->GetObject(flameId));
						ctx->GetCurrentScene()->Activate(flame->GetScript(0), true);

						m_checkpoints->GetElementValue(sector - 1, 1, &flameId);
						flame = static_cast<CK3dEntity*>(ctx->GetObject(flameId));
						ctx->GetCurrentScene()->Activate(flame->GetScript(0), true);

						if (sector > m_checkpoints->GetRowCount()) {
							CKMessageManager* mm = bml->GetMessageManager();
							CKMessageType msg = mm->AddMessageType("last Checkpoint reached");
							mm->SendMessageSingle(msg, static_cast<CKGroup*>(ctx->GetObjectByNameAndClass("All_Sound", CKCID_GROUP)));

							ResetBall(bml, ctx);
						}
						else {
							bml->AddTimer(2u, [this, bml, sector, ctx, flame]() {
								VxMatrix matrix;
								m_checkpoints->GetElementValue(sector - 1, 0, &matrix);
								flame->SetWorldMatrix(matrix);
								CKBOOL active = true;
								m_curLevel->SetElementValue(0, 4, &active);
								ctx->GetCurrentScene()->Activate(flame->GetScript(0), true);
								bml->Show(flame, CKSHOW, true);

								ResetBall(bml, ctx);
								});
						}
					});
					return false;
					});
			}
		}
	}
}

void CommandSector::ResetBall(IBML* bml, CKContext* ctx) {
	CKMessageManager* mm = bml->GetMessageManager();
	CKMessageType ballDeact = mm->AddMessageType("BallNav deactivate");

	mm->SendMessageSingle(ballDeact, static_cast<CKGroup*>(ctx->GetObjectByNameAndClass("All_Gameplay", CKCID_GROUP)));
	mm->SendMessageSingle(ballDeact, static_cast<CKGroup*>(ctx->GetObjectByNameAndClass("All_Sound", CKCID_GROUP)));

	bml->AddTimer(2u, [this, bml, ctx]() {
		CK3dEntity* curBall = static_cast<CK3dEntity*>(m_curLevel->GetElementObject(0, 1));
		if (curBall) {
			ExecuteBB::Unphysicalize(curBall);

			ModLoader::m_instance->m_bmlmod->m_dynamicPos->ActivateInput(1);
			ModLoader::m_instance->m_bmlmod->m_dynamicPos->Activate();

			bml->AddTimer(1u, [this, bml, curBall, ctx]() {
				VxMatrix matrix;
				m_curLevel->GetElementValue(0, 3, &matrix);
				curBall->SetWorldMatrix(matrix);

				CK3dEntity* camMF = static_cast<CK3dEntity*>(ctx->GetObjectByNameAndClass("Cam_MF", CKCID_3DENTITY));
				bml->RestoreIC(camMF, true);
				camMF->SetWorldMatrix(matrix);

				bml->AddTimer(1u, [this]() {
					ModLoader::m_instance->m_bmlmod->m_dynamicPos->ActivateInput(0);
					ModLoader::m_instance->m_bmlmod->m_dynamicPos->Activate();

					ModLoader::m_instance->m_bmlmod->m_phyNewBall->ActivateInput(0);
					ModLoader::m_instance->m_bmlmod->m_phyNewBall->Activate();
					ModLoader::m_instance->m_bmlmod->m_phyNewBall->GetParent()->Activate();
					});
				});
		}
		});
}

void CommandWin::Execute(IBML* bml, std::vector<std::string> args) {
	if (bml->IsPlaying()) {
		CKMessageManager* mm = bml->GetMessageManager();
		CKMessageType levelWin = mm->AddMessageType("Level_Finish");

		CKContext* ctx = bml->GetCKContext();
		mm->SendMessageSingle(levelWin, static_cast<CKGroup*>(ctx->GetObjectByNameAndClass("All_Gameplay", CKCID_GROUP)));
		bml->SendIngameMessage("Level Finished");
	}
}