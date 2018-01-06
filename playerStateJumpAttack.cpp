//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateJumpAttack.h"
#include "playerStateLoading.h"
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
CPlayerStateJumpAttack::CPlayerStateJumpAttack():
m_MoveY(0.0f)
{
}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateJumpAttack::Update(CPlayer* pPlayer)
{
	int Key = pPlayer->GetKey();
	if (Key > 1)
	{
		m_MoveY -= PLAYER_GRAVITY * 4;
	}
	pPlayer->HitEnemy();

	// 移動処理
	pPlayer->Position().y += m_MoveY;

	// プレイヤーに対応する床の高さ
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
		m_MoveY = 0.0f;
		pPlayer->Position().y = m_FloorHeight;
		pPlayer->ChangeState(new CPlayerStateLoading);
		return;
	}

	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_JUMPATTACK);
}
