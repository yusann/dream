//=============================================================================
// �v���C���[�i�󂯐g�j
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateDamage.h"
#include "playerStateLoading.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"
#include "meshField.h"

//=======================================================================================
//   �R���X�g���N�^�i�������j
//=======================================================================================
CPlayerStateDamage::CPlayerStateDamage(D3DXVECTOR2 damageVector) :
	m_DamageVector(damageVector),
	m_MoveY(1.0f){}

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateDamage::Update(CPlayer* pPlayer)
{
	m_MoveY -= PLAYER_GRAVITY;
	pPlayer->Position().y += m_MoveY;
	pPlayer->DamageMove(m_DamageVector);

	float floorPosY = pPlayer->GetFloorHeight();

	// ���n������
	if (pPlayer->Position().y < floorPosY)
	{
		m_MoveY = 0.0f;
		pPlayer->Position().y = floorPosY;
		pPlayer->ChangeState(new CPlayerStateLoading);
	}

	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_DAMAGE);
}
