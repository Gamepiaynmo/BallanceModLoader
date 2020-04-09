#include "CKCollisionManager.h"

NAKED void CKCollisionManager::AddObstacle(CK3dEntity* ent, CKBOOL moving, CK_GEOMETRICPRECISION precision, CKBOOL hiera) {
	JUMPV(0x78);
}

NAKED int CKCollisionManager::AddObstaclesByName(CKLevel* level, CKSTRING substring, CKBOOL moving, CK_GEOMETRICPRECISION precision, CKBOOL hiera) {
	JUMPV(0x7c);
}

NAKED void CKCollisionManager::RemoveObstacle(CK3dEntity* ent) {
	JUMPV(0x80);
}

NAKED void CKCollisionManager::RemoveAllObstacles(CKBOOL level) {
	JUMPV(0x84);
}

NAKED CKBOOL CKCollisionManager::IsObstacle(CK3dEntity* ent, CKBOOL moving) {
	JUMPV(0x88);
}

NAKED int CKCollisionManager::GetFixedObstacleCount(CKBOOL level) {
	JUMPV(0x8c);
}

NAKED CK3dEntity* CKCollisionManager::GetFixedObstacle(int pos, CKBOOL level) {
	JUMPV(0x90);
}

NAKED int CKCollisionManager::GetMovingObstacleCount(CKBOOL level) {
	JUMPV(0x94);
}

NAKED CK3dEntity* CKCollisionManager::GetMovingObstacle(int pos, CKBOOL level) {
	JUMPV(0x98);
}

NAKED int CKCollisionManager::GetObstacleCount(CKBOOL level) {
	JUMPV(0x9c);
}

NAKED CK3dEntity* CKCollisionManager::GetObstacle(int pos, CKBOOL level) {
	JUMPV(0xa0);
}

NAKED CKBOOL CKCollisionManager::DetectCollision(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level, int replacementPrecision, int detectionPrecision, CK_IMPACTINFO inmpactFlags, ImpactDesc* imp) {
	JUMPV(0xa4);
}

NAKED CKBOOL CKCollisionManager::ObstacleBetween(const VxVector& pos, const VxVector& endpos, float width, float height) {
	JUMPV(0xa8);
}

NAKED CKBOOL CKCollisionManager::BoxBoxIntersection(CK3dEntity* ent1, CKBOOL hiera1, CKBOOL local1, CK3dEntity* ent2, CKBOOL hiera2, CKBOOL local2) {
	JUMPV(0xac);
}

NAKED CKBOOL CKCollisionManager::BoxFaceIntersection(CK3dEntity* ent1, CKBOOL hiera1, CKBOOL local1, CK3dEntity* ent2) {
	JUMPV(0xb0);
}

NAKED CKBOOL CKCollisionManager::FaceFaceIntersection(CK3dEntity* ent1, CK3dEntity* ent2) {
	JUMPV(0xb4);
}

NAKED CKBOOL CKCollisionManager::IsInCollision(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level1, CK3dEntity* ent2, CK_GEOMETRICPRECISION precis_level2) {
	JUMPV(0xb8);
}

NAKED CK3dEntity* CKCollisionManager::IsInCollisionWithHierarchy(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level1, CK3dEntity* ent2, CK_GEOMETRICPRECISION precis_level2) {
	JUMPV(0xbc);
}

NAKED CKBOOL CKCollisionManager::IsHierarchyInCollisionWithHierarchy(CK3dEntity* ent, CK_GEOMETRICPRECISION precis_level1, CK3dEntity* ent2, CK_GEOMETRICPRECISION precis_level2, CK3dEntity** sub, CK3dEntity** subob) {
	JUMPV(0xc0);
}

NAKED CK3dEntity* CKCollisionManager::ObstacleBetween(const VxVector& pos, const VxVector& endpos, CKBOOL iFace, CKBOOL iFirstContact, CKBOOL iIgnoreAlpha, VxIntersectionDesc* oDesc) {
	JUMPV(0xc4);
}
