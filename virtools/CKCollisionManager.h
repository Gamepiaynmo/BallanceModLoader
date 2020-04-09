#pragma once

#include "CKDef.h"
#include "CKBaseManager.h"
#include "CK3dEntity.h"

struct ImpactDesc {
	CK_ID m_OwnerEntity;
	CK_ID m_ObstacleTouched;
	CK_ID m_SubObstacleTouched;
	int m_TouchedVertex;
	int m_TouchingVertex;
	int m_TouchedFace;
	int m_TouchingFace;
	VxMatrix m_ImpactWorldMatrix;
	VxVector m_ImpactPoint;
	VxVector m_ImpactNormal;
	CK_ID m_Entity;
};

class BML_EXPORT CKCollisionManager : public CKBaseManager {
public:
	void AddObstacle(CK3dEntity* ent, CKBOOL moving = FALSE, CK_GEOMETRICPRECISION precision = CKCOLLISION_BOX, CKBOOL hiera = FALSE);
	int	AddObstaclesByName(CKLevel* level, CKSTRING substring, CKBOOL moving = FALSE, CK_GEOMETRICPRECISION precision = CKCOLLISION_BOX, CKBOOL hiera = FALSE);
	void RemoveObstacle(CK3dEntity* ent);
	void RemoveAllObstacles(CKBOOL level = TRUE);
	CKBOOL IsObstacle(CK3dEntity* ent, CKBOOL moving = FALSE);
	int GetFixedObstacleCount(CKBOOL level = FALSE);
	CK3dEntity* GetFixedObstacle(int pos, CKBOOL level = FALSE);
	int GetMovingObstacleCount(CKBOOL level = FALSE);
	CK3dEntity* GetMovingObstacle(int pos, CKBOOL level = FALSE);
	int GetObstacleCount(CKBOOL level = FALSE);
	CK3dEntity* GetObstacle(int pos, CKBOOL level = FALSE);
	CKBOOL DetectCollision(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level, int replacementPrecision, int detectionPrecision, CK_IMPACTINFO inmpactFlags, ImpactDesc* imp);
	CKBOOL ObstacleBetween(const VxVector& pos, const VxVector& endpos, float width, float height);
	CKBOOL BoxBoxIntersection(CK3dEntity* ent1, CKBOOL hiera1, CKBOOL local1, CK3dEntity* ent2, CKBOOL hiera2, CKBOOL local2);
	CKBOOL BoxFaceIntersection(CK3dEntity* ent1, CKBOOL hiera1, CKBOOL local1, CK3dEntity* ent2);
	CKBOOL FaceFaceIntersection(CK3dEntity* ent1, CK3dEntity* ent2);
	CKBOOL IsInCollision(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level1, CK3dEntity* ent2, CK_GEOMETRICPRECISION precis_level2);
	CK3dEntity* IsInCollisionWithHierarchy(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level1, CK3dEntity* ent2, CK_GEOMETRICPRECISION precis_level2);
	CKBOOL IsHierarchyInCollisionWithHierarchy(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level1, CK3dEntity* ent2, CK_GEOMETRICPRECISION precis_level2, CK3dEntity** sub, CK3dEntity** subob);
	CK3dEntity* ObstacleBetween(const VxVector& pos, const VxVector& endpos, CKBOOL iFace = TRUE, CKBOOL iFirstContact = FALSE, CKBOOL iIgnoreAlpha = FALSE, VxIntersectionDesc* oDesc = NULL);

protected:
	CKCollisionManager() {};
	~CKCollisionManager() {};
};