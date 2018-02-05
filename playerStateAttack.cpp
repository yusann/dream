//=============================================================================
// �v���C���[�i��]�U���j
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateAttack.h"
#include "playerStateNormal.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"

#include "inputKey.h"

//=======================================================================================
//   �R���X�g���N�^�i�������j
//=======================================================================================
CPlayerStateAttack::CPlayerStateAttack(float MoveY) :
	m_Move(D3DXVECTOR3(0.0f, MoveY, 0.0f)),
	m_FloorPosY(0.0f) {}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateAttack::Update(CPlayer* pPlayer)
{
	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_ATTACK);

	// �G�Ƃ̓����蔻��
	pPlayer->HitEnemy();

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

	// �߂荞�ݏ���
	if (pPlayer->Position().y < m_FloorPosY)
	{
		m_Move.y = 0.0f;
		pPlayer->Position().y = m_FloorPosY;
	}

	// ��ԑJ��
	int key = pPlayer->GetKey();
	if (key >0)
	{
		//pPlayer->ChangeState(new CPlayerStateNormal);
		return;
	}
}
