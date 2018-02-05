//=============================================================================
// プレイヤー（休憩）
// Author : YUUSAN KA
//=============================================================================
#include "main.h"
#include "playerStateBreak.h"
#include "playerStateNormal.h"

#include "scene.h"
#include "sceneMotionPartsX.h"
#include "player.h"

//=======================================================================================
//   更新処理
//=======================================================================================
void CPlayerStateBreak::Update(CPlayer* pPlayer)
{
	// モーションの代入　更新
	pPlayer->SetMotion(CPlayer::STATE_BREAK);

	pPlayer->Stamina() = min(pPlayer->Stamina() + 0.005f, PLAYER_STAMINA_MAX);

	// 状態遷移
	if (pPlayer->Stamina() >= PLAYER_STAMINA_MAX)
	{
		pPlayer->ChangeState(new CPlayerStateNormal);
	}
}
