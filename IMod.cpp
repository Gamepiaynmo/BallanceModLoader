#include "IMod.h"
#include "Logger.h"
#include "Config.h"
#include "ModLoader.h"

ILogger* IMod::GetLogger() {
	if (m_logger == nullptr)
		m_logger = new Logger(GetID());
	return m_logger;
}

IConfig* IMod::GetConfig() {
	if (m_config == nullptr) {
		Config* config = new Config(this);
		m_config = config;
		ModLoader::m_instance->AddConfig(config);
	}
	return m_config;
}

IMod::~IMod() {
	if (m_logger) delete m_logger;
	if (m_config) delete m_config;
}