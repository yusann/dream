//=============================================================================
// �v���C���[�i�W�����v_�~���j
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
//   �R���X�g���N�^�i�������j
//=======================================================================================
CPlayerStateJumpDown::CPlayerStateJumpDown(float JumpHeight):
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f))
{
	m_Move.y = JumpHeight;
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateJumpDown::Update(CPlayer* pPlayer)
{
	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_JUMPDOWN);

	// �L�[����
	if (CInputKey::InputPlayerDash())
	{
		pPlayer->InputKeyMove(&m_Move, 1.2f);
	}
	else
	{
		pPlayer->InputKeyMove(&m_Move);
	}

	// �ړ�����
	m_Move.y -= PLAYER_GRAVITY;
	pPlayer->Position() += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;

	m_FloorHeight = pPlayer->GetFloorHeight();

	// ��ԕύX
	// ���n��
	float playerPosY = pPlayer->Position().y;
	if (playerPosY < m_FloorHeight)
	{
		m_Move.y = 0.0f;
		pPlayer->Position().y = m_FloorHeight;
		pPlayer->ChangeState(new CPlayerStateNormal);
		return;
	}
	// ��苗���̗�����
	if (playerPosY - m_FloorHeight > 8.0f)
	{
		// ��ԕύX
		if (CInputKey::InputPlayerJump())
		{
			pPlayer->ChangeState(new CPlayerStateJumpAttack());
		}
	}
	// �A�^�b�N�L�[��������
	if (CInputKey::InputPlayerAttack())
	{
		pPlayer->ChangeState(new CPlayerStateAttack(m_Move.y));
		return;
	}
}
