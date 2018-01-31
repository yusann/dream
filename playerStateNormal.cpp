//=============================================================================
// プレイヤー
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateNormal.h"
#include "playerStateMove.h"
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

CPlayerStateNormal::CPlayerStateNormal():
	m_FloorPosY(0.0f),
	m_MoveY (0.0f){}

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateNormal::Update(CPlayer* pPlayer)
{
	m_MoveY -= PLAYER_GRAVITY;
	pPlayer->Position().y += m_MoveY;

	m_FloorPosY = pPlayer->GetFloorHeight();

	// 地面判定
	if (!pPlayer->OnBlock())
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		m_FloorPosY = pMeshField->GetHeight(pPlayer->Position());
	}
	// 着地時処理
	if (pPlayer->Position().y < m_FloorPosY)
	{
		m_MoveY = 0.0f;
		pPlayer->Position().y = m_FloorPosY;
	}
	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_NORMAL);

	// 状態判定
	if (pPlayer->Position().y - m_FloorPosY > 8.0f)
	{
		pPlayer->ChangeState(new CPlayerStateJumpDown(m_MoveY));
		return;
	}
	if (CInputKey::InputPlayerMove())
	{
		pPlayer->ChangeState(new CPlayerStateMove);
		return;
	}
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpUp(pPlayer->GetJumpHeight()));
		return;
	}
	if (CInputKey::InputPlayerAttack())
	{
		pPlayer->ChangeState(new CPlayerStateAttack(m_MoveY));
		return;
	}
}
