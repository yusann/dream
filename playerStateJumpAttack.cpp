//=============================================================================
// �v���C���[
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
//   �R���X�g���N�^�i�������j
//=======================================================================================
CPlayerStateJumpAttack::CPlayerStateJumpAttack():
m_MoveY(0.0f)
{
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateJumpAttack::Update(CPlayer* pPlayer)
{
	int Key = pPlayer->GetKey();
	if (Key > 1)
	{
		m_MoveY -= PLAYER_GRAVITY * 4;
	}
	pPlayer->HitEnemy();

	// �ړ�����
	pPlayer->Position().y += m_MoveY;

	// �v���C���[�ɑΉ����鏰�̍���
	m_FloorHeight = pPlayer->GetFloorHeight();

	// �n�ʔ���
	if (!pPlayer->OnBlock())
	{
		CMeshField *pMeshField = CModeGame::GetMeshField();
		if (pMeshField == NULL) { return; }
		m_FloorHeight = pMeshField->GetHeight(pPlayer->Position());
	}

	// �߂荞�ݏ���
	if (pPlayer->Position().y < m_FloorHeight)
	{
		m_MoveY = 0.0f;
		pPlayer->Position().y = m_FloorHeight;
		pPlayer->ChangeState(new CPlayerStateLoading);
		return;
	}

	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_JUMPATTACK);
}
