//=============================================================================
// �v���C���[
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateJumpUp.h"
#include "playerStateJumpDown.h"
#include "playerStateJumpAttack.h"
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
	int Key = pPlayer->GetKey();
	if (Key < 1)
	{
		return;
	}
	// �L�[����
	pPlayer->InputKeyMove(&m_Move);

	// �ړ�����
	m_Move.y -= PLAYER_GRAVITY;
	pPlayer->Position() += m_Move;
	m_Move.x = 0.0f;
	m_Move.z = 0.0f;

	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_JUMPUP);

	// ��ԕύX
	if (m_Move.y <= 0.0f)
	{
		pPlayer->ChangeState(new CPlayerStateJumpDown(m_Move.y));
	}
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpAttack());
	}
}
