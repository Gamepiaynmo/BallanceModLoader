#include "Config.h"
#include "ModLoader.h"
#include <fstream>

Config::Config(IMod* mod) : m_mod(mod), m_modname(mod->GetID()) {
	Load();
}

Config::~Config() {
	for (Category& cate : m_data) {
		for (Property* prop : cate.props)
			delete prop;
	}
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
			Property* prop = new Property(nullptr, category, propname);
			switch (token[0]) {
				case 'S': {
					std::string value;
					std::getline(fin, value);
					trim(value);
					prop->SetDefaultString(value.c_str());
					break;
				}
				case 'B': {
					bool value;
					fin >> value;
					prop->SetDefaultBoolean(value);
					break;
				}
				case 'K': {
					int value;
					fin >> value;
					prop->SetDefaultKey(CKKEYBOARD(value));
					break;
				}
				case 'I': {
					int value;
					fin >> value;
					prop->SetDefaultInteger(value);
					break;
				}
				case 'F': {
					float value;
					fin >> value;
					prop->SetDefaultFloat(value);
					break;
				}
			}
			prop->SetComment(comment.c_str());
			GetCategory(category.c_str()).props.push_back(prop);
		}
		else {
			category = token;
			GetCategory(category.c_str()).comment = comment;
			comment.clear();
		}
	}
}

void Config::Save() {
	std::ofstream fout("../ModLoader/Config/" + m_modname + ".cfg");
	if (fout.fail()) return;

	for (auto& category : m_data) {
		for (auto iter = category.props.begin(); iter != category.props.end(); ) {
			if (!(*iter)->m_config) {
				delete (*iter);
				iter = category.props.erase(iter);
			} else iter++;
		}
	}

	for (auto iter = m_data.begin(); iter != m_data.end(); ) {
		if (iter->props.empty())
			iter = m_data.erase(iter);
		else iter++;
	}

	fout << "# Configuration File for Mod: " << m_mod->GetName() << " - " << m_mod->GetVersion() << std::endl << std::endl;
	for (auto& category : m_data) {
		fout << "# " << category.comment << std::endl;
		fout << category.name << " {" << std::endl << std::endl;

		for (auto property : category.props) {
			fout << "\t# " << property->GetComment() << std::endl;
			fout << "\t";
			switch (property->GetType()) {
				case IProperty::STRING: fout << "S "; break;
				case IProperty::BOOLEAN: fout << "B "; break;
				case IProperty::FLOAT: fout << "F "; break;
				case IProperty::KEY: fout << "K "; break;
				case IProperty::INTEGER:
				default: fout << "I "; break;
			}

			fout << property->m_key << " ";
			switch (property->GetType()) {
				case IProperty::STRING: fout << property->GetString(); break;
				case IProperty::BOOLEAN: fout << property->GetBoolean(); break;
				case IProperty::FLOAT: fout << property->GetFloat(); break;
				case IProperty::KEY: fout << (int)property->GetKey(); break;
				case IProperty::INTEGER:
				default: fout << property->GetInteger(); break;
			}

			fout << std::endl << std::endl;
		}

		fout << "}" << std::endl << std::endl;
	}
}

bool Config::HasCategory(CKSTRING category) {
	for (Category& cate : m_data)
		if (cate.name == category)
			return true;
	return false;
}

bool Config::HasKey(CKSTRING category, CKSTRING key) {
	if (HasCategory(category))
		for (Property* prop : GetCategory(category).props)
			if (prop->m_key == key)
				return true;
	return false;
}

IProperty* Config::GetProperty(CKSTRING category, CKSTRING key) {
	bool exist = HasKey(category, key);
	Property* prop = GetCategory(category).GetProperty(key);
	prop->m_config = this;
	if (!exist) {
		prop->m_type = IProperty::NONE;
		prop->m_value.m_int = 0;
		prop->m_category = category;
		prop->m_key = key;
	}
	return prop;
}

Config::Category& Config::GetCategory(CKSTRING name) {
	for (Category& cate : m_data)
		if (cate.name == name)
			return cate;

	Config::Category cate;
	cate.name = name;
	cate.config = this;
	m_data.push_back(cate);
	return m_data.back();
}

Property* Config::Category::GetProperty(CKSTRING name) {
	for (Property* prop : props)
		if (prop->m_key == name)
			return prop;

	Property* prop = new Property(config, this->name, name);
	props.push_back(prop);
	return props.back();
}

CKSTRING Config::GetCategoryComment(CKSTRING category) {
	return GetCategory(category).comment.c_str();
}

void Config::SetCategoryComment(CKSTRING category, CKSTRING comment) {
	GetCategory(category).comment = comment;
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
		if (m_config)
			ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetBoolean(bool value) {
	if (m_type != BOOLEAN || m_value.m_bool != value) {
		m_value.m_bool = value;
		m_type = BOOLEAN;
		if (m_config)
			ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetInteger(int value) {
	if (m_type != INTEGER || m_value.m_int != value) {
		m_value.m_int = value;
		m_type = INTEGER;
		if (m_config)
			ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetFloat(float value) {
	if (m_type != FLOAT || m_value.m_float != value) {
		m_value.m_float = value;
		m_type = FLOAT;
		if (m_config)
			ModLoader::m_instance->OnModifyConfig(m_config->m_mod, m_category.c_str(), m_key.c_str(), this);
	}
}

void Property::SetKey(CKKEYBOARD value) {
	if (m_type != KEY || m_value.m_key != value) {
		m_value.m_key = value;
		m_type = KEY;
		if (m_config)
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

void Property::CopyValue(Property* o) {
	m_type = o->GetType();
	switch (m_type) {
	case INTEGER: SetInteger(o->GetInteger()); break;
	case FLOAT: SetFloat(o->GetFloat()); break;
	case BOOLEAN: SetBoolean(o->GetBoolean()); break;
	case KEY: SetKey(o->GetKey()); break;
	case STRING: SetString(o->GetString()); break;
	}
}