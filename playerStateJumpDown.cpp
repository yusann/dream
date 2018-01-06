//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateJumpDown.h"
#include "playerStateNormal.h"
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
	// キー判定
	pPlayer->InputKeyMove(&m_Move);

	// 移動処理
	m_Move.y -= PLAYER_GRAVITY;
	pPlayer->Position() += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;

	m_FloorHeight = pPlayer->GetFloorHeight();

	// 地面判定
	if (!pPlayer->OnBlock())
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		m_FloorHeight = pMeshField->GetHeight(pPlayer->Position());
	}

	// めり込み処理
	if (pPlayer->Position().y < m_FloorHeight)
	{
		m_Move.y = 0.0f;
		pPlayer->Position().y = m_FloorHeight;
		pPlayer->ChangeState(new CPlayerStateNormal);
		return;
	}

	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_JUMPDOWN);
}
