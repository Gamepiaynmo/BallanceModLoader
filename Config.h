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
	friend class Config;
	friend class GuiModMenu;
	friend class GuiModCategory;
public:
	Property(Config* config, std::string category, std::string key);
	Property() {};

	virtual CKSTRING GetString() override;
	virtual bool GetBoolean() override;
	virtual int GetInteger() override;
	virtual float GetFloat() override;
	virtual CKKEYBOARD GetKey() override;

	virtual void SetString(CKSTRING value) override;
	virtual void SetBoolean(bool value) override;
	virtual void SetInteger(int value) override;
	virtual void SetFloat(float value) override;
	virtual void SetKey(CKKEYBOARD value) override;

	CKSTRING GetComment();
	virtual void SetComment(CKSTRING comment) override;

	virtual void SetDefaultString(CKSTRING value) override;
	virtual void SetDefaultBoolean(bool value) override;
	virtual void SetDefaultInteger(int value) override;
	virtual void SetDefaultFloat(float value) override;
	virtual void SetDefaultKey(CKKEYBOARD value) override;

	virtual PropertyType GetType() override { return m_type; }

	void CopyValue(Property* o);

private:
	union {
		bool m_bool;
		int m_int = 0;
		float m_float;
		CKKEYBOARD m_key;
	} m_value;
	std::string m_string;

	PropertyType m_type = INTEGER;
	std::string m_comment;

	std::string m_category, m_key;
	Config* m_config = nullptr;
};

class Config : public IConfig {
	friend class Property;
	friend class GuiModMenu;
	friend class GuiModCategory;
public:
	Config(IMod* mod);
	~Config();

	IMod* GetMod() { return m_mod; }

	virtual bool HasCategory(CKSTRING category) override;
	virtual bool HasKey(CKSTRING category, CKSTRING key) override;

	virtual IProperty* GetProperty(CKSTRING category, CKSTRING key) override;

	CKSTRING GetCategoryComment(CKSTRING category);
	virtual void SetCategoryComment(CKSTRING category, CKSTRING comment) override;

	void Load();
	void Save();

private:
	void trim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not_fn(std::isspace)));
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not_fn(std::isspace)).base(), s.end());
	}

	IMod* m_mod;
	std::string m_modname;

	struct Category {
		std::string name;
		std::string comment;
		Config* config;

		std::vector<Property*> props;

		Property* GetProperty(CKSTRING name);
	};

	Category& GetCategory(CKSTRING name);

	std::vector<Category> m_data;
};