//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateAttack.h"
#include "playerStateNormal.h"
#include "playerStateJumpDown.h"
#include "playerStateJumpUp.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"
#include "meshField.h"

#include "mode.h"
#include "modeGame.h"
#include "inputKey.h"

//=======================================================================================
//   コンストラクタ（初期化）
//=======================================================================================
CPlayerStateAttack::CPlayerStateAttack() :
	m_Move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_FloorPosY(0.0f) {}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateAttack::Update(CPlayer* pPlayer)
{
	pPlayer->HitEnemy();

	int Key = pPlayer->GetKey();
	// 状態遷移
	if (Key >0)
	{
		pPlayer->ChangeState(new CPlayerStateNormal);
		return;
	}

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

	// 地面判定
	if (!pPlayer->OnBlock())
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		m_FloorPosY = pMeshField->GetHeight(pPlayer->Position());
	}

	// めり込み処理
	if (pPlayer->Position().y < m_FloorPosY)
	{
		m_Move.y = 0.0f;
		pPlayer->Position().y = m_FloorPosY;
	}
	else if (pPlayer->Position().y - m_FloorPosY > 8.0f)
	{
		pPlayer->ChangeState(new CPlayerStateJumpDown(m_Move.y));
		return;
	}

	// 状態変更
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpUp(pPlayer->GetJumpHeight()));
		return;
	}

	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_ATTACK);
}
