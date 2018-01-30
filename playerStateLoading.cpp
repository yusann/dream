//=============================================================================
// プレイヤー
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
//   更新処理
//=======================================================================================
void CPlayerStateLoading::Update(CPlayer* pPlayer)
{
	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_LOADING);

	// 状態遷移
	if (pPlayer->EndMotionKey())
	{
		pPlayer->ChangeState(new CPlayerStateNormal);
	}
}
