//=============================================================================
// �v���C���[
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
//   �R���X�g���N�^�i�������j
//=======================================================================================
CPlayerStateAttack::CPlayerStateAttack() :
	m_Move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_FloorPosY(0.0f) {}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateAttack::Update(CPlayer* pPlayer)
{
	pPlayer->HitEnemy();

	int Key = pPlayer->GetKey();
	// ��ԑJ��
	if (Key >0)
	{
		pPlayer->ChangeState(new CPlayerStateNormal);
		return;
	}

	// �ړ�����
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

	// �n�ʔ���
	if (!pPlayer->OnBlock())
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		m_FloorPosY = pMeshField->GetHeight(pPlayer->Position());
	}

	// �߂荞�ݏ���
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

	// ��ԕύX
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpUp(pPlayer->GetJumpHeight()));
		return;
	}

	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_ATTACK);
}
