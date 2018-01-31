#ifndef _ENEMY_STATE_CHASE_H_
#define _ENEMY_STATE_CHASE_H_

#include "enemyState.h"

//*****************************************************************************
//   �v���C���[�N���X��`
//*****************************************************************************
class CEnemyStateChase : public CEnemyState
{
public:
	CEnemyStateChase();
	~CEnemyStateChase() {};

	void Update(CEnemy* pEnemy) override;

private:
	D3DXVECTOR3 m_Move;
	float m_FloorPosY;
	float m_RotY;
	int   m_Frame;
	int   m_toNextStateFrame;
};

#endif