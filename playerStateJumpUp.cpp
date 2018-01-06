//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateJumpUp.h"
#include "playerStateJumpDown.h"
#include "playerStateJumpAttack.h"
#include "manager.h"
#include "mode.h"
#include "modeGame.h"
#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"

#include "player.h"
#include "meshField.h"

#include "inputKey.h"

#include "camera.h"

//=======================================================================================
//   コンストラクタ（初期化）
//=======================================================================================
CPlayerStateJumpUp::CPlayerStateJumpUp(float JumpHeight):
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f))
{
	m_Move.y = JumpHeight;
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateJumpUp::Update(CPlayer* pPlayer)
{
	int Key = pPlayer->GetKey();
	if (Key < 1)
	{
		return;
	}
	// キー判定
	pPlayer->InputKeyMove(&m_Move);

	// 移動処理
	m_Move.y -= PLAYER_GRAVITY;
	pPlayer->Position() += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;

	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_JUMPUP);

	// 状態変更
	if (m_Move.y <= 0.0f)
	{
		pPlayer->ChangeState(new CPlayerStateJumpDown(m_Move.y));
	}
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpAttack());
	}
}
