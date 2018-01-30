//=============================================================================
// �v���C���[
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateLoading.h"
#include "playerStateNormal.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "sceneMesh.h"
#include "player.h"

//=======================================================================================
//   �X�V����
//=======================================================================================
void CPlayerStateLoading::Update(CPlayer* pPlayer)
{
	// ���[�V�����̑���@�X�V
	pPlayer->SetMotion(CPlayer::STATE_LOADING);

	// ��ԑJ��
	if (pPlayer->EndMotionKey())
	{
		pPlayer->ChangeState(new CPlayerStateNormal);
	}
}
