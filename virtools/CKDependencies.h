#pragma once

#include "XSArray.h"
#include "XObjectArray.h"
#include "XHashTable.h"

// Destroy Dependencies
// Defines which dependencies of an object  should also be destroyed
#define CK_DEPENDENCIES_DESTROY_BEOBJECT_SCRIPTS		1	// Destroy Object scripts, Default : On
#define CK_DEPENDENCIES_DESTROY_MATERIAL_TEXTURE		1	// Destroy Material texture, Default : Off
#define CK_DEPENDENCIES_DESTROY_MESH_MATERIAL			1   // Destroy Mesh materials, Default : Off
#define CK_DEPENDENCIES_DESTROY_3DENTITY_MESH			1	// Destroy 3DEntity meshes, Default : Off	
#define CK_DEPENDENCIES_DESTROY_3DENTITY_CHILDREN		2	// Destroy 3DEntity hierarchy, Default : Off
#define CK_DEPENDENCIES_DESTROY_3DENTITY_ANIMATIONS		4	// Destroy 3DEntity animations, Default : On
#define CK_DEPENDENCIES_DESTROY_DATAARRAY_OBJECTS		1	// Destroy objects referenced by a DataArray, Default: Off
#define CK_DEPENDENCIES_DESTROY_PLACE_PORTALS			1	// Destroy portals referenced by a Plane, Default : Off
#define CK_DEPENDENCIES_DESTROY_SPRITE3D_MATERIAL		1	// Destroy Sprite3D material, Default : Off
#define CK_DEPENDENCIES_DESTROY_TARGETLIGHT_TARGET		1	// Destroy TargetLight target 3DEntity, Default : Off
#define CK_DEPENDENCIES_DESTROY_TARGETCAMERA_TARGET		1	// Destroy TargetCamera target 3DEntity, Default : Off
#define CK_DEPENDENCIES_DESTROY_GROUP_OBJECTS			1	// Destroy every objects referenced by the Group, Default : Off

// Copy Dependencies
// Defines which dependencies of an object should also be copied
#define CK_DEPENDENCIES_COPY_OBJECT_NAME			1		// Copy object name, Default : On
#define CK_DEPENDENCIES_COPY_OBJECT_UNIQUENAME		2		// Ensure name uniqueness when copying, Default : On
#define CK_DEPENDENCIES_COPY_SCENEOBJECT_SCENES		1		// Add copy to every scenes the source was belonging to, Default : On
#define CK_DEPENDENCIES_COPY_BEOBJECT_SCRIPTS		1		// Copy BeObject scripts, Default : On
#define CK_DEPENDENCIES_COPY_BEOBJECT_ATTRIBUTES	2		// Copy BeObject attributes, Default : On
#define CK_DEPENDENCIES_COPY_BEOBJECT_GROUPS		4		// If BeObject belongs to a group, adds its copy to the group, Default : On
#define CK_DEPENDENCIES_COPY_MATERIAL_TEXTURE		1		// Copy Material texture, Default : Off 
#define CK_DEPENDENCIES_COPY_MESH_MATERIAL			1		// Copy Mesh materials, Default : Off
#define CK_DEPENDENCIES_COPY_3DENTITY_MESH			1		// Copy 3DEntity meshes, Default : On
#define CK_DEPENDENCIES_COPY_3DENTITY_CHILDREN		2		// Copy 3DEntity hierarchy, Default : On
#define CK_DEPENDENCIES_COPY_3DENTITY_ANIMATIONS	4		// Copy 3DEntity animation, Default : On
#define CK_DEPENDENCIES_COPY_CHARACTER_SHAREANIMS	1		// When copying a character shares its animation data, Default : On
#define CK_DEPENDENCIES_COPY_DATAARRAY_OBJECTS		1		// When copying a DataArray, this options also copies the objects referenced, Default : Off
#define CK_DEPENDENCIES_COPY_DATAARRAY_DATA			2		// Copy DataArray contents, Default : On
#define CK_DEPENDENCIES_COPY_PLACE_PORTALS			1		// Copy portals referenced by a Plane, Default : On
#define CK_DEPENDENCIES_COPY_SPRITE_SHAREBITMAP		1		// Sprite copy will share its bitmap data with the source sprite, Default : On
#define CK_DEPENDENCIES_COPY_SPRITE3D_MATERIAL		1		// Copy Sprite3D material, Default : On
#define CK_DEPENDENCIES_COPY_TARGETLIGHT_TARGET		1		// Copy TargetLight target 3DEntity, Default : On
#define CK_DEPENDENCIES_COPY_TARGETCAMERA_TARGET	1		// Copy TargetCamera target 3DEntity, Default : On
#define CK_DEPENDENCIES_COPY_GROUP_OBJECTS			1		// Copy every objects referenced by the Group, Default : On
#define CK_DEPENDENCIES_COPY_GRID_LAYERS			1		// Copy Grid layers, Default : On
#define CK_DEPENDENCIES_COPY_GRIDLAYER_DATA			1		// Copy Layer Data, Default : On

