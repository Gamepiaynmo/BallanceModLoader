/*************************************************************************/
/*	File : CKGlobals.h						 		 					 */
/*																		 */	
/*  Globals Functions for Virtools SDK										 */
/*																		 */	
/*	Virtools SDK 															 */	 
/*	Copyright (c) Virtools 2000, All Rights Reserved.					 */	
/*************************************************************************/
#ifndef _CKGLOBALS_H

#define _CKGLOBALS_H "$Id:$"

#include "CKDef.h"
#include "XBitArray.h"

typedef XHashTable<CKObjectDeclaration*,CKGUID>::Iterator XObjDeclHashTableIt;		

#define  CKCID_OBJECT					1		
#define  CKCID_PARAMETERIN				2	
#define  CKCID_PARAMETEROPERATION		4	
#define  CKCID_STATE					5	
#define  CKCID_BEHAVIORLINK				6	
#define  CKCID_BEHAVIOR					8	
#define  CKCID_BEHAVIORIO				9	
#define  CKCID_RENDERCONTEXT			12	
#define  CKCID_KINEMATICCHAIN			13	
#define  CKCID_SCENEOBJECT				11		
#define  CKCID_OBJECTANIMATION			15	
#define  CKCID_ANIMATION				16	
#define  CKCID_KEYEDANIMATION		18	
#define  CKCID_BEOBJECT					19	
#define	 CKCID_DATAARRAY			52	
#define  CKCID_SCENE				10	
#define  CKCID_LEVEL				21	
#define  CKCID_PLACE				22	
#define  CKCID_GROUP				23	
#define  CKCID_SOUND				24	
#define  CKCID_WAVESOUND		25	
#define  CKCID_MIDISOUND		26	
#define  CKCID_MATERIAL				30	
#define  CKCID_TEXTURE				31	
#define  CKCID_MESH					32	
#define CKCID_PATCHMESH			53	
#define  CKCID_RENDEROBJECT			47	
#define  CKCID_2DENTITY			27	
#define  CKCID_SPRITE		28	
#define  CKCID_SPRITETEXT	29	
#define  CKCID_3DENTITY				33	
#define CKCID_GRID				50	
#define  CKCID_CURVEPOINT		36	
#define  CKCID_SPRITE3D			37	
#define  CKCID_CURVE			43	
#define  CKCID_CAMERA			34	
#define  CKCID_TARGETCAMERA	35	
#define  CKCID_LIGHT			38	
#define  CKCID_TARGETLIGHT	39	
#define  CKCID_CHARACTER		40	
#define  CKCID_3DOBJECT			41	
#define  CKCID_BODYPART		42	
#define  CKCID_PARAMETER				46		
#define  CKCID_PARAMETERLOCAL		45	
#define  CKCID_PARAMETERVARIABLE	55	
#define  CKCID_PARAMETEROUT			3	
#define CKCID_INTERFACEOBJECTMANAGER	48	
#define CKCID_CRITICALSECTION			49	
#define CKCID_LAYER						51	
#define CKCID_PROGRESSIVEMESH			54	
#define CKCID_SYNCHRO					20	

//-----------------------------------------------
// Initializations functions

CKERROR CKStartUp();
CKERROR CKShutdown();


CKContext* GetCKContext(int pos);

CKObject* CKGetObject(CKContext* iCtx,CK_ID iID);

CKERROR CKCreateContext(CKContext** iContext,WIN_HANDLE iWin,const char* iConfigFile = NULL);
CKERROR CKCloseContext(CKContext*);

CKSTRING		CKGetStartPath();
CKSTRING		CKGetPluginsPath();

void CKDestroyObject(CKObject *o,DWORD Flags=0,CKDependencies* dep = NULL);

CKDWORD CKGetVersion();


void CKBuildClassHierarchyTable();

CKPluginManager* CKGetPluginManager();

//----------------------------------------------------------
// Behavior prototype declaration functions

int					CKGetPrototypeDeclarationCount();
CKObjectDeclaration *CKGetPrototypeDeclaration(int n);


