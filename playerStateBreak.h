#ifndef _PLAYER_STATE_BREAK_H_
#define _PLAYER_STATE_BREAK_H_

#include "playerState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayerStateBreak : public CPlayerState
{
public:
	CPlayerStateBreak() {}
	~CPlayerStateBreak() {}

	void Update(CPlayer* pPlayer) override;
};

#endif