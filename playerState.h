#ifndef _PLAYERSTATE_H_
#define _PLAYERSTATE_H_

// �O���錾
class CPlayer;

#define PLAYER_GRAVITY				(0.08f)       // �d��

//*****************************************************************************
//   �v���C���[��Ԓ�`
//*****************************************************************************
class CPlayerState
{
public:
	virtual ~CPlayerState() {}
	virtual void Update(CPlayer* pPlayer) = 0;
};
class CPlayerStateNone : public CPlayerState
{
public:
	virtual ~CPlayerStateNone() {}
	virtual void Update(CPlayer* pEnemy) override {}
};

#endif