XObjDeclHashTableIt	CKGetPrototypeDeclarationStartIterator();

XObjDeclHashTableIt	CKGetPrototypeDeclarationEndIterator();

CKObjectDeclaration *CKGetObjectDeclarationFromGuid(CKGUID guid);
CKBehaviorPrototype *CKGetPrototypeFromGuid(CKGUID guid);
CKERROR				CKRemovePrototypeDeclaration(CKObjectDeclaration* objdecl);
CKObjectDeclaration* CreateCKObjectDeclaration(CKSTRING Name);
CKBehaviorPrototype* CreateCKBehaviorPrototype(CKSTRING Name);
CKBehaviorPrototype* CreateCKBehaviorPrototypeRunTime(CKSTRING Name);

#ifdef VIRTOOLS_RUNTIME_VERSION
#define CreateCKBehaviorPrototype CreateCKBehaviorPrototypeRunTime
#endif

/**********************************************
Summary: Helper macro to register a behavior declaration 

Arguments:
	reg: A pointer to the XObjectDeclarationArray given in the RegisterBehaviorDeclarations function.
	fct: A function that creates the behavior object declaration (CKObjectDeclaration) and returns it.
See Also:Main Steps of Building Block Creation
*************************************************/
#define RegisterBehavior(reg,fct) CKObjectDeclaration *fct(); CKStoreDeclaration(reg,fct());

//----------------------------------------------------------
// Class Hierarchy Management

typedef void (*CKCLASSREGISTERFCT)();
typedef CKObject* (*CKCLASSCREATIONFCT)(CKContext* context);
typedef void (*CKCLASSRELEASEFCT)(CKContext* context, CKObject* object);
typedef CKSTRING(*CKCLASSNAMEFCT)();
typedef CKSTRING(*CKCLASSDEPENDENCIESFCT)(int, int);
typedef int		 (*CKCLASSDEPENDENCIESCOUNTFCT)(int);

struct CKClassDesc
{
	int					Done;
	// Initialized upon class registration
	CK_CLASSID			Parent;				// Class Identifier of parent class
	CKCLASSREGISTERFCT	RegisterFct;		// Pointer to Class Specific Registration function
	CKCLASSCREATIONFCT	CreationFct;		// Pointer to Class instance creation function
	CKCLASSRELEASEFCT	ReleaseFct;		// Pointer to Class instance release function
	CKCLASSNAMEFCT		NameFct;			// Pointer to Class name function
	CKCLASSDEPENDENCIESFCT		DependsFct;		// Pointer to Class dependencies function (Copy,delete,replace...)
	CKCLASSDEPENDENCIESCOUNTFCT	DependsCountFct;// Pointer to Class dependencies Count function (Copy,delete,replace...)

	// Initialized by class specific registration function
	CKDWORD				DefaultOptions;		// Default options for this class	
	CKDWORD				DefaultCopyDependencies;
	CKDWORD				DefaultDeleteDependencies;
	CKDWORD				DefaultReplaceDependencies;
	CKDWORD				DefaultSaveDependencies;
	CKGUID				Parameter;			// Associated parameter GUID

	// Initialized when building class hierarchy table
	int					DerivationLevel;	// O => CKObject , etc..
	XBitArray			Parents;			// Bit Mask of parents classes
	XBitArray			Children;			// Bit Mask of children classes
	XBitArray			ToBeNotify;			// Mask for Classes that should warn the objects of this class when they are deleted
	XBitArray			CommonToBeNotify;	// idem but merged with sub classes masks
	XSArray<CK_CLASSID>	ToNotify;			// List of ClassID to notify when an object of this class is deleted (inverse of ToBeNotify) 					

	CKClassDesc()
	{
		Done = DerivationLevel = 0;
		DefaultOptions = DefaultCopyDependencies = DefaultDeleteDependencies = DefaultReplaceDependencies = DefaultSaveDependencies = 0;
		Parent = 0;
		RegisterFct = NULL;
		CreationFct = NULL;
		ReleaseFct = NULL;
		NameFct = NULL;
		DependsFct = NULL;
		DependsCountFct = NULL;
	}
};

