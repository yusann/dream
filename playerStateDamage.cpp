//=============================================================================
// プレイヤー（受け身）
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateDamage.h"
#include "playerStateLoading.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"
#include "meshField.h"

//=======================================================================================
//   コンストラクタ（初期化）
//=======================================================================================
CPlayerStateDamage::CPlayerStateDamage(D3DXVECTOR2 damageVector) :
	m_DamageVector(damageVector),
	m_MoveY(1.0f){}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateDamage::Update(CPlayer* pPlayer)
{
	m_MoveY -= PLAYER_GRAVITY;
	pPlayer->Position().y += m_MoveY;
	pPlayer->DamageMove(m_DamageVector);

	float floorPosY = pPlayer->GetFloorHeight();

	// 着地時処理
	if (pPlayer->Position().y < floorPosY)
	{
		m_MoveY = 0.0f;
		pPlayer->Position().y = floorPosY;
		pPlayer->ChangeState(new CPlayerStateLoading);
	}

	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_DAMAGE);
}
