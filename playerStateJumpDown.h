#ifndef _PLAYER_STATE_JUMP_DOWN_H_
#define _PLAYER_STATE_JUMP_DOWN_H_

#include "playerState.h"

//*****************************************************************************
//   プレイヤークラス定義
//*****************************************************************************
class CPlayerStateJumpDown : public CPlayerState
{
public:
	CPlayerStateJumpDown(float JumpHeight);
	~CPlayerStateJumpDown() {};

	void Update(CPlayer* pPlayer) override;

private:
	CPlayerStateJumpDown(){}

	D3DXVECTOR3 m_Move;
	float m_FloorHeight;
};

#endif