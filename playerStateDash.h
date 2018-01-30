#ifndef _PLAYER_STATE_DASH_H_
#define _PLAYER_STATE_DASH_H_

#include "playerState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayerStateDash : public CPlayerState
{
public:
	CPlayerStateDash();
	~CPlayerStateDash() {};

	void Update(CPlayer* pPlayer) override;
private:
	D3DXVECTOR3 m_Move;
	float m_FloorPosY;
};

#endif