// Save Dependencies
// Defines which dependencies of an object should also be saved
#define CK_DEPENDENCIES_SAVE_OBJECT_NAME			1		// Save Object name, Default : On
#define CK_DEPENDENCIES_SAVE_BEOBJECT_SCRIPTS		1		// Save BeObject scripts, Default : On
#define CK_DEPENDENCIES_SAVE_BEOBJECT_ATTRIBUTES	2		// Save BeObject attributes, Default : On
#define CK_DEPENDENCIES_SAVE_BEOBJECT_GROUPS		4		// Save groups this object belongs to, Default : On
#define CK_DEPENDENCIES_SAVE_MATERIAL_TEXTURE		1		// Save Material texture, Default : On 
#define CK_DEPENDENCIES_SAVE_MESH_MATERIAL			1		// Save Mesh materials, Default : On
#define CK_DEPENDENCIES_SAVE_3DENTITY_MESH			1		// Save 3DEntity meshes, Default : On
#define CK_DEPENDENCIES_SAVE_3DENTITY_CHILDREN		2		// Save 3DEntity children, Default : On
#define CK_DEPENDENCIES_SAVE_3DENTITY_ANIMATIONS	4		// Save 3DEntity animations, Default : On
#define CK_DEPENDENCIES_SAVE_PLACE_PORTALS			1		// Save portals referenced by a Plane, Default : On
#define CK_DEPENDENCIES_SAVE_SPRITE3D_MATERIAL		1		// Save Sprite3D material, Default : On
#define CK_DEPENDENCIES_SAVE_TARGETLIGHT_TARGET		1		// Save TargetLight target 3DEntity, Default : On
#define CK_DEPENDENCIES_SAVE_TARGETCAMERA_TARGET	1		// Save TargetCamera target 3DEntity, Default : On
#define CK_DEPENDENCIES_SAVE_GROUP_OBJECTS			1		// Save every objects referenced by the Group, Default : On

typedef XHashTable<CK_ID, CK_ID>			XHashID;
typedef XHashID::Iterator				XHashItID;
typedef XHashID::ConstIterator			XHashItCID;
typedef XHashID::Pair					XHashPairID;

typedef enum CK_DEPENDENCIES_FLAGS {
	CK_DEPENDENCIES_CUSTOM = 0x00000000,	// Dependencies will depends on what options where modified in CKDependencies
	CK_DEPENDENCIES_NONE = 0x00000001,	// No dependencies will be taken into account
	CK_DEPENDENCIES_FULL = 0x00000002	// Every dependencies will be taken
} CK_DEPENDENCIES_FLAGS;

class BML_EXPORT CKDependencies : public XSArray<CKDWORD> {
public:

	CKDependencies() :XSArray<CKDWORD>(), m_Flags(CK_DEPENDENCIES_NONE) {}

	void ModifyOptions(CK_CLASSID cid, CKDWORD add, CKDWORD rem)
	{
		(*this)[cid] |= add;
		(*this)[cid] &= ~rem;
	}

	CK_DEPENDENCIES_FLAGS	m_Flags;
};

class CKDependenciesContext {
	friend class CKObject;
	friend class CKStateChunk;
	friend class CKContext;
	friend class CKUIManager;
public:


	CKDependenciesContext(CKContext* context) : m_Dependencies(NULL),
		m_MapID(256),
		m_Mode(CK_DEPENDENCIES_BUILD),
		m_CKContext(context),
		m_CreationMode(CK_OBJECTCREATION_NONAMECHECK),
		m_DynamicStack(0)
	{
		//	m_CallerStack.Reserve(32);
	}


	// Objects Access
	void		AddObjects(CK_ID* ids, int count);
	int			GetObjectsCount();
	CKObject* GetObjects(int i);

	/*************************************************
	Summary: Remaps a CK_ID.

	Arguments:
		id : the CK_ID to remap. If the object was in
	the dependencies context, it is changed. Otherwise, it remains unchanged.

	Return Value:
		Returns the remapped value of the CK_ID given, or the
	old value if it wasn't in the dependencies context.

	See also: Remap
	*************************************************/
	CK_ID		RemapID(CK_ID& id);

