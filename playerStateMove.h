#ifndef _PLAYER_STATE_MOVE_H_
#define _PLAYER_STATE_MOVE_H_

#include "playerState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayerStateMove : public CPlayerState
{
public:
	CPlayerStateMove();
	~CPlayerStateMove() {};

	void Update(CPlayer* pPlayer) override;
private:
	D3DXVECTOR3 m_Move;
	float m_FloorPosY;
};

#endif