#ifndef _COLLISION_H_
#define _COLLISION_H_

//*****************************************************************************
//   “–‚½‚è”»’èƒNƒ‰ƒX’è‹`
//*****************************************************************************
class CCollision
{
public:
	static float AABBToPoint(float fPoint, float fAABBMin, float fAABBMax, float fLen);
	static bool AABB(float fPoint, float fAABBMin, float fAABBMax);
	static bool Cube(D3DXVECTOR3 Pos1, D3DXVECTOR3 Scl1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Scl2);
	static bool Sphere(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2);
};
#endif
