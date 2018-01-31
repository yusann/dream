#ifndef _ENEMY_STATE_MOVE_H_
#define _ENEMY_STATE_MOVE_H_

#include "enemyState.h"

//*****************************************************************************
//   プレイヤークラス定義
//*****************************************************************************
class CEnemyStateMove : public CEnemyState
{
public:
	CEnemyStateMove();
	~CEnemyStateMove() {};

	void Update(CEnemy* pEnemy) override;

private:
	D3DXVECTOR3 m_Move;
	float m_FloorPosY;
	float m_RotY;
	int   m_Frame;
	int   m_toNextStateFrame;
};

#endif