#ifndef _PLAYER_STATE_LOADING_H_
#define _PLAYER_STATE_LOADING_H_

#include "playerState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CPlayerStateLoading : public CPlayerState
{
public:
	CPlayerStateLoading() {}
	~CPlayerStateLoading() {}

	void Update(CPlayer* pPlayer) override;
};

#endif