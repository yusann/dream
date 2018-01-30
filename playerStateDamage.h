#ifndef _PLAYER_STATE_Damage_H_
#define _PLAYER_STATE_Damage_H_

#include "playerState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayerStateDamage : public CPlayerState
{
public:
	CPlayerStateDamage(D3DXVECTOR2 damageVector);
	~CPlayerStateDamage() {}

	void Update(CPlayer* pPlayer) override;
private:
	D3DXVECTOR2 m_DamageVector;
	float m_MoveY;
};

#endif