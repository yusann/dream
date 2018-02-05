//=============================================================================
// �v���C���[�i�W�����v_�㏸�j
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateJumpUp.h"
#include "playerStateJumpDown.h"
#include "playerStateJumpAttack.h"
#include "playerStateAttack.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"

#include "inputKey.h"
#include "camera.h"

//=======================================================================================
//   �R���X�g���N�^�i�������j
//=======================================================================================
CPlayerStateJumpUp::CPlayerStateJumpUp(float JumpHeight):
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f))
{
	m_Move.y = JumpHeight;
}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateJumpUp::Update(CPlayer* pPlayer)
{
	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_JUMPUP);

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

	// ��ԕύX
	if (m_Move.y <= 0.0f)
	{
		pPlayer->ChangeState(new CPlayerStateJumpDown(m_Move.y));
		return;
	}
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpAttack());
		return;
	}
	if (CInputKey::InputPlayerAttack())
	{
		pPlayer->ChangeState(new CPlayerStateAttack(m_Move.y));
		return;
	}
}
