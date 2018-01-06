#ifndef _PLAYER_STATE_JUMP_UP_H_
#define _PLAYER_STATE_JUMP_UP_H_

#include "playerState.h"

//*****************************************************************************
//   プレイヤークラス定義
//*****************************************************************************
class CPlayerStateJumpUp : public CPlayerState
{
public:
	CPlayerStateJumpUp(float JumpHeight);
	~CPlayerStateJumpUp() {};

	void Update(CPlayer* pPlayer) override;

private:
	CPlayerStateJumpUp(){}

	D3DXVECTOR3 m_Move;
};

#endif