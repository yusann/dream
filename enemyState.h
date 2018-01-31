#ifndef _ENEMYSTATE_H_
#define _ENEMYSTATE_H_

// �O���錾
class CEnemy;

#define ENEMY_GRAVITY				(0.08f)       // �d��

//*****************************************************************************
//   �v���C���[��Ԓ�`
//*****************************************************************************
class CEnemyState
{
public:
	virtual ~CEnemyState() {}
	virtual void Update(CEnemy* pEnemy) = 0;
};
class CEnemyStateNone : public CEnemyState
{
public:
	virtual ~CEnemyStateNone() {}
	virtual void Update(CEnemy* pEnemy) override {}
};

#endif