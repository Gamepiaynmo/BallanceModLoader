#include "Config.h"
#include "ModLoader.h"
#include <fstream>

Config::Config(IMod* mod) : m_mod(mod), m_modname(mod->GetID()) {
	Load();
}

void Config::Load() {
	std::ifstream fin("../ModLoader/Config/" + m_modname + ".cfg");
	if (fin.fail()) return;

	std::string token, comment, category;
	bool inCate = false;
	while (fin >> token) {
		if (token == "#") {
			std::getline(fin, comment);
			trim(comment);
		}
		else if (token == "{")
			inCate = true;
		else if (token == "}")
			inCate = false;
		else if (inCate) {
			std::string propname;
			fin >> propname;
			Property prop(nullptr, category, propname);
			switch (token[0]) {
				case 'S': {
					std::string value;
					std::getline(fin, value);
					trim(value);
					prop.SetDefaultString(value.c_str());
					break;
				}
				case 'B': {
					bool value;
					fin >> value;
					prop.SetDefaultBoolean(value);
					break;
				}
				case 'K': {
					int value;
					fin >> value;
					prop.SetDefaultKey(CKKEYBOARD(value));
					break;
				}
				case 'I': {
					int value;
					fin >> value;
					prop.SetDefaultInteger(value);
					break;
				}
				case 'F': {
					float value;
					fin >> value;
					prop.SetDefaultFloat(value);
					break;
				}
			}
			prop.SetComment(comment.c_str());
			m_data[category].second[propname] = prop;
		}
		else {
			category = token;
			m_data[token].first = comment;
			comment.clear();
		}
	}
}

void Config::Save() {
	std::ofstream fout("../ModLoader/Config/" + m_modname + ".cfg");
	if (fout.fail()) return;

	for (auto& category : m_data) {
		for (auto iter = category.second.second.begin(); iter != category.second.second.end(); ) {
			if (!iter->second.m_config)
				iter = category.second.second.erase(iter);
			else iter++;
		}
	}

	for (auto iter = m_data.begin(); iter != m_data.end(); ) {
		if (iter->second.second.empty())
			iter = m_data.erase(iter);
		else iter++;
	}

	fout << "# Configuration File for Mod: " << m_mod->GetName() << " - " << m_mod->GetVersion() << std::endl << std::endl;
	for (auto& category : m_data) {
		fout << "# " << category.second.first << std::endl;
		fout << category.first << " {" << std::endl << std::endl;

		for (auto& property : category.second.second) {
			fout << "\t# " << property.second.GetComment() << std::endl;
			fout << "\t";
			switch (property.second.GetType()) {
				case IProperty::STRING: fout << "S "; break;
				case IProperty::BOOLEAN: fout << "B "; break;
				case IProperty::FLOAT: fout << "F "; break;
				case IProperty::KEY: fout << "K "; break;
				case IProperty::INTEGER:
				default: fout << "I "; break;
			}

			fout << property.first << " ";
			switch (property.second.GetType()) {
				case IProperty::STRING: fout << property.second.GetString(); break;
				case IProperty::BOOLEAN: fout << property.second.GetBoolean(); break;
				case IProperty::FLOAT: fout << property.second.GetFloat(); break;
				case IProperty::KEY: fout << (int)property.second.GetKey(); break;
				case IProperty::INTEGER:
				default: fout << property.second.GetInteger(); break;
			}

			fout << std::endl << std::endl;
		}

		fout << "}" << std::endl << std::endl;
	}
}

bool Config::HasCategory(CKSTRING category) {
	return m_data.count(category) > 0;
}

bool Config::HasKey(CKSTRING category, CKSTRING key) {
	auto iter = m_data.find(category);
	if (iter != m_data.end())
		return iter->second.second.count(key) > 0;
	return false;
}

IProperty* Config::GetProperty(CKSTRING category, CKSTRING key) {
	auto& cate = m_data[category].second;
	bool exist = cate.find(key) != cate.end();
	Property& prop = m_data[category].second[key];
	prop.m_config = this;
	if (!exist) {
		prop.m_type = IProperty::NONE;
		prop.m_value.m_int = 0;
		prop.m_category = category;
		prop.m_key = key;
	}
	return &prop;
}

void Config::SetCategoryComment(CKSTRING category, CKSTRING comment) {
	m_data[category].first = comment;
}


Property::Property(Config* config, std::string category, std::string key) {
	m_type = NONE;
	m_value.m_int = 0;
	m_config = config;
	m_category = category;
	m_key = key;
}

CKSTRING Property::GetString() {
	return m_type == STRING ? m_string.c_str() : "";
}

bool Property::GetBoolean() {
	return m_type == BOOLEAN ? m_value.m_bool : false;
}

int Property::GetInteger() {
	return m_type == INTEGER ? m_value.m_int : 0;
}

float Property::GetFloat() {
	return m_type == FLOAT ? m_value.m_float : 0.0f;
}

CKKEYBOARD Property::GetKey() {
	return m_type == KEY ? m_value.m_key : (CKKEYBOARD)0;
}

void Property::SetString(CKSTRING value) {
	if (m_type != STRING || m_string != value) {
		m_string = value;
		m_type = STRING;
		ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetBoolean(bool value) {
	if (m_type != BOOLEAN || m_value.m_bool != value) {
		m_value.m_bool = value;
		m_type = BOOLEAN;
		ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetInteger(int value) {
	if (m_type != INTEGER || m_value.m_int != value) {
		m_value.m_int = value;
		m_type = INTEGER;
		ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetFloat(float value) {
	if (m_type != FLOAT || m_value.m_float != value) {
		m_value.m_float = value;
		m_type = FLOAT;
		ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetKey(CKKEYBOARD value) {
	if (m_type != KEY || m_value.m_key != value) {
		m_value.m_key = value;
		m_type = KEY;
		ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

CKSTRING Property::GetComment() {
	return m_comment.c_str();
}

void Property::SetComment(CKSTRING comment) {
	m_comment = comment;
}

void Property::SetDefaultString(CKSTRING value) {
	if (m_type != STRING) {
		m_type = STRING;
		m_string = value;
	}
}

void Property::SetDefaultBoolean(bool value) {
	if (m_type != BOOLEAN) {
		m_type = BOOLEAN;
		m_value.m_bool = value;
	}
}

void Property::SetDefaultInteger(int value) {
	if (m_type != INTEGER) {
		m_type = INTEGER;
		m_value.m_int = value;
	}
}

void Property::SetDefaultFloat(float value) {
	if (m_type != FLOAT) {
		m_type = FLOAT;
		m_value.m_float = value;
	}
}

void Property::SetDefaultKey(CKKEYBOARD value) {
	if (m_type != KEY) {
		m_type = KEY;
		m_value.m_key = value;
	}
}

void Property::CopyValue(Property& o) {
	m_type = o.GetType();
	switch (m_type) {
	case INTEGER: SetInteger(o.GetInteger()); break;
	case FLOAT: SetFloat(o.GetFloat()); break;
	case BOOLEAN: SetBoolean(o.GetBoolean()); break;
	case KEY: SetKey(o.GetKey()); break;
	case STRING: SetString(o.GetString()); break;
	}
}