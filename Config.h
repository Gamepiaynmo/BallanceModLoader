#pragma once

#include "IConfig.h"
#include "IMod.h"
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <functional>

class Config;

class Property : public IProperty {
public:
	Property(Config* config, std::string category, std::string key);
	Property() {};

	virtual CKSTRING GetString() override;
	virtual bool GetBoolean() override;
	virtual int GetInteger() override;
	virtual float GetFloat() override;

	virtual void SetString(CKSTRING value) override;
	virtual void SetBoolean(bool value) override;
	virtual void SetInteger(int value) override;
	virtual void SetFloat(float value) override;

	CKSTRING GetComment();
	virtual void SetComment(CKSTRING comment) override;

	virtual void SetDefaultString(CKSTRING value) override;
	virtual void SetDefaultBoolean(bool value) override;
	virtual void SetDefaultInteger(int value) override;
	virtual void SetDefaultFloat(float value) override;

	virtual PropertyType GetType() override { return m_type; }

private:
	union {
		bool m_bool;
		int m_int;
		float m_float;
	} m_value;
	std::string m_string;

	PropertyType m_type;
	std::string m_comment;

	std::string m_category, m_key;
	Config* m_config;
};

class Config : public IConfig {
	friend class Property;
public:
	Config(IMod* mod);

	virtual bool HasCategory(CKSTRING category) override;
	virtual bool HasKey(CKSTRING category, CKSTRING key) override;

	virtual IProperty* GetProperty(CKSTRING category, CKSTRING key) override;
	virtual void SetCategoryComment(CKSTRING category, CKSTRING comment) override;

	void Load();
	void Save();

private:
	void trim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	}

	IMod* m_mod;
	std::string m_modname;

	typedef std::map<std::string, std::pair<std::string, std::map<std::string, Property>>> ConfigData;
	ConfigData m_data;
};