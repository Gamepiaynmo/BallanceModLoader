#pragma once

#include "CKDef.h"

#define CKPLUGIN_BITMAP			"Bitmap Readers"	 
#define CKPLUGIN_SOUND			"Sound Readers"		
#define CKPLUGIN_MODEL			"Model Readers"		
#define CKPLUGIN_MANAGER		"Managers"			
#define CKPLUGIN_BEHAVIOR		"BuildingBlocks"	
#define CKPLUGIN_RENDERENGINE	"Render Engines"	
#define CKPLUGIN_MOVIE			"Movie Readers"		
#define CKPLUGIN_EXTENSIONS		"Extensions"		

class CKDataReader;
class CKBitmapReader;
class CKSoundReader;
class CKModelReader;
class CKMovieReader;

struct CKPluginDll
{
	XString			m_DllFileName;		// DLL Path
	INSTANCE_HANDLE	m_DllInstance;		// Instance of the Loaded Dll (as HINSTANCE on windows)
	int				m_PluginInfoCount;	// Number of plugins declared by this DLL


	CKPluginDll() {
		m_DllFileName = "";
		m_DllInstance = 0;
	}

	//Summary: Returns a pointer to a function inside the plugin.
	//Arguments:
	//	FunctionName: Name of the function which should be returned			
	//Return Value:
	//	A Pointer to the function or NULL if the function was not found in the DLL.
	void* GetFunctionPtr(CKSTRING FunctionName);
};

// Summary: Reader plugin creation function prototype
// 
// See Also:Creating New Plugins
typedef CKDataReader* (*CKReaderGetReaderFunction)(int);


// Summary: Data Reader (Movie,Bitmap,Sound,Models...) specific options
// 
//struct CKPluginEntryReadersData
//{
//	CKGUID						m_SettingsParameterGuid;	// Parameter type for options
//	int							m_OptionCount;				// Number of options for the reader
//	CK_DATAREADER_FLAGS			m_ReaderFlags;				// Reader Save/Load options
//	CKReaderGetReaderFunction	m_GetReaderFct;				// A pointer to the function that will create a reader.
//
//
//	CKPluginEntryReadersData() {
//		m_GetReaderFct = NULL;
//		m_OptionCount = 0;
//		m_ReaderFlags = (CK_DATAREADER_FLAGS)0;
//		m_SettingsParameterGuid = CKGUID(0, 0);
//	}
//};
struct CKPluginEntryReadersData;

// Summary: List of behavior GUID declared by a plugin
// 
//See Also:CKPluginEntry
struct CKPluginEntryBehaviorsData
{
	XArray<CKGUID>			m_BehaviorsGUID;
};

struct  CKPluginEntry
{
	int				m_PluginDllIndex;	// Index of the owner Dll in the list of Dlls
	int				m_PositionInDll;	// Position of the PluginInfo inside the DLL (when thery are several plugins inside a same DLL)
	CKPluginInfo	m_PluginInfo;		// Base Info on the plugin (Type, Name,Description)

//--- According to the type of plugin 

	CKPluginEntryReadersData* m_ReadersInfo;		// Reader plugins specific info (optionnal settings + load/save capabilities) 
	CKPluginEntryBehaviorsData* m_BehaviorsInfo;	// Behavior plugins specific info (list of declared behavior GUIDS)

	CKBOOL			m_Active;			// For manager and Render engines TRUE if a manager was created, for other plugins this value is not used.
	int				m_IndexInCategory;	// Index of this entry in its category
	CKBOOL			m_NeededByFile;		// When saving a file TRUE if at least one object needs this plugin


	CKPluginEntry& operator = (const CKPluginEntry& ent);

	CKPluginEntry();

	CKPluginEntry(const CKPluginEntry& ent);

	~CKPluginEntry();
};



struct CKPluginCategory
{
	XString					m_Name;
	XArray<CKPluginEntry*>	m_Entries;

	CKPluginCategory() {}
	CKPluginCategory(const CKPluginCategory& s) {
		m_Name = s.m_Name;
		m_Entries = s.m_Entries;
	}

	// Operator
	CKPluginCategory& operator=(const CKPluginCategory& s) {
		if (&s != this) {
			m_Name = s.m_Name;
			m_Entries = s.m_Entries;
		}
		return *this;
	}
};


// Summary: Plugin declaration count function prototype
// 
// See Also:Creating New Plugins
typedef int (*CKPluginGetInfoCountFunction)();

// Summary: Plugin declaration function prototype
// 
// See Also:Creating New Plugins
typedef CKPluginInfo* (*CKPluginGetInfoFunction)(int Index);

class BML_EXPORT CKPluginManager {
public:
	int ParsePlugins(CKSTRING Directory);
	CKERROR RegisterPlugin(CKSTRING str);
	CKPluginEntry* FindComponent(CKGUID Component, int catIdx = -1);
	int AddCategory(CKSTRING cat);
	CKERROR RemoveCategory(int catIdx);
	int GetCategoryCount();
	CKSTRING GetCategoryName(int catIdx);
	int GetCategoryIndex(CKSTRING cat);
	CKERROR RenameCategory(int catIdx, CKSTRING newName);
	int GetPluginDllCount();
	CKPluginDll* GetPluginDllInfo(int PluginDllIdx);
	CKPluginDll* GetPluginDllInfo(CKSTRING PluginName, int* idx = NULL);
	CKERROR UnLoadPluginDll(int PluginDllIdx);
	CKERROR ReLoadPluginDll(int PluginDllIdx);
	int GetPluginCount(int catIdx);
	CKPluginEntry* GetPluginInfo(int catIdx, int PluginIdx);
	BOOL SetReaderOptionData(CKContext* context, void* memdata, CKParameterOut* Param, CKFileExtension ext, CKGUID* guid = NULL);
	CKParameterOut* GetReaderOptionData(CKContext* context, void* memdata, CKFileExtension ext, CKGUID* guid = NULL);
	CKBitmapReader* GetBitmapReader(CKFileExtension& ext, CKGUID* preferedGUID = NULL);
	CKSoundReader* GetSoundReader(CKFileExtension& ext, CKGUID* preferedGUID = NULL);
	CKModelReader* GetModelReader(CKFileExtension& ext, CKGUID* preferedGUID = NULL);
	CKMovieReader* GetMovieReader(CKFileExtension& ext, CKGUID* preferedGUID = NULL);
	CKERROR Load(CKContext* context, CKSTRING FileName, CKObjectArray* liste, CK_LOAD_FLAGS LoadFlags, CKCharacter* carac = NULL, CKGUID* Readerguid = NULL);
	CKERROR Save(CKContext* context, CKSTRING FileName, CKObjectArray* liste, CKDWORD SaveFlags, CKGUID* Readerguid = NULL);
};