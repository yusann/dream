//=============================================================================
// �v���C���[�i�x�e�j
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateBreak.h"
#include "playerStateNormal.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "player.h"

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateBreak::Update(CPlayer* pPlayer)
{
	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_BREAK);

	pPlayer->Stamina() = min(pPlayer->Stamina() + 0.005f, PLAYER_STAMINA_MAX);

	// ��ԑJ��
	if (pPlayer->Stamina() >= PLAYER_STAMINA_MAX)
	{
		pPlayer->ChangeState(new CPlayerStateNormal);
	}
}
