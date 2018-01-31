#ifndef _ENEMY_STATE_NORMAL_H_
#define _ENEMY_STATE_NORMAL_H_

#include "enemyState.h"

//*****************************************************************************
//   プレイヤークラス定義
//*****************************************************************************
class CEnemyStateNormal : public CEnemyState
{
public:
	CEnemyStateNormal(float FloorPosY);
	~CEnemyStateNormal() {};

	void Update(CEnemy* pEnemy) override;

private:
	float m_MoveY;
	float m_FloorPosY;
	int   m_Frame;
	int   m_toNextStateFrame;
};

#endif