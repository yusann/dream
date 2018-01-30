//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateDash.h"
#include "playerStateNormal.h"
#include "playerStateJumpUp.h"
#include "playerStateJumpDown.h"
#include "playerStateAttack.h"

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
#include "sceneBillboard.h"
#include "particle.h"

//=======================================================================================
//   コンストラクタ（初期化）
//=======================================================================================
CPlayerStateDash::CPlayerStateDash():
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f)),
m_FloorPosY(0.0f){}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateDash::Update(CPlayer* pPlayer)
{
	// キー判定
	if (!CInputKey::InputPlayerDash())
	{
		pPlayer->ChangeState(new CPlayerStateNormal());
		return;
	}
	if (CInputKey::InputPlayerAttack())
	{
		pPlayer->SetMotion(CPlayer::STATE_ATTACK);
		pPlayer->ChangeState(new CPlayerStateAttack());
		return;
	}
	pPlayer->InputKeyMove(&m_Move, 1.5f);
	static int frame = 0;
	frame = frame % 10 + 1;
	if (frame == 10)
	{
		CParticle::SetParticl(CParticle::TYPE_RUN, pPlayer->Position());
	}

	// 移動処理
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
	else if(pPlayer->Position().y- m_FloorPosY > 8.0f)
	{
		pPlayer->ChangeState(new CPlayerStateJumpDown(m_Move.y));
	}

	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_DASH);

	// 状態変更
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpUp(pPlayer->GetJumpHeight()));
	}
}