int				CKGetClassCount();
CKClassDesc*		CKGetClassDesc(CK_CLASSID cid);		
CKSTRING			CKClassIDToString(CK_CLASSID cid);
CK_CLASSID		CKStringToClassID(CKSTRING classname);

CKBOOL		CKIsChildClassOf(CK_CLASSID child,CK_CLASSID parent);
CKBOOL		CKIsChildClassOf(CKObject *obj,CK_CLASSID parent);
CK_CLASSID	CKGetParentClassID(CK_CLASSID child);
CK_CLASSID	CKGetParentClassID(CKObject *obj);
CK_CLASSID	CKGetCommonParent(CK_CLASSID cid1,CK_CLASSID cid2);

//-----------------------------------------------
// Array Creation Functions	
				
CKObjectArray*  CreateCKObjectArray();
void			   DeleteCKObjectArray(CKObjectArray * obj);

//-----------------------------------------------
// StateChunk Creation Functions
					
CKStateChunk*	CreateCKStateChunk(CK_CLASSID id,CKFile* file=NULL);
CKStateChunk*	CreateCKStateChunk(CKStateChunk* chunk);
void				DeleteCKStateChunk(CKStateChunk* chunk);

CKStateChunk*	CKSaveObjectState(CKObject* obj,CKDWORD Flags = CK_STATESAVE_ALL);
CKERROR			CKReadObjectState(CKObject* obj,CKStateChunk* chunk);

//-----------------------------------------------
// Bitmap utilities 

BITMAP_HANDLE	CKLoadBitmap(CKSTRING filename);
CKBOOL			CKSaveBitmap(CKSTRING filename,BITMAP_HANDLE bm);
CKBOOL			CKSaveBitmap(CKSTRING filename,VxImageDescEx& desc);

//------------------------------------------------
//--- Endian Conversion utilities

void CKConvertEndianArray32(void* buf,int DwordCount);
void CKConvertEndianArray16(void* buf,int DwordCount);
CKDWORD CKConvertEndian32(CKDWORD dw);
CKWORD  CKConvertEndian16(CKWORD w);

//------------------------------------------------
// Compression utilities

CKDWORD CKComputeDataCRC(char* data,int size,DWORD PreviousCRC=0);
char* CKPackData(char* Data,int size,int &NewSize,int compressionlevel);
char* CKUnPackData(int DestSize,char* SrcBuffer,int SrcSize);

//-------------------------------------------------
// String Utilities 

CKSTRING CKStrdup(CKSTRING string);
CKSTRING CKStrndup(CKSTRING iString, int iLength);
void		CKStrdelete(CKSTRING str);
CKSTRING CKStrupr(CKSTRING string);
CKSTRING CKStrlwr(CKSTRING string);

//-------------------------------------------------
// CKBitmapProperties Utilities 

CKBitmapProperties* CKCopyBitmapProperties(CKBitmapProperties* bp);

#define CKDeleteBitmapProperties(bp) CKDeletePointer((void *)bp)

//-------------------------------------------------
// Class Dependencies utilities

void CKCopyDefaultClassDependencies(CKDependencies& d,CK_DEPENDENCIES_OPMODE mode);
CKDependencies* CKGetDefaultClassDependencies(CK_DEPENDENCIES_OPMODE mode);

void		CKDeletePointer(void* ptr);

//-------------------------------------------------------------------
#ifdef DOCJETDUMMY // Docjet secret macro
#else

//-------------------------------------------------
// Merge Utilities
CKERROR CKCopyAllAttributes(CKBeObject* Src,CKBeObject* Dest);
CKERROR CKMoveAllScripts(CKBeObject* Src,CKBeObject* Dest);
CKERROR CKMoveScript(CKBeObject* Src,CKBeObject* Dest,CKBehavior *Beh);
void CKRemapObjectParameterValue(CKContext *ckContext,CK_ID oldID,CK_ID newID,CK_CLASSID cid = CKCID_OBJECT,CKBOOL derived=TRUE);	