	/*************************************************
	Summary: Remaps a CKObject.
	Arguments:
		o : the CKObject to remap.
	Return Value:
		Returns the remapped object, or the old object if it wasn't in the dependencies context.
	See also: RemapID
	*************************************************/
	CKObject* Remap(const CKObject* o);


	/*************************************************
	Summary: Tests if a CK_ID is in the dependencies context.

	Arguments:
		id : CK_ID to test.

	Return Value:
		TRUE if the object is here, FALSE otherwise.

	See also: RemapID
	*************************************************/
	CKBOOL IsDependenciesHere(CK_ID id) { return m_MapID.IsHere(id); }

	/// Dependencies access
	XObjectArray FillDependencies();
	XObjectArray FillRemappedDependencies();

	/*************************************************
	Summary: Sets dependencies options for the subsequent operations
	to come.

	Arguments:
		d : a CKDependencies.

	Remarks:
		You'll need to call this function before calling Copy()
	for example if you wan't full or custom dependencies to be
	taken into account.

	See also: CKDependencies,StopDependencies
	*************************************************/
	void StartDependencies(CKDependencies* d) { m_DependenciesStack.PushBack(d); m_Dependencies = d; }

	/*************************************************
	Summary: Stops using the actual dependencies options.

	Remarks:
		You'll need to call this function before calling Copy()
	for example if you wan't full or custom dependencies to be
	taken into account.

	See also: CKDependencies, StartDependencies
	*************************************************/
	void StopDependencies() {
		m_DependenciesStack.PopBack();
		m_Dependencies = ((m_DependenciesStack.Size()) ? m_DependenciesStack.Back() : NULL);
	}

	CKDWORD GetClassDependencies(int c);

	void Copy(CKSTRING appendstring = NULL);

	/*************************************************
	Summary: Sets the operation mode for this dependencies context.

	Arguments:
		m : the operation mode desired.

	See also: CK_DEPENDENCIES_OPMODE, IsInMode
	*************************************************/
	void SetOperationMode(CK_DEPENDENCIES_OPMODE m) { m_Mode = m; }

	/*************************************************
	Summary: Gets the operation mode for this dependencies context.

	Return Value:
		The operation mode desired.

	See also: CK_DEPENDENCIES_OPMODE, SetOperationMode
	*************************************************/
	CKBOOL IsInMode(CK_DEPENDENCIES_OPMODE m) { return ((CK_DEPENDENCIES_OPMODE)m_Mode == m); }

	/*************************************************
	Summary: Sets the creation mode for subsequent object creation.

	Arguments:
		m : the creation mode desired.

	See also: CK_DEPENDENCIES_OPMODE, IsInMode
	*************************************************/
	void SetCreationMode(CK_OBJECTCREATION_OPTIONS m) { m_CreationMode = m; }

	CKBOOL ContainClassID(CK_CLASSID Cid);

	//-------------------------------------------------------------------------
	// Internal functions 
#ifdef DOCJETDUMMY // DOCJET secret macro
#else

	struct DynamicSentinel
	{
		DynamicSentinel(CKDependenciesContext* iDepContext) :dc(iDepContext)
		{
			if (dc)
				++dc->m_DynamicStack;
		}
		~DynamicSentinel()
		{
			if (dc)
				--dc->m_DynamicStack;
		}
		CKDependenciesContext* dc;
	};
	friend struct DynamicSentinel;


	DynamicSentinel StackPrepareDependencies(CKObject* iMySelf, CKBOOL iCaller);

	// the context
	CKContext* m_CKContext;

	const XHashID& GetDependenciesMap() const
	{
		return m_MapID;
	}
protected:

	// Add Object 
	CKBOOL AddDependencies(CK_ID id);

	void Clear();

	CKDependencies* m_Dependencies;
	// Remapping Hashtable						
	XHashID					m_MapID;
	// Objects to process						
	XObjectArray			m_Objects;
	// Objects to process						
	XArray<CKDependencies*>	m_DependenciesStack;
	// In there are sccripts in the objects being processed they will also be stored here 
	XObjectArray			m_Scripts;

	CKDWORD					m_Mode;
	CKDWORD					m_CreationMode;

	// dynamic objects currently prepared
	int						m_DynamicStack;

	XString				m_CopyAppendString;
	XBitArray			m_ObjectsClassMask;
#endif // docjet secret macro
};