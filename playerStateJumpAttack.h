#ifndef _PLAYER_STATE_JUMP_ATTACK_H_
#define _PLAYER_STATE_JUMP_ATTACK_H_

#include "playerState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayerStateJumpAttack : public CPlayerState
{
public:
	CPlayerStateJumpAttack();
	~CPlayerStateJumpAttack() {};

	void Update(CPlayer* pPlayer) override;

private:
	float m_MoveY;
	float m_FloorHeight;
};

#endif