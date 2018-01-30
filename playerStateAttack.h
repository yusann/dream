#ifndef _PLAYER_STATE_ATTACK_H_
#define _PLAYER_STATE_ATTACK_H_

#include "playerState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayerStateAttack : public CPlayerState
{
public:
	CPlayerStateAttack();
	~CPlayerStateAttack() {};

	void Update(CPlayer* pPlayer) override;

private:
	D3DXVECTOR3 m_Move;
	float m_FloorPosY;
};

#endif