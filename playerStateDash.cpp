//=============================================================================
// �v���C���[
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateDash.h"
#include "playerStateNormal.h"
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

#include "camera.h"
#include "sceneBillboard.h"
#include "particle.h"

//=======================================================================================
//   �R���X�g���N�^�i�������j
//=======================================================================================
CPlayerStateDash::CPlayerStateDash():
m_Move(D3DXVECTOR3(0.0f,0.0f,0.0f)),
m_FloorPosY(0.0f){}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateDash::Update(CPlayer* pPlayer)
{
	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_DASH);

	pPlayer->InputKeyMove(&m_Move, 1.5f);
	static int frame = 0;
	frame = frame % 10 + 1;
	if (frame == 10)
	{
		CParticle::SetParticl(CParticle::TYPE_RUN, pPlayer->Position());
	}

	// �ړ�����
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
	else if(pPlayer->Position().y- m_FloorPosY > 8.0f)
	{
		pPlayer->ChangeState(new CPlayerStateJumpDown(m_Move.y));
	}

	// ��ԕύX
	if (CInputKey::InputPlayerJump())
	{
		pPlayer->ChangeState(new CPlayerStateJumpUp(pPlayer->GetJumpHeight()));
	}
	if (!CInputKey::InputPlayerMove()||!CInputKey::InputPlayerDash())
	{
		pPlayer->ChangeState(new CPlayerStateNormal());
		return;
	}
	if (CInputKey::InputPlayerAttack())
	{
		pPlayer->SetMotion(CPlayer::STATE_ATTACK);
		pPlayer->ChangeState(new CPlayerStateAttack(m_Move.y));
		return;
	}
}
