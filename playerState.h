#ifndef _PLAYERSTATE_H_
#define _PLAYERSTATE_H_

// 前方宣言
class CPlayer;

#define PLAYER_GRAVITY				(0.08f)       // 重力

//*****************************************************************************
//   プレイヤー状態定義
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