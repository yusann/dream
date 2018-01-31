//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateJumpDown.h"
#include "playerStateNormal.h"
#include "playerStateJumpAttack.h"
#include "playerStateAttack.h"

#include "mode.h"
#include "modeGame.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"

#include "inputKey.h"
#include "camera.h"

//=======================================================================================
//   コンストラクタ（初期化）
//=======================================================================================
CPlayerStateJumpDown::CPlayerStateJumpDown(float JumpHeight):
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f))
{
	m_Move.y = JumpHeight;
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateJumpDown::Update(CPlayer* pPlayer)
{
	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_JUMPDOWN);

	// キー判定
	if (CInputKey::InputPlayerDash())
	{
		pPlayer->InputKeyMove(&m_Move, 1.2f);
	}
	else
	{
		pPlayer->InputKeyMove(&m_Move);
	}

	// 移動処理
	m_Move.y -= PLAYER_GRAVITY;
	pPlayer->Position() += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;

	m_FloorHeight = pPlayer->GetFloorHeight();

	// 状態変更
	// 着地時
	float playerPosY = pPlayer->Position().y;
	if (playerPosY < m_FloorHeight)
	{
		m_Move.y = 0.0f;
		pPlayer->Position().y = m_FloorHeight;
		pPlayer->ChangeState(new CPlayerStateNormal);
		return;
	}
	// 一定距離の落下時
	if (playerPosY - m_FloorHeight > 8.0f)
	{
		// 状態変更
		if (CInputKey::InputPlayerJump())
		{
			pPlayer->ChangeState(new CPlayerStateJumpAttack());
		}
	}
	// アタックキー押した時
	if (CInputKey::InputPlayerAttack())
	{
		pPlayer->ChangeState(new CPlayerStateAttack(m_Move.y));
		return;
	}
}
