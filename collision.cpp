//=============================================================================
// 当たり判定
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "collision.h"

//==================================================================================================================================================
//   線と点の距離
//==================================================================================================================================================
float CCollision::AABBToPoint( float fPoint, float fAABBMin, float fAABBMax, float fLen )
{
	// AABBの中に入った時
	if( fPoint > fAABBMin && fPoint < fAABBMax ) {

		// 差分の少ないほうを代入
		if( fabs(fAABBMin - fPoint) < fabs(fAABBMax - fPoint) )
		{
			fLen = fAABBMin - fPoint;
		}
		else
		{
			fLen = fAABBMax - fPoint;
		}
	}

	// 差分を返す
	return fLen;
}

//==================================================================================================================================================
//   線と点の当たり判定
//==================================================================================================================================================
bool CCollision::AABB( float fPoint, float fAABBMin, float fAABBMax )
{
	// 当たっていない時
	if( fPoint <= fAABBMin || fPoint >= fAABBMax )
	{
		// 偽を返す
		return false;
	}

	// 逆の場合真を返す
	return true;
}

//==================================================================================================================================================
//   当たり判定（矩形）
//==================================================================================================================================================
bool CCollision::Cube(D3DXVECTOR3 Pos1, D3DXVECTOR3 Scl1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Scl2)
{
	// X辺
	if (!AABB(Pos1.x,
		Pos2.x - (Scl2.x * 0.5f) - Scl1.x,
		Pos2.x + (Scl2.x * 0.5f) + Scl1.x))
	{ return FALSE; };

	// Z辺
	if (!AABB(Pos1.z,
		Pos2.z - (Scl2.z * 0.5f) - Scl1.z,
		Pos2.z + (Scl2.z * 0.5f) + Scl1.z))
	{ return FALSE; };

	// Y辺
	if (!AABB(Pos1.y,
		Pos2.y          - Scl2.y,
		Pos2.y + Scl2.y + Scl2.y))
	{ return FALSE; }

	return TRUE;
}

//==================================================================================================================================================
//   当たり判定（球）
//==================================================================================================================================================
bool CCollision::Sphere(D3DXVECTOR3 pos1, float fRadius1, D3DXVECTOR3 pos2, float fRadius2)
{
	//(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
	if (((pos2.x - pos1.x) * (pos2.x - pos1.x)) +
		((pos2.y - pos1.y) * (pos2.y - pos1.y)) +
		((pos2.z - pos1.z) * (pos2.z - pos1.z)) <= ((fRadius1 + fRadius2) * (fRadius1 + fRadius2))) {
		return TRUE;
	}
	return FALSE;
}