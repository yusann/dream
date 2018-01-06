#ifndef _PLAYER_STATE_NORMAL_H_
#define _PLAYER_STATE_NORMAL_H_

#include "playerState.h"

//*****************************************************************************
//   プレイヤークラス定義
//*****************************************************************************
class CPlayerStateNormal : public CPlayerState
{
public:
	CPlayerStateNormal();
	~CPlayerStateNormal() {};

	void Update(CPlayer* pPlayer) override;

private:
	float m_MoveY;
	float m_FloorPosY;
};

#endif