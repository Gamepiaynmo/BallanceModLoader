#pragma once

#include "CKDef.h"
#include "CKObject.h"

struct CKPluginEntry;

typedef CKERROR(*CK_PARAMETERCREATEDEFAULTFUNCTION)(CKParameter*);
typedef void (*CK_PARAMETERDELETEFUNCTION)(CKParameter*);
typedef void (*CK_PARAMETERCHECKFUNCTION)(CKParameter*);
typedef void (*CK_PARAMETERREMAPFUNCTION)(CKParameter*, CKDependenciesContext&);
typedef void (*CK_PARAMETERCOPYFUNCTION)(CKParameter*, CKParameter*);
typedef void (*CK_PARAMETERSAVELOADFUNCTION)(CKParameter* param, CKStateChunk** chunk, CKBOOL load);
typedef int (*CK_PARAMETERSTRINGFUNCTION)(CKParameter* param, CKSTRING ValueString, CKBOOL ReadFromString);
typedef WIN_HANDLE(*CK_PARAMETERUICREATORFUNCTION)(CKParameter* param, WIN_HANDLE ParentWindow, CKRECT* rect);

struct CKParameterTypeDesc {
	CKParameterType Index;
	CKGUID Guid;
	CKGUID DerivedFrom;
	XString	TypeName;
	int Valid;
	int DefaultSize;
	CK_PARAMETERCREATEDEFAULTFUNCTION CreateDefaultFunction;
	CK_PARAMETERDELETEFUNCTION DeleteFunction;
	CK_PARAMETERSAVELOADFUNCTION SaveLoadFunction;
	CK_PARAMETERCHECKFUNCTION CheckFunction;
	CK_PARAMETERCOPYFUNCTION CopyFunction;
	CK_PARAMETERSTRINGFUNCTION StringFunction;
	CK_PARAMETERUICREATORFUNCTION UICreatorFunction;

	CKPluginEntry* CreatorDll;
	CKDWORD dwParam;
	CKDWORD dwFlags;
	CKDWORD Cid;
	XBitArray DerivationMask;
	CKGUID Saver_Manager;

	CKParameterTypeDesc() {
		Cid = dwFlags = dwParam = DefaultSize = Valid = 0;
		CreatorDll = NULL;
		UICreatorFunction = 0;
		StringFunction = 0;
		SaveLoadFunction = 0;
		CheckFunction = 0;
		DeleteFunction = 0;
		CopyFunction = 0;
		CreateDefaultFunction = 0;
		DerivedFrom = CKGUID(0, 0);
		Guid = CKGUID(0, 0);
		TypeName = "";
		Saver_Manager = CKGUID(0, 0);
	}
};

class BML_EXPORT CKParameter : public CKObject {
public:
	void CheckClass(CKParameterTypeDesc* iType);

	CKObject* GetOwner();
	void SetOwner(CKObject* o);

	CKGUID GetGUID();
	CK_CLASSID GetParameterClassID();
	CKParameterType GetType();
	CKBOOL IsCompatibleWith(CKParameter* param);
	void SetType(CKParameterType type);
	void SetGUID(CKGUID guid);

	CKERROR CopyValue(CKParameter* param, CKBOOL UpdateParam = TRUE);
	int GetDataSize();
	void* GetReadDataPtr(CKBOOL update = TRUE);
	int GetStringValue(CKSTRING Value, CKBOOL update = TRUE);
	CKERROR GetValue(void* buf, CKBOOL update = TRUE);
	CKObject* GetValueObject(CKBOOL update = TRUE);
	void* GetWriteDataPtr();
	CKERROR SetStringValue(CKSTRING Value);
	CKERROR SetValue(const void* buf, int size = 0);

protected:
	CKParameter() {};
	~CKParameter() {};
};

class BML_EXPORT CKParameterLocal : public CKParameter {
protected:
	CKParameterLocal() {};
	~CKParameterLocal() {};
};

class BML_EXPORT CKParameterOut : public CKParameter {
public:
	void DataChanged();
	CKERROR AddDestination(CKParameter* param, CKBOOL CheckType);
	void RemoveDestination(CKParameter* param);
	int GetDestinationCount();
	CKParameter* GetDestination(int pos);
	void RemoveAllDestinations();

protected:
	CKParameterOut() {};
	~CKParameterOut() {};
};