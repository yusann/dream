//=============================================================================
// プレイヤー（回転攻撃）
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateAttack.h"
#include "playerStateNormal.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"

#include "inputKey.h"

//=======================================================================================
//   コンストラクタ（初期化）
//=======================================================================================
CPlayerStateAttack::CPlayerStateAttack(float MoveY) :
	m_Move(D3DXVECTOR3(0.0f, MoveY, 0.0f)),
	m_FloorPosY(0.0f) {}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateAttack::Update(CPlayer* pPlayer)
{
	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_ATTACK);

	// 敵との当たり判定
	pPlayer->HitEnemy();

	// 移動処理
	if (CInputKey::InputPlayerDash())
	{
		pPlayer->InputKeyMove(&m_Move,1.5f);
	}
	else
	{
		pPlayer->InputKeyMove(&m_Move);
	}
	m_Move.y -= PLAYER_GRAVITY;
	pPlayer->Position() += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;

	m_FloorPosY = pPlayer->GetFloorHeight();

	// めり込み処理
	if (pPlayer->Position().y < m_FloorPosY)
	{
		m_Move.y = 0.0f;
		pPlayer->Position().y = m_FloorPosY;
	}

	// 状態遷移
	int key = pPlayer->GetKey();
	if (key >0)
	{
		//pPlayer->ChangeState(new CPlayerStateNormal);
		return;
	}
}
