//=============================================================================
// �v���C���[
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateNormal.h"
#include "playerStateMove.h"
#include "playerStateJumpUp.h"
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
//   �X�V����
//=======================================================================================
void CPlayerStateNormal::Update(CPlayer* pPlayer)
{
	m_MoveY -= PLAYER_GRAVITY;
	pPlayer->Position().y += m_MoveY;

	m_FloorPosY = pPlayer->GetFloorHeight();

	// �n�ʔ���
	if (!pPlayer->OnBlock())
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		m_FloorPosY = pMeshField->GetHeight(pPlayer->Position());
	}
	// ���n������
	if (pPlayer->Position().y < m_FloorPosY)
	{
		m_MoveY = 0.0f;
		pPlayer->Position().y = m_FloorPosY;
	}
	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_NORMAL);

	// ��Ԕ���
	if (CInputKey::InputPlayerMove())
	{
		pPlayer->ChangeState(new CPlayerStateMove);
	}
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpUp(pPlayer->GetJumpHeight()));
	}
}
