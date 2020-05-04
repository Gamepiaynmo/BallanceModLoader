#pragma once

#include "virtools/CKAll.h"
#include <cfloat>

class BML_EXPORT IProperty {
public:
	virtual CKSTRING GetString() = 0;
	virtual bool GetBoolean() = 0;
	virtual int GetInteger() = 0;
	virtual float GetFloat() = 0;
	virtual CKKEYBOARD GetKey() = 0;

	virtual void SetString(CKSTRING value) = 0;
	virtual void SetBoolean(bool value) = 0;
	virtual void SetInteger(int value) = 0;
	virtual void SetFloat(float value) = 0;
	virtual void SetKey(CKKEYBOARD value) = 0;

	virtual void SetComment(CKSTRING comment) = 0;
	virtual void SetDefaultString(CKSTRING value) = 0;
	virtual void SetDefaultBoolean(bool value) = 0;
	virtual void SetDefaultInteger(int value) = 0;
	virtual void SetDefaultFloat(float value) = 0;
	virtual void SetDefaultKey(CKKEYBOARD value) = 0;

	enum PropertyType {
		STRING,
		BOOLEAN,
		INTEGER,
		KEY,
		FLOAT,
		NONE
	};
	virtual PropertyType GetType() = 0;
};

class BML_EXPORT IConfig {
public:
	virtual bool HasCategory(CKSTRING category) = 0;
	virtual bool HasKey(CKSTRING category, CKSTRING key) = 0;

	virtual IProperty* GetProperty(CKSTRING category, CKSTRING key) = 0;
	virtual void SetCategoryComment(CKSTRING category, CKSTRING comment) = 0;
};