typedef XArray<CKObjectDeclaration*> XObjectDeclarationArray;
void CKStoreDeclaration(XObjectDeclarationArray* reg,CKObjectDeclaration *a);

//-------- CKClass Registration 
#define CKCLASSNOTIFYFROM(cls1,cls2) CKClassNeedNotificationFrom(cls1::m_ClassID,cls2::m_ClassID)
#define CKCLASSNOTIFYFROMCID(cls1,cid) CKClassNeedNotificationFrom(cls1::m_ClassID,cid)			
#define CKPARAMETERFROMCLASS(cls,pguid) CKClassRegisterAssociatedParameter(cls::m_ClassID,pguid)	
#define CKCLASSDEFAULTCOPYDEPENDENCIES(cls1,depend_Mask) CKClassRegisterDefaultDependencies(cls1::m_ClassID,depend_Mask,CK_DEPENDENCIES_COPY)		
#define CKCLASSDEFAULTDELETEDEPENDENCIES(cls1,depend_Mask) CKClassRegisterDefaultDependencies(cls1::m_ClassID,depend_Mask,CK_DEPENDENCIES_DELETE)	
#define CKCLASSDEFAULTREPLACEDEPENDENCIES(cls1,depend_Mask) CKClassRegisterDefaultDependencies(cls1::m_ClassID,depend_Mask,CK_DEPENDENCIES_REPLACE)	
#define CKCLASSDEFAULTSAVEDEPENDENCIES(cls1,depend_Mask) CKClassRegisterDefaultDependencies(cls1::m_ClassID,depend_Mask,CK_DEPENDENCIES_SAVE)		
#define CKCLASSDEFAULTOPTIONS(cls1,options_Mask) CKClassRegisterDefaultOptions(cls1::m_ClassID,options_Mask)	


#define CKCLASSREGISTER(cls1,Parent_Class)\
{\
	if (cls1::m_ClassID<=0)  cls1::m_ClassID=CKClassGetNewIdentifier();\
	CKClassRegister(cls1::m_ClassID,Parent_Class::m_ClassID,cls1::Register,(CKCLASSCREATIONFCT)cls1::CreateInstance,(CKCLASSRELEASEFCT)cls1::ReleaseInstance,cls1::GetClassName,cls1::GetDependencies,cls1::GetDependenciesCount);\
}\


#define CKCLASSREGISTERCID(cls1,Parent_Class)\
{\
	if (cls1::m_ClassID<=0)  cls1::m_ClassID=CKClassGetNewIdentifier();\
	CKClassRegister(cls1::m_ClassID,Parent_Class,cls1::Register,(CKCLASSCREATIONFCT)cls1::CreateInstance,(CKCLASSRELEASEFCT)cls1::ReleaseInstance,cls1::GetClassName,cls1::GetDependencies,cls1::GetDependenciesCount);\
}\


void CKClassNeedNotificationFrom(CK_CLASSID Cid1,CK_CLASSID Cid2);						
void CKClassRegisterAssociatedParameter(CK_CLASSID Cid,CKGUID pguid);					
void CKClassRegisterDefaultDependencies(CK_CLASSID Cid,CKDWORD depend_Mask,int mode);	
void CKClassRegisterDefaultOptions(CK_CLASSID Cid,CKDWORD options_Mask);					
CK_CLASSID CKClassGetNewIdentifier();													
void		  CKClassRegister(CK_CLASSID Cid,CK_CLASSID Parent_Cid,
								CKCLASSREGISTERFCT registerfct,CKCLASSCREATIONFCT creafct,CKCLASSRELEASEFCT relfct,
								CKCLASSNAMEFCT		NameFct,CKCLASSDEPENDENCIESFCT	DependsFct,
								CKCLASSDEPENDENCIESCOUNTFCT	DependsCountFct);						




#endif // Docjet secret macro
#endif
