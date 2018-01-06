#ifndef _PLAYER_STATE_LOADING_H_
#define _PLAYER_STATE_LOADING_H_

#include "playerState.h"

//*****************************************************************************
//   プレイヤークラス定義
//*****************************************************************************
class CPlayerStateLoading : public CPlayerState
{
public:
	CPlayerStateLoading() {}
	~CPlayerStateLoading() {}

	void Update(CPlayer* pPlayer) override;
};

